//
// Created by KRATSTOM on 06.05.2021.
//

#include "Map.h"
#include <iostream>
#include <algorithm>

Map::Map(const std::string &name, const std::string &mapFile) : GameObject(name) {
    try {
        loadMap(mapFile);
    } catch (std::invalid_argument &e) {
        cleanMap();
        throw e;
    }
    //SDL_Color c = {153, 204, 237, 255};
    getSprite()->setColor({0,0,0,0});
}

Map::~Map() {
    cleanMap();
}

void Map::cleanMap() {
    if(!tilemap)
        return;
    for(int y = 0; y < height; y++) {
        for(auto tile : tilemap[y])
            delete tile;
    }
    delete[] tilemap;
}

/**
 * Reads file with map char by char and creates an array of tilemap
 * @param mapFile a path to the file with the map
 * @throws std::invalid_argument
 */
void Map::loadMap(const std::string &mapFile) {
    Logger::info("Loading map from " + mapFile);
    std::ifstream in(mapFile.c_str());
    if (in.is_open()) {
        try {
            loadDimensions(in);

            tilemap = new std::vector<Tile *>[height];
            setScale(width * 32, height * 32);
            setAbsolutePosition({1920.0F / 2 - (float)width * 16, 1080.0F / 2 - (float)height * 16});

            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    char ch;
                    in.get(ch);
                    loadTile(ch, x, y);
                }
                char next;
                in.get(next);
                if (next != '\n')
                    throw std::invalid_argument("Invalid character in the map file at the end of the line " + std::to_string(y) + ".");
            }
        } catch (std::invalid_argument &e) {
            in.close();
            throw e;
        }
        in.close();
        if(!baseTile) {
            throw std::invalid_argument("There is not a Base in the Map!");
        }
        calculateDistancesFromTheBase();
        sortTowerSlotsByDistanceFromTheBase();
        assignTextures();
    } else {
        throw std::invalid_argument("Map file " + mapFile + " was not found!");
    }
}



/**
 * Reads dimensions from the map file.
 * @param in the stream of the file.
 */
void Map::loadDimensions(std::ifstream &in) {
    std::string dimensions;
    in >> height;
    if (in.fail()) {
        in.close();
        throw std::invalid_argument("Invalid height in the map file.");
    }
    in >> width;
    if (in.fail()) {
        in.close();
        throw std::invalid_argument("Invalid width in the map file.");
    }
    in.get(); //remove \n character after dimensions
    Logger::info("Map dimensions: W=" + std::to_string(width) + " H=" + std::to_string(height));
}

/**
 * Loads a tile by the tileChar.
 * @param tileChar the character representing the tile. <br>
 * '#' - water <br>
 * '$' - tower slot <br>
 * ' ' - land<br>
 * 'B' - base<br>
 * 'I' - input (starting point for units)<br>
 * @param x the x coordinate
 * @param y the y coordinate
 */
void Map::loadTile(char tileChar, int x, int y) {
    //Logger::info("Char: " + std::to_string(tileChar));
    Tile::TileType tileType;
    switch (tileChar) {
        case '#':
            tileType = Tile::TileType::SEA;
            break;
        case ' ':
            tileType = Tile::TileType::LAND;
            break;
        case '$':
            tileType = Tile::TileType::TOWER_SLOT;
            break;
        case 'B':
            tileType = Tile::TileType::BASE;
            break;
        case 'I':
            tileType = Tile::TileType::UNIT_DROP_OFF;
            break;
        default:
            throw std::invalid_argument(
                    "Invalid char in the map at X=" + std::to_string(x) + " Y=" + std::to_string(y));
    }
    auto tileGO = new GameObject("tile_" + std::to_string(x) + "_" + std::to_string(y));
    tileGO->setScale({32, 32});
    tileGO->setParent(this);
    tileGO->setRelativePosition({(float)x * 32, (float)y * 32});

    Tile * tile = new Tile(((int)tilemap[y].size() + 1) + y * width, {(float) x, (float) y}, tileType, tileGO);
    tilemap[y].push_back(tile);
    if(tileType==Tile::TileType::BASE) {
        if(baseTile != nullptr)
            throw std::invalid_argument("Map can't have more than 1 base!");
        baseTile = tile;
    } else if(tileType == Tile::TileType::TOWER_SLOT) {
        towerSlots.push_back(tile);
    }
}

/**
 * Calculate and assign heuristic distances from the Base for each tile.
 */
void Map::calculateDistancesFromTheBase() {
    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {
            float dist = Vector2D::distance(baseTile->getPosition(), tilemap[y][x]->getPosition());
            tilemap[y][x]->setDistanceFromBase(dist);
        }
    }
}

void Map::sortTowerSlotsByDistanceFromTheBase() {
    std::sort(towerSlots.begin(), towerSlots.end(), [](Tile * t1, Tile * t2) {
        return t1->getDefenseLevel() < t2->getDefenseLevel() 
        || (t1->getDefenseLevel() == t2->getDefenseLevel() 
        && t1->getDistanceFromBase() < t2->getDistanceFromBase());
    });
}

/**
 * Assigns textures of land by its neighbors.
 */
void Map::assignTextures() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            auto tile = tilemap[y][x];
            if (tile->getType() == Tile::TileType::SEA) {
                tile->getGameObject()->setVisibility(false);
                continue;
            }
            std::string tileName = "tile_";
            if (y > 0 && tilemap[y - 1][x]->getType() != Tile::TileType::SEA)
                tileName.push_back('N');
            if (y < height - 1 && tilemap[y + 1][x]->getType() != Tile::TileType::SEA)
                tileName.push_back('S');
            if (x > 0 && tilemap[y][x - 1]->getType() != Tile::TileType::SEA)
                tileName.push_back('W');
            if (x < width - 1 && tilemap[y][x + 1]->getType() != Tile::TileType::SEA)
                tileName.push_back('E');

            if(y > 0 && x > 0 && tilemap[y-1][x-1]->getType() != Tile::TileType::SEA)
                tileName.push_back('q');
            if(y > 0 && x < width - 1 && tilemap[y-1][x+1]->getType() != Tile::TileType::SEA)
                tileName.push_back('p');
            if(y < height - 1 && x < width - 1 && tilemap[y+1][x+1]->getType() != Tile::TileType::SEA)
                tileName.push_back('b');
            if(y < height - 1 && x > 0 && tilemap[y+1][x-1]->getType() != Tile::TileType::SEA)
                tileName.push_back('d');

            auto texture = ResourceManager::getTexture(tileName);
            if (texture)
                tile->getGameObject()->setTexture(texture->texture);
            else
                tile->getGameObject()->getSprite()->setColor({247, 195, 82, 255});
        }
    }
}

/**
 * @param pos the absolutePosition to check
 * @return true if the absolutePosition is outside of bounds of the map.
 */
bool Map::isOutOfRange(const Vector2D & pos) const {
    return pos.x < 0 || pos.x >= width || pos.y < 0 || pos.y >= height;
}

/**
 * @param pos the absolutePosition of the tile
 * @return tile at the specified absolutePosition.
 * @throws std::invalid_argument if the absolutePosition is out of bounds of the map.
 */
Tile * Map::getTileAt(const Vector2D & pos) const {
    Vector2D clamped = pos;
    clamped.clamp();
    if(isOutOfRange(clamped))
        throw std::invalid_argument("Tile &Map::getTileAt: Position " + std::to_string(clamped.x) + " " + std::to_string(clamped.y) + " is out of range of the map!");
    return tilemap[(int)clamped.y][(int)clamped.x];
}

/**
 * @return width and height of the map.
 */
Vector2D Map::getDimensions() const {
    return Vector2D(width, height);
}

/**
 * @param tile the tile to find neighbors for
 * @return vector with neighbors of the tile
 * @throws std::invalid_argument if the absolutePosition of the tile is outside of bounds of the map
 */
std::vector<Tile *> Map::getNeighbors(const Tile &tile) const {
    return getNeighbors(tile.getPosition());
}

/**
 * @param position the absolutePosition of the tile
 * @return vector with neighbors of the tile at the specified absolutePosition
 * @throws std::invalid_argument if the absolutePosition is outside of bounds of the map
 */
