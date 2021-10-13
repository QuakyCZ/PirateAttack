//
// Created by KRATSTOM on 28.05.21.
//

#include "Missile.h"

/**
 * The constructor
 * @param maxDistance max distance that can be reached from the tower
 * @param damage the damage to deal to enemy / enemies.
 */
Missile::Missile(const int & maxDistance, const int & damage)
: GameObject("Missile"), maxDistance(maxDistance), damage(damage) {}

/**
 * The copy constructor
 * @param other other Missile
 */
Missile::Missile(Missile *other)
: GameObject(other), maxDistance(other->maxDistance), target(other->target), targetPosition(other->targetPosition), damage(other->damage) {}

/**
 * Clone a Missile
 * @return a pointer to a clone of the missile
 */
GameObject *Missile::clone() {
    return new Missile(this);
}

/**
 * Set a unit as a target of the missile.
 * @param newTarget 
 */
void Missile::setTarget(Unit *newTarget) {
    target = newTarget;
}

/**
 * Set an absolute position as a target of the missile.
 * @param newTarget 
 */
void Missile::setTarget(const Vector2D &newTarget) {
    target = nullptr;
    targetPosition = newTarget;
}

/**
 * Prepare missile before it starts moving.
 */
void Missile::start() {
    GameObject::start();
    if(!target) {
        destroyed = true;
        Logger::warn("Missile had not a target!");
    }
    if(parent)
        setRelativePosition(getScale() / 2);
    
    startingPosition = getAbsolutePosition();
}

/**
 * Move to the target until it's reached.
 * @param deltaTime 
 */
void Missile::update(const float &deltaTime) {
    GameObject::update(deltaTime);
    Vector2D moveVector;
    
    if(target) {
        targetPosition = target->getAbsolutePosition();
        targetPosition.x += target->getScale().x / 2;
        targetPosition.y += target->getScale().y / 2;
        if(target->isDestroyed()) {
            target = nullptr;    
        }
    }
    
    Vector2D targetCenter = getAbsolutePosition() + Vector2D(getScale().x / 2, getScale().y / 2);
    
    if(Vector2D::distance(targetCenter, targetPosition) < 32) {
        onTargetReached();
        return;
    }
    
    moveVector = Vector2D::moveTowards(getAbsolutePosition(), targetPosition);
    moveVector.normalize();
    moveVector *= (float)deltaTime / 1000.0F * 32 * speed;    
    setAbsolutePosition(getAbsolutePosition() + moveVector);
    if(Vector2D::distance(getAbsolutePosition(), startingPosition) > (float)maxDistance * 32)
        onMaxDistanceReached();
}

/**
 * Do something when the missile reached the target.
 */
void Missile::onTargetReached() {
    Logger::info("Target reached.");
    destroyed = true;
}

/**
 * Do something (destroy self) when the max distance from the tower has been reached.
 */
void Missile::onMaxDistanceReached() {
    destroyed = true;
}
