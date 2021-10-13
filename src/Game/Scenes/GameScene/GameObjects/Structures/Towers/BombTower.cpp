//
// Created by KRATSTOM on 06.05.2021.
//

#include "BombTower.h"
BombTower::BombTower()
: Tower("bomb_tower") {
    auto texture = ResourceManager::getTexture("bomb_tower");
    if(texture)
        setTexture(texture->texture);
    setScale(32, 32);
}

BombTower::BombTower(BombTower *other)
: Tower(other) {}

/**
 * @return a clone of this.
 */
GameObject * BombTower::clone() {
    return new BombTower(this);
}

/**
 * Create prefab of a bomb missile
 */
void BombTower::start() {
    Tower::start();
    if(!missilePrefab)
        missilePrefab = new Bomb(getRange(), attack);
}
