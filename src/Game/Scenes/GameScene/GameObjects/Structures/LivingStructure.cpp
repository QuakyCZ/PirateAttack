//
// Created by KRATSTOM on 21.05.21.
//

#include "LivingStructure.h"

LivingStructure::LivingStructure(const int &health, const int & destroyScore)
: Structure(), maxHealth(health), health(health), destroyScore(destroyScore) {}

LivingStructure::LivingStructure(LivingStructure *other)
: Structure(other), maxHealth(other->maxHealth), health(other->health), destroyScore(other->destroyScore) {
    if(other->healthBar)
        healthBar = new ProgressBar(other->healthBar);
}

/**
 * Creates health bar above the structure.
 */
void LivingStructure::start() {
    if(!healthBar) {
        healthBar = new ProgressBar({-40, -10}, {80, 5});
        healthBar->getSprite()->setColor({0, 0, 0, 255});
        healthBar->setParent(this);
        healthBar->setRelativePosition({-24, -20});
    }
}

/**
 * Take damage and show current health on the health bar.
 * @param amount the amount of health to take
 */
void LivingStructure::onDamage(const int & amount) {
    if(destroyed)
        return;
    health -= amount;
    if(health <= 0) {
        health = 0;
        onDestroy();
        return;
    }
    healthBar->setValue((float)health / (float)maxHealth);
}

/**
 * When the health is 0.
 */
void LivingStructure::onDestroy() {
    
    destroyed = true;
    setVisibility(false);
}

