//
// Created by KRATSTOM on 06.05.2021.
//

#pragma once
#include "Unit.h"

class Troll: public Unit {
private:
public:
    Troll();
    explicit Troll(Troll * other);
    GameObject * clone() override;
};
