//
// Created by KRATSTOM on 01.06.21.
//

#include "Arrow.h"

Arrow::Arrow(const int & maxDistance, const int & damage): Missile(maxDistance, damage) {
    auto texture = ResourceManager::getTexture("arrow");
    if(texture)
        setTexture(texture->texture);
    setScale(32, 32);
}

Arrow::Arrow(Arrow * other): Missile(other) {}


GameObject *Arrow::clone() {
    return new Arrow(this);
}

/**
 * Move to the target and rotate self to look to it.
 * @param deltaTime 
 */
void Arrow::update(const float &deltaTime) {
    Missile::update(deltaTime);
    Vector2D centerPoint = getAbsolutePosition();
    centerPoint.x += getScale().x / 2;
    centerPoint.y += getScale().y / 2;
    
    float xDist = centerPoint.x - targetPosition.x;
    float yDist = centerPoint.y - targetPosition.y;
    int angle = 0;
    if(fabsf(yDist) < 0.0001) {
        if(fabsf(xDist) < 0.0001)
            return;
        angle = xDist > 0 ? 90 : -90;    
    } else
        angle = 180 - (int)(std::atan(xDist / yDist) * 180 / 3.14159265);
    
    getSprite()->setAngle((int)angle);
}

/**
 * Hit the target.
 */
void Arrow::onTargetReached() {
    Missile::onTargetReached();
    if(!target || target->isDestroyed())
        return;
    target->onDamage(damage);
}
