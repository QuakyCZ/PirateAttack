//
// Created by KRATSTOM on 06.05.2021.
//

#pragma once
#include "Tower.h"
#include "Missiles/Bomb.h"
class BombTower: public Tower {
public:
    BombTower();
    explicit BombTower(BombTower * other);
    GameObject * clone() override;
    
    void start() override;
};