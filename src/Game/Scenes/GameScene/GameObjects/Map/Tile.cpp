//
// Created by KRATSTOM on 19.05.21.
//

#include "Tile.h"


Tile::Tile(const int & id, const Vector2D & pos, const TileType & type, GameObject * tileGO):
id(id), type(type), mapPosition(pos), tileGO(tileGO) {
    buildStructure();
}

/**
 * @return the type of the tile
 */
Tile::TileType Tile::getType() const{
    return type;
}

/**
 * @return game object of the tile
 */
GameObject *Tile::getGameObject() const {
    return tileGO;
}

/**
 * Builds a structure on the tile according to the type of the tile.
 */
void Tile::buildStructure() {
    switch(type) {
        default: return;
        case TileType::BASE:
            this->structure = new Base();
            this->structure->getSprite()->setColor({255, 0, 0, 255});
            break;
        case TileType::UNIT_DROP_OFF:
            this->structure = new UnitDropOff();
            this->structure->getSprite()->setColor({0, 255, 0, 255});
            break;
        case TileType::TOWER_SLOT:
            this->structure = new TowerSlot();
            this->structure->getSprite()->setColor({0, 0, 255, 255});
            break;
    }

    structure->setParent(tileGO);
    structure->setRelativePosition({0,0});
    structure->setScale(32, 32);
    structure->start();
}

/**
 * @return the structure that is built on the tile or nullptr.
 */
Structure *Tile::getStructure() const {
    return structure;
}

/**
 * Clear pointer of the structure.
 */
void Tile::destroyStructure() {
    structure = nullptr;
}

/**
 * @return the defense level of this tile. Also number of towers that can target this tile.
 */
int Tile::getDefenseLevel() const {
    return defenseLevel;
}

/**
 * @param other the othe tile to compare
 * @return true if tile's id is less than other's id. It means that this tile is left or 
 */
bool Tile::operator<(const Tile &other) const {
    return id < other.id;
}
