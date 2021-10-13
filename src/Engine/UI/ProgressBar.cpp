//
// Created by KRATSTOM on 21.05.21.
//

#include "ProgressBar.h"


ProgressBar::ProgressBar(const Vector2D & pos, const Vector2D & scale, const float & startingVal)
: GameObject("ProgressBar", pos, scale) {
    valueBar = new GameObject("ProgressBar Value", pos, scale);
    valueBar->getSprite()->setColor({255,0,0,255});
    valueBar->setParent(this);
    valueBar->getSprite()->setLayer(100);
    valueBar->setRelativePosition({0,0});
    getSprite()->setLayer(50);
    setValue(startingVal);
}

/**
 * Set value and update sprite size.
 * @param val number between 0 and 1.
 */
void ProgressBar::setValue(const float &val) {
    if(val < 0)
        value = 0;
    else if(val > 1)
        value = 1;
    else
        value = val;
    if(direction == LEFT_RIGHT)
        valueBar->setScale({std::ceil(getScale().x * value), getScale().y});
    else
        valueBar->setScale({getScale().x,std::ceil(getScale().y * value)});
}

/**
 * @return current value of the bar (between 0 and 1)
 */
float ProgressBar::getValue() const {
    return value;
}
