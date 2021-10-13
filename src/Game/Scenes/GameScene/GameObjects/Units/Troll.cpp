//
// Created by KRATSTOM on 06.05.2021.
//

#include "Troll.h"

Troll::Troll(): Unit("troll") {}

Troll::Troll(Troll *other): Unit(other) {}

GameObject *Troll::clone() {
    return new Troll(this);
}
