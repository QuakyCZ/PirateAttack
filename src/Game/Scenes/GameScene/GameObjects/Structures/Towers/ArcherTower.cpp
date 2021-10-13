//
// Created by KRATSTOM on 06.05.2021.
//

#include "ArcherTower.h"

ArcherTower::ArcherTower()
: Tower("archer_tower") {
    auto texture = ResourceManager::getTexture("archer_tower");
    if(texture)
        setTexture(texture->texture);
    setScale(32, 32);
}

ArcherTower::ArcherTower(ArcherTower *other): Tower(other) {}

GameObject *ArcherTower::clone() {
    return new ArcherTower(this);
}

/**
 * Assigns Arrow to the missilePrefab
 */
void ArcherTower::start() {
    Tower::start();
    if(!missilePrefab)
        missilePrefab = new Arrow(range, attack);
}