std::vector<Tile *> Map::getNeighbors(const Vector2D &position) const {
    if(isOutOfRange(position))
        throw std::invalid_argument("std::vector<Tile> Map::getNeighbors: Position " + std::to_string(position.x) + " " + std::to_string(position.y) + " is out of range of the map!");

    std::vector<Tile *> neighbors;
    if(position.x > 0)
        neighbors.push_back(tilemap[(int)position.y][(int)position.x - 1]);
    if(position.x < (float) width - 1)
        neighbors.push_back(tilemap[(int)position.y][(int)position.x + 1]);
    if(position.y > 0)
        neighbors.push_back(tilemap[(int)position.y - 1][(int)position.x]);
    if((int)position.y < height - 1)
        neighbors.push_back(tilemap[(int)position.y + 1][(int)position.x]);

    // diagonal neighbors
    if(position.x > 0 && position.y > 0)
        neighbors.push_back(tilemap[(int)position.y - 1][(int)position.x - 1]);
    if(position.x > 0 && (int)position.y < height - 1)
        neighbors.push_back(tilemap[(int)position.y + 1][(int)position.x - 1]);
    if((int)position.x < width - 1 && position.y > 0)
        neighbors.push_back(tilemap[(int)position.y - 1][(int)position.x + 1]);
    if((int)position.x < width - 1 && (int)position.y < height - 1)
        neighbors.push_back(tilemap[(int)position.y + 1][(int)position.x + 1]);

    return neighbors;
}

/**
 * A* pathfinding
 * @param start the map position of the start tile
 * @param end the end position of the tile to find path to
 * @return a list of move Vector2D's to the end tile if the path has been found. If not, it's empty.
 */
std::list<Vector2D> Map::findPath(const Vector2D &start, const Vector2D &end) {
    Tile * startTile = getTileAt(start);

    std::vector<Tile *> openTiles;
    std::set<int> openPositions;
    std::set<int> closedTiles;

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            tilemap[y][x]->gCost = INT_MAX;
            tilemap[y][x]->cameFrom = nullptr;
        }
    }
    startTile->gCost = 0;
    startTile->hCost = (int)Vector2D::distance(start, end);

    openTiles.push_back(startTile);
    while(!openTiles.empty()) {
        auto current = getAndRemoveLowestFCostTile(openTiles);

        if(current->getPosition() == end)
            return calculatePath(current);

        closedTiles.insert(current->getId());

        for(auto & neighbour : getWalkableNeighbors(current->getPosition())) {
            if(closedTiles.find(neighbour->getId()) == closedTiles.end()) {
                int tentativeCost = current->gCost + (int)Vector2D::distance(current->getPosition(), neighbour->getPosition());
                if(tentativeCost < neighbour->gCost) {
                    neighbour->cameFrom = current;
                    neighbour->gCost = tentativeCost;
                    neighbour->hCost = (int)Vector2D::distance(neighbour->getPosition(), end);
                    if(openPositions.insert(neighbour->getId()).second)
                        openTiles.push_back(neighbour);
                }
            }
        }
    }
    return {};
}

/**
 * Reverse the path from end to the start.
 * @param tile the end tile
 * @return vectors with the path from the start to the end
 */
std::list<Vector2D> Map::calculatePath(Tile * tile) const {
    std::list<Vector2D> path;
    auto current = tile;
    while(current != nullptr) {
        path.push_front(current->getPosition());
        current = current->cameFrom;
    }
    return path;
}

/**
 * Find lowest FCost tile from tiles and remove it.
 * @param tiles vector of pending tiles
 * @return the lowest FCost tile or nullptr if tiles are empty.
 */
Tile * Map::getAndRemoveLowestFCostTile(std::vector<Tile*> & tiles) const {
    if(tiles.empty())
        return nullptr;
    auto lowest = tiles.begin();
    for(auto it = tiles.begin(); it != tiles.end(); ++it) {
        if((*it)->getFCost() < (*lowest)->getFCost())
            lowest = it;
    }
    Tile * t = *lowest;
    tiles.erase(lowest);
    return t;
}

/**
 * @param screenPosition the absolute position of the tile
 * @return Vector2D with the tile position in the map or {-1, -1} if it's out of bounds
 */
Vector2D Map::screenToMap(const Vector2D &screenPosition) const {
    Vector2D relativeToMap(screenPosition.x - getAbsolutePosition().x, screenPosition.y - getAbsolutePosition().y);
    if(relativeToMap.x < 0 || relativeToMap.y < 0 || relativeToMap.x >= getScale().x || relativeToMap.y >= getScale().y)
        return {-1, -1};
    relativeToMap.x /= tileScale.x;
    relativeToMap.y /= tileScale.y;
    relativeToMap.clamp();
    return relativeToMap;
}

