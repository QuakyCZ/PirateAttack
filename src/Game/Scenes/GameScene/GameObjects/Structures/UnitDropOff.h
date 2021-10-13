//
// Created by KRATSTOM on 21.05.21.
//

#pragma once


#include "Structure.h"


class UnitDropOff: public Structure {
private:
    GameObject * circle = nullptr;
protected:
    void onClick() override;
public:
    UnitDropOff();
    void update(const float & deltaTime) override;
};


