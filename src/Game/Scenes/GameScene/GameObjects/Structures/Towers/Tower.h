//
// Created by KRATSTOM on 10.04.21.
//
#pragma once

#include "Missiles/Missile.h"

class Tower : public LivingStructure {
private:    
    GameObject * towerRange = nullptr;
    void createRangeGameObject();
    void updateDefenseLevel(const int & amount) const;
protected:
    int price;
    int range = 0;
    int attack = 0;
    float chargeTime = 2000.0F;
    float chargeCooldown = 0;
    
    Vector2D mapPosition;
    Missile * missilePrefab = nullptr;
    void onHoverEnter() override;
    void onHoverExit() override;
public:
    explicit Tower(const std::string & name);
    explicit Tower(Tower * other);
    ~Tower() override;
    
    void start() override;
    void update(const float & deltaTime) override;
    GameObject * clone() override {
        return new Tower(this);
    }
    
    int getRange() const {
        return range;
    }
    
    int getPrice() const {
        return price;
    }
    
    void onDamage(const int &amount) override;
    
    void serialize(xmlTextWriterPtr & writer) override;
};
