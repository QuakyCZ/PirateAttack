//
// Created by KRATSTOM on 21.05.21.
//

#include "Tooltip.h"
/**
 * Constructor of Tooltip.
 */
Tooltip::Tooltip(): VerticalLayoutGroup({10, 10}) {
    this->setVisibility(false);
}

/**
 * Add a text to the tooltip.
 * @param text a pointer to the text
 */
void Tooltip::addText(Text * text) {
    text->setParent(this);
}
