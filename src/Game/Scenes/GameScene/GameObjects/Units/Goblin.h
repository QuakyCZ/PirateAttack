//
// Created by KRATSTOM on 06.05.2021.
//

#pragma once
#include "Unit.h"

class Goblin: public Unit {
private:
public:
    static int count;
    Goblin();
    explicit Goblin(Goblin * other);
    GameObject * clone() override;
    void getNextTarget() override;
    void onTargetDestroyed() override;
};
