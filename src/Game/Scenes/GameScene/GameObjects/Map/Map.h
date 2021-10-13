//
// Created by KRATSTOM on 06.05.2021.
//

#pragma once
#include "Tile.h"
#include <climits>
#include <list>
#include <set>
#include <queue>

class Map: public GameObject {
private:
    std::vector<Tile *> * tilemap = nullptr;
    Vector2D tileScale = {32, 32};
    int width = 0, height = 0;
    std::vector<Tile *> towerSlots;
    
    void loadMap(const std::string &mapFile);
    void cleanMap();
    void loadDimensions(std::ifstream & in);
    void loadTile(char tileChar, int x, int y);
    void calculateDistancesFromTheBase();
    void sortTowerSlotsByDistanceFromTheBase();
    void assignTextures();

    bool isOutOfRange(const Vector2D & pos) const;

    std::list<Vector2D> calculatePath(Tile * tile) const;
    Tile * getAndRemoveLowestFCostTile(std::vector<Tile*> & tiles) const;
public:
    Tile * baseTile = nullptr;
    
    explicit Map(const std::string & name, const std::string &mapFile);
    ~Map() override;

    Tile * getTileAt(const Vector2D & pos) const;
    std::vector<Tile *> getNeighbors(const Tile & tile) const;
    std::vector<Tile *> getNeighbors(const Vector2D & position) const;
    std::vector<Tile *> getWalkableNeighbors(const Vector2D & position) const;
    Vector2D getDimensions() const;
    std::list<Vector2D> findPath(const Vector2D & start, const Vector2D & end);
    Vector2D screenToMap(const Vector2D & screenPosition) const;

    std::vector<Tile *> & getTowerSlots() {
        return towerSlots;
    }
    
    LivingStructure *getNearestLivingStructure(const Vector2D & position) const;
};
