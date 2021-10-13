//
// Created by KRATSTOM on 10.04.21.
//

#include "../../../GameScene.h"
#include "Tower.h"

Tower::Tower(const std::string & name): LivingStructure(0, 200) {
    this->name = name;
    auto config = ResourceManager::getConfig("towers");
    auto values = config.getValues(name);
    if(values.size() < 5)
        throw std::invalid_argument("Not enough values in the config for tower " + name);

    price = std::stoi(values[0]);
    maxHealth = std::stoi(values[1]);
    health = maxHealth;
    range = std::stoi(values[2]);
    attack = std::stoi(values[3]);
    chargeCooldown = std::stof(values[4]);
}

Tower::Tower(Tower * other)
: LivingStructure(other), price(other->price), range(other->range), attack(other->attack), chargeTime(other->chargeTime) {
    towerRange = getChildByName("tower_range");
    missilePrefab = other->missilePrefab;
}

Tower::~Tower() {
    delete missilePrefab;
}

/**
 * Creates a circle around the tower that shows the range of the tower.
 */
void Tower::createRangeGameObject() {
    auto texture = ResourceManager::getTexture("tower_range");
    if(!texture)
        return;
    towerRange = new GameObject("tower_range");
    towerRange->setTexture(texture->texture);
    towerRange->setScale({(1 + 2.0F * (float)range) * texture->originalScale.x, (1 + 2.0F * (float)range) * texture->originalScale.y});
    towerRange->setParent(this);
    towerRange->setRelativePosition(((towerRange->getScale() / 2) * -1) + (getScale() / 2));
    towerRange->setVisibility(false);
    towerRange->getSprite()->setLayer(3);
}

/**
 * Update defense level of near tiles.
 * @param amount amount of the defense level to change
 */
void Tower::updateDefenseLevel(const int &amount) const{
    for(int y = (int)mapPosition.y - getRange(); y <= (int)mapPosition.y + getRange(); ++y) {
        for(int x = (int)mapPosition.x - getRange(); x <= (int)mapPosition.x + getRange(); ++x) {
            try {
                GameScene::map->getTileAt({(float)x,(float)y})->changeDefenseLevel(amount);
            } catch(std::invalid_argument & e) {
                continue;
            }
        }
    }
}

/**
 * Prepares the tower.
 */
void Tower::start() {
    LivingStructure::start();
    mapPosition = GameScene::map->screenToMap(getAbsolutePosition());
    if(mapPosition == Vector2D(-1,-1)) {
        destroy();
        return;
    }
    updateDefenseLevel(5);
    if(!towerRange)
        createRangeGameObject();
    chargeCooldown = chargeTime;
}

/**
 * Check if any unit is in the tower's range. If so, shoot.
 * @param deltaTime 
 */
void Tower::update(const float &deltaTime) {
    if(destroyed)
        return;
    Structure::update(deltaTime);
    if(!missilePrefab) {
        Logger::warn("Tower has not assigned missile prefab! Aborting shot.");
    }
    if(chargeCooldown <= 0) {
        auto units = GameScene::getPlayer()->getUnits();
        for(auto unit : units) {
            if (!unit) {
                continue;
            }
            if((Vector2D::distance(getAbsolutePosition(), unit->getAbsolutePosition()) / 32.0F) <= (float)range) {
                chargeCooldown = chargeTime;
                Logger::info( "Shoot.");
                auto missile = dynamic_cast<Missile*>(missilePrefab->clone());
                missile->setTarget(unit);
                missile->setParent(this);
                missile->start();
                break;
            }
        }
    } else {
        chargeCooldown -= deltaTime;
    }
}

/**
 * Show the circle of tower's range.
 */
void Tower::onHoverEnter() {
    GameObject::onHoverEnter();
    if(towerRange)
        towerRange->setVisibility(true);
}

/**
 * Hide the circle of tower's range.
 */
void Tower::onHoverExit() {
    GameObject::onHoverExit();
    if(towerRange)
        towerRange->setVisibility(false);
}

/**
 * Take damage.
 * @param amount the amount of damage to take.
 */
void Tower::onDamage(const int &amount) {
    LivingStructure::onDamage(amount);
    if(destroyed)
        updateDefenseLevel(-10);
}

/**
 * Save the tower to the xml file.
 * @param writer the writer of the xml file
 */
void Tower::serialize(xmlTextWriterPtr &writer) {
    xmlTextWriterStartElement(writer, BAD_CAST name.c_str());
    xmlTextWriterWriteAttribute(writer, BAD_CAST "x", BAD_CAST std::to_string(getAbsolutePosition().x).c_str());
    xmlTextWriterWriteAttribute(writer, BAD_CAST "y", BAD_CAST std::to_string(getAbsolutePosition().y).c_str());
    xmlTextWriterWriteAttribute(writer, BAD_CAST "health", BAD_CAST std::to_string(health).c_str());
    xmlTextWriterEndElement(writer);
}

