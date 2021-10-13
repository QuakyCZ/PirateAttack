//
// Created by KRATSTOM on 28.05.21.
//

#pragma once
#include "Missile.h"

class Bomb: public Missile {
private:
    float range = 4;
protected:
    void onTargetReached() override;
    void onMaxDistanceReached() override;
public:
    Bomb() = delete;
    explicit Bomb(const int & maxDistance, const int & attackDamage);
    explicit Bomb(Bomb * other);
    GameObject * clone() override;
    
    void start() override;
};


