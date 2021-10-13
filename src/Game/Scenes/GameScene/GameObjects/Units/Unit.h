//
// Created by KRATSTOM on 06.05.2021.
//

#pragma once

#include "../Structures/LivingStructure.h"

#include <list>

class Unit : public GameObject {
protected:
    int maxAmount = 5;
    int maxHealth = 10;
    int health = 10;
    int price = 10;
    float speed = 2;
    int attackCooldown = 2000;
    float attackTimer = 0;
    int damage = 2;
    std::list<Vector2D> pathToTarget;
    Vector2D nextPosition;
    Vector2D mapPosition = {-1, -1};
    ProgressBar *healthBar = nullptr;
    LivingStructure *target = nullptr;
    bool isMoving = false;
    bool atTarget = false;

    void move(const double &deltaTime);
    
    virtual void getNextTarget();

    virtual void onIdle();

    virtual void onDestinationReached();

    virtual void onStayingAtTarget(const float &deltaTime);

    virtual void onTargetDestroyed();

public:
    Unit(const std::string &name);

    explicit Unit(Unit *other);

    GameObject *clone() override;

    int getHealth() const;

    void setHealth(const int &health);

    /**
     * @return the summon price of the unit
     */
    int getPrice() const {
        return price;
    }

    int getMaxAmount() const {
        return maxAmount;
    }
    
    void setMaxAmount(const int & val) {
        maxAmount = val;
    }

    void setTarget(LivingStructure *newTarget) {
        target = newTarget;
    }

    void start() override;

    void update(const float &deltaTime) override;

    void onDamage(const int &val);
    
    
    void serialize(xmlTextWriterPtr &writer) override;
};
