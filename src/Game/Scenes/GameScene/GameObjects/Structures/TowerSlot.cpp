//
// Created by KRATSTOM on 21.05.21.
//

#include "TowerSlot.h"

TowerSlot::TowerSlot(): Structure("TowerSlot") {
    auto texture = ResourceManager::getTexture("tower_slot");
    if(texture)
        setTexture(texture->texture);
    setScale({32,32});
}

/**
 * Build a tower on the slot
 * @param newTower a pointer to the tower
 */
void TowerSlot::buildTower(Tower * newTower)  {
    this->tower = newTower;
    this->tower->setParent(this);
    this->tower->start();
}

/**
 * Check if the tower has been destroyed. If so, clear the pointer.
 * @param deltaTime 
 */
void TowerSlot::update(const float &deltaTime) {
    for(auto child : children) {
        child->update(deltaTime);
    }
    
    if(tower && tower->isDestroyed()) {
        
        tower = nullptr;
    }
}

/**
 * Save tower to the xml file.
 * @param writer the writer of the xml file
 */
void TowerSlot::serialize(xmlTextWriterPtr &writer) {
    if(tower)
        tower->serialize(writer);
}


 