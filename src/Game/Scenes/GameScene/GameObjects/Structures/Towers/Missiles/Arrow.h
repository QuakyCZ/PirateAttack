//
// Created by KRATSTOM on 01.06.21.
//

#pragma once
#include "Missile.h"
#include <cmath>
class Arrow: public Missile {
private:
protected:
    void onTargetReached() override;
public:
    Arrow(const int & maxDistance, const int & damage);
    Arrow(Arrow * other);
    
    GameObject * clone() override;
    
    void update(const float &deltaTime) override;
};