/**
 * @param position the position of the tile
 * @return vector with walkable neighbors
 */
std::vector<Tile *> Map::getWalkableNeighbors(const Vector2D &position) const {
    if(isOutOfRange(position))
        throw std::invalid_argument("std::vector<Tile> Map::getNeighbors: Position " + std::to_string(position.x) + " " + std::to_string(position.y) + " is out of range of the map!");

    std::vector<Tile *> neighbors;
    if(position.x > 0 && tilemap[(int)position.y][(int)position.x - 1]->isWalkable())
        neighbors.push_back(tilemap[(int)position.y][(int)position.x - 1]);
    if(position.x < (float) width - 1 && tilemap[(int)position.y][(int)position.x + 1]->isWalkable())
        neighbors.push_back(tilemap[(int)position.y][(int)position.x + 1]);
    if(position.y > 0 && tilemap[(int)position.y - 1][(int)position.x]->isWalkable())
        neighbors.push_back(tilemap[(int)position.y - 1][(int)position.x]);
    if((int)position.y < height - 1 && tilemap[(int)position.y + 1][(int)position.x]->isWalkable())
        neighbors.push_back(tilemap[(int)position.y + 1][(int)position.x]);

    // diagonal neighbors
    if(position.x > 0 && position.y > 0
        && tilemap[(int)position.y - 1][(int)position.x - 1]->isWalkable()
        && tilemap[(int)position.y][(int)position.x - 1]->isWalkable()
        && tilemap[(int)position.y - 1][(int)position.x]->isWalkable()
    )
        neighbors.push_back(tilemap[(int)position.y - 1][(int)position.x - 1]);
    if(position.x > 0
        && (int)position.y < height - 1
        && tilemap[(int)position.y + 1][(int)position.x - 1]->isWalkable()
        && tilemap[(int)position.y][(int)position.x - 1]->isWalkable()
        && tilemap[(int)position.y - 1][(int)position.x]->isWalkable()
    )
        neighbors.push_back(tilemap[(int)position.y + 1][(int)position.x - 1]);
    if((int)position.x < width - 1
        && position.y > 0
        && tilemap[(int)position.y - 1][(int)position.x + 1]->isWalkable()
        && tilemap[(int)position.y - 1][(int)position.x]->isWalkable()
        && tilemap[(int)position.y][(int)position.x + 1]->isWalkable()
    )
        neighbors.push_back(tilemap[(int)position.y - 1][(int)position.x + 1]);
    if((int)position.x < width - 1
        && (int)position.y < height - 1
        && tilemap[(int)position.y + 1][(int)position.x + 1]->isWalkable()
        && tilemap[(int)position.y][(int)position.x + 1]->isWalkable()
        && tilemap[(int)position.y + 1][(int)position.x]->isWalkable()
        )
        neighbors.push_back(tilemap[(int)position.y + 1][(int)position.x + 1]);

    return neighbors;
}

/**
 * BFS
 * @param position the position for which the structure should be found.
 * @return nearest living structure or nullptr if no structure was found or if the position was out of bounds of the map
 */
LivingStructure *Map::getNearestLivingStructure(const Vector2D & position) const {
    if(isOutOfRange(position))
        return nullptr;
    
    std::queue<Tile *> tileQueue;
    std::set<Tile *> checkedTiles;
    auto startTile = getTileAt(position);
    tileQueue.push(startTile);
    checkedTiles.insert(startTile);
    
    while(!tileQueue.empty()) {
        auto currentTile = tileQueue.front();
        tileQueue.pop();
        
        if(currentTile->getType() == Tile::TileType::BASE)
            return dynamic_cast<LivingStructure*>(currentTile->getStructure());
        
        else if(currentTile->getType() == Tile::TileType::TOWER_SLOT) {
            auto slot = dynamic_cast<TowerSlot *>(currentTile->getStructure());
            if(slot->hasTower())
                return slot->getTower();
        }
        
        for(auto nb : getNeighbors(currentTile->getPosition())) {
            if(nb->isWalkable() && checkedTiles.insert(nb).second)
                tileQueue.push(nb);
        }
    }
    
    
    return nullptr;
}
