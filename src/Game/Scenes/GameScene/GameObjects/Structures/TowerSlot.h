//
// Created by KRATSTOM on 21.05.21.
//

#pragma once

#include "Towers/Tower.h"
class TowerSlot: public Structure {
private:
    Tower * tower = nullptr;
public:
    TowerSlot();
    void buildTower(Tower * newTower);
    bool hasTower() const {
        return tower != nullptr;
    }
    Tower * getTower() {
        return tower;
    }
    
    void update(const float & deltaTime) override;
    
    void serialize(xmlTextWriterPtr & writer) override;
};



