//
// Created by KRATSTOM on 21.05.21.
//

#pragma once


#include "../GameObject.h"

class ProgressBar: public GameObject {
public:
    enum Direction {
        LEFT_RIGHT,
        BOTTOM_UP
    };
    ProgressBar() = delete;
    ProgressBar(const Vector2D & pos, const Vector2D & scale, const float & startingVal = 1);
    ProgressBar(ProgressBar * other) {
        value = other->value;
        valueBar = other->valueBar->clone();
        direction = other->direction;
    }
    void setValue(const float & val);
    float getValue() const;

private:
    float value = 1;
    GameObject * valueBar = nullptr;
    Direction direction = LEFT_RIGHT;
};
