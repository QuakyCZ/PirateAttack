//
// Created by KRATSTOM on 19.05.21.
//

#pragma once

#include "../Structures/Base.h"
#include "../Structures/UnitDropOff.h"
#include "../Structures/TowerSlot.h"

class Tile {
public:
    enum TileType {
        SEA, LAND, TOWER_SLOT, BASE, UNIT_DROP_OFF
    };
    Tile(const int & id, const Vector2D & pos, const TileType & type, GameObject * tileGO);

    TileType getType() const;
    GameObject * getGameObject() const;
    
    /**
     * @return Vector2D with the position on the map
     */
    Vector2D getPosition() const {
        return mapPosition;
    }

    int getId() const {
        return id;
    }

    void buildStructure();
    void destroyStructure();
    int getDefenseLevel() const;
    void changeDefenseLevel(const int & val) {
        defenseLevel += val;
    }

    Structure * getStructure() const;

    Tile * cameFrom = nullptr;
    int gCost = 0, hCost = 0;
    
    /**
     * @return FCost = gCost + hCost + defenseLevel
     */
    int getFCost() const {
        return gCost + hCost + defenseLevel;
    }

    bool operator < (const Tile & other) const;

    /**
     * @return true if units can walk on this tile
     */
    bool isWalkable() const {
        return type != SEA;
    }

    /**
     * Set the heuristic distance from the base. It won't be overwritten if it was already set.
     * @param value the heuristic distance from the base
     */
    void setDistanceFromBase(const float & value) {
        if(distanceFromBase == -1)
            distanceFromBase = value;
    };

    /**
     * @return distance from the base
     */
    float getDistanceFromBase() const {
        return distanceFromBase;
    }
private:
    int id;
    TileType type = SEA;
    int defenseLevel = 0;
    Vector2D mapPosition;
    GameObject * tileGO = nullptr;
    GameObject * map = nullptr;
    Structure * structure = nullptr;
    float distanceFromBase = -1;
};