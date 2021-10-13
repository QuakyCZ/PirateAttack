//
// Created by KRATSTOM on 21.05.21.
//

#pragma once


#include "../../../../../Engine/GameObject.h"

class Structure : public GameObject {
public:
    Structure(): GameObject("Structure") {
        getSprite()->setLayer(10);
    }
    explicit Structure(Structure * other): GameObject(other) {}
    explicit Structure(const std::string & name): GameObject(name) {}
    GameObject * clone() override{
        return new Structure(this);
    }
};


