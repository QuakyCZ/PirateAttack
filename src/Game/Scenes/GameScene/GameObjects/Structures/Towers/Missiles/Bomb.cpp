//
// Created by KRATSTOM on 28.05.21.
//

#include "Bomb.h"
#include "../../../../GameScene.h"
Bomb::Bomb(const int & maxDistance, const int & attackDamage)
: Missile(maxDistance, attackDamage) {
    auto texture = ResourceManager::getTexture("bomb");
    if(texture)
        setTexture(texture->texture);
    setScale({16,16});
}

Bomb::Bomb(Bomb *other):Missile(other) {}


GameObject *Bomb::clone() {
    return new Bomb(this);
}

/**
 * Set target as current position of the targeted game object
 */
void Bomb::start() {
    Missile::start();
    setTarget(target->getAbsolutePosition());
}

/**
 * Explodes and deals field damage.
 */
void Bomb::onTargetReached() {
    Missile::onTargetReached();
    for(auto unit : GameScene::getPlayer()->getUnits()) {
        if(Vector2D::distance(getAbsolutePosition(), unit->getAbsolutePosition()) < (range * 32))
            unit->onDamage(this->damage);
    }
}

/**
 * Explode when max distance reached.
 */
void Bomb::onMaxDistanceReached() {
    Missile::onMaxDistanceReached();
    onTargetReached();
}

