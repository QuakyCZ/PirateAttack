//
// Created by KRATSTOM on 31.05.21.
//

#pragma once

#include "LivingStructure.h"
class Base: public LivingStructure {
protected:
    void onDestroy() override;    
public:
    Base(): LivingStructure(100, 1000) {}
    void serialize(xmlTextWriterPtr & writer);
};


