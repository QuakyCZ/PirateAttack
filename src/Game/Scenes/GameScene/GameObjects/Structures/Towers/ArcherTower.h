//
// Created by KRATSTOM on 06.05.2021.
//

#pragma once
#include "Tower.h"
#include "Missiles/Arrow.h"
class ArcherTower: public Tower {
private:
public:
    ArcherTower();
    ArcherTower(ArcherTower * other);
    GameObject * clone() override;
    void start() override;
};