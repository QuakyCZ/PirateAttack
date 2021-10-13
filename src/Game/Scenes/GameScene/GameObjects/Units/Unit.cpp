//
// Created by KRATSTOM on 06.05.2021.
//

#include "Unit.h"
#include "../../GameScene.h"

Unit::Unit(const std::string & name)
        : GameObject(name) {
    auto values = ResourceManager::getConfig("units").getValues(name);
    if(values.size() < 6)
        throw std::invalid_argument("Config of unit " + name + " has not enough values.");

    maxAmount = std::stoi(values[0]);
    price = std::stoi(values[1]);
    maxHealth = std::stoi(values[2]);
    health = maxHealth;
    damage = std::stoi(values[3]);
    attackCooldown = std::stoi(values[4]);
    speed = std::stof(values[5]);

    auto texture = ResourceManager::getTexture(name);
    if(texture)
        setTexture(texture->texture);
    else
        getSprite()->setColor({196, 135, 0, 255});

    setScale({32, 32});
}

Unit::Unit(Unit *other) :
        GameObject(other), maxHealth(other->maxHealth), health(other->health), price(other->price), speed(other->speed),
        attackCooldown(other->attackCooldown), damage(other->damage) {}

GameObject *Unit::clone() {
    return new Unit(this);
}

/**
 * @return current health of the unit
 */
int Unit::getHealth() const {
    return health;
}

/**
 * set the health of the unit
 * @param health 
 */
void Unit::setHealth(const int &health) {
    this->health = health;
}

/**
 * Behaviour when the unit starts. The health bar is created and it finds first target.
 */
void Unit::start() {
    GameObject::start();
    healthBar = new ProgressBar(getAbsolutePosition(), {64, 5});
    healthBar->setParent(this);
    healthBar->setRelativePosition({-16, -10});
    healthBar->getSprite()->setColor({0, 0, 0, 255});
    mapPosition = GameScene::map->screenToMap(getAbsolutePosition());
    
    if (!target)
        getNextTarget();
    
    pathToTarget = GameScene::map->findPath(mapPosition, GameScene::map->screenToMap(target->getAbsolutePosition()));
    nextPosition = pathToTarget.front();
    pathToTarget.pop_front();

    isMoving = true;
}

/**
 * Behaviour of each frame while the unit is active.
 * @param deltaTime 
 */
void Unit::update(const float &deltaTime) {
    if (!GameScene::map->baseTile->getStructure())
        return;
    GameObject::update(deltaTime);
    if (destroyed)
        return;

    if (isMoving)
        move(deltaTime);
    else if (atTarget)
        onStayingAtTarget(deltaTime);
    else
        onIdle();
}

void Unit::getNextTarget() {
    target = GameScene::map->getNearestLivingStructure(mapPosition);
}

/**
 * Move the unit to the next position.
 * @param deltaTime 
 */
void Unit::move(const double &deltaTime) {
    if (!target || target->isDestroyed()) {
        isMoving = false;
        atTarget = false;
        onIdle();
        return;
    }

    Vector2D moveVector =
            Vector2D::moveTowards(mapPosition, nextPosition).normalized() * 32 * speed * (float) deltaTime / 1000.0;

    if (Vector2D::distance(mapPosition, nextPosition) < 0.1) {
        if (pathToTarget.empty()) {
            onDestinationReached();
            return;
        }
        nextPosition = pathToTarget.front();
        pathToTarget.pop_front();
    }
    setAbsolutePosition({
                                getAbsolutePosition().x + moveVector.x,
                                getAbsolutePosition().y + moveVector.y
                        });
    mapPosition.x += moveVector.x / 32;
    mapPosition.y += moveVector.y / 32;
}


/**
 * Decrease health of this unit when damaged.
 * @param val the value to remove from the health
 */
void Unit::onDamage(const int &val) {
    health -= val;
    if (health <= 0) {
        health = 0;
        destroyed = true;
        GameScene::getPlayer()->unregisterUnit(this);
        Logger::info("Unit dead.");
    }
    healthBar->setValue((float) health / (float) maxHealth);
}

/**
 * Behaviour when the unit is idle (e.g. previous target has been destroyed).
 */
void Unit::onIdle() {
    getNextTarget();
    pathToTarget = GameScene::map->findPath(mapPosition, GameScene::map->screenToMap(target->getAbsolutePosition()));
    nextPosition = pathToTarget.front();
    pathToTarget.pop_front();
    if (!target) {
        this->destroyed = true;
        GameScene::getPlayer()->unregisterUnit(this);
    }
    isMoving = true;
}

/**
 * What to do when the destination (target) has been reached.
 */
void Unit::onDestinationReached() {
    isMoving = false;
    atTarget = true;
}

/**
 * What to do when the unit stays at the target. Default = attack the target.
 * @param deltaTime 
 */
void Unit::onStayingAtTarget(const float &deltaTime) {
    if (!target || target->isDestroyed()) {
        atTarget = false;
        return;
    }
    if (attackTimer <= 0) {
        target->onDamage(damage);
        if (target->isDestroyed())
            onTargetDestroyed();

        attackTimer = (float)attackCooldown;
    } else {
        attackTimer -= deltaTime;
    }
}

/**
 * What to do if the target has been destroyed. Default = Register score for the player and stop movement.
 */
void Unit::onTargetDestroyed() {
    GameScene::getPlayer()->registerScore(target->getDestroyScore());
    target = nullptr;
    isMoving = false;
    atTarget = false;

}

/**
 * Write data of the unit to the xml file.
 * @param writer
 */
void Unit::serialize(xmlTextWriterPtr &writer) {
    xmlTextWriterStartElement(writer, BAD_CAST name.c_str());
    
    xmlTextWriterWriteAttribute(writer, BAD_CAST "health", BAD_CAST std::to_string(health).c_str());
    xmlTextWriterWriteAttribute(writer, BAD_CAST "x", BAD_CAST std::to_string(getAbsolutePosition().x).c_str());
    xmlTextWriterWriteAttribute(writer, BAD_CAST "y", BAD_CAST std::to_string(getAbsolutePosition().y).c_str());
    
    xmlTextWriterEndElement(writer);
}
