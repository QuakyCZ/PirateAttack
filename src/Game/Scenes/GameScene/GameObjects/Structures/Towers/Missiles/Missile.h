//
// Created by KRATSTOM on 28.05.21.
//

#pragma once
#include "../../../Units/Unit.h"

class Missile: public GameObject {
private:
    Vector2D startingPosition;
    int maxDistance;
    float speed = 2.5;
protected:
    Unit * target = nullptr;
    Vector2D targetPosition;
    int damage = 5;
    virtual void onTargetReached();
    virtual void onMaxDistanceReached();
public:
    Missile() = delete;
    explicit Missile(const int & maxDistance, const int & damage);
    explicit Missile(Missile * other);
    
    GameObject * clone() override;
    
    void setTarget(Unit * newTarget);
    void setTarget(const Vector2D & newTarget);
    
    void start() override;
    void update(const float &deltaTime) override;
};


