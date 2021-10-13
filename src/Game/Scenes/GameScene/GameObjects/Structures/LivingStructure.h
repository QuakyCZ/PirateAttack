//
// Created by KRATSTOM on 21.05.21.
//

#pragma once
#include "Structure.h"
#include "../../../../../Engine/UI/ProgressBar.h"

class LivingStructure: public Structure {
private:
    ProgressBar * healthBar = nullptr;
protected:
    int maxHealth = 20;
    int health;
    int destroyScore = 100;
    virtual void onDestroy();
public:
    LivingStructure() = delete;
    LivingStructure(const int & health, const int & destroyScore);
    explicit LivingStructure(LivingStructure * other);

    GameObject * clone() override {
        return new LivingStructure(this);
    }
    
    int getHealth() const {
        return health;
    }
    
    int getDestroyScore() const {
        return destroyScore;
    }
    
    void start() override;
    
    
    virtual void onDamage(const int & amount);
    void setHealth(const int & val) {
        health = val;
        healthBar->setValue((float)health/(float)maxHealth);
        if(health <= 0) {
            health = 0;
            onDestroy();
        }
    }
};


