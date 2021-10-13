//
// Created by KRATSTOM on 15.04.21.
//

#pragma once
#include "../GameObject.h"

class VerticalLayoutGroup: public GameObject {
private:
    Vector2D spacing{0,0};
    float currentHeight = 0;
public:
    explicit VerticalLayoutGroup(const Vector2D & spacing);
    VerticalLayoutGroup(const std::string & name, Vector2D & position, Vector2D & scale, Vector2D & spacing);

    void setSpacing(const Vector2D & nSpacing);

    void setSpacingX(float & x);

    void setSpacingY(float & y);

    void appendChild(GameObject * child) override;
};