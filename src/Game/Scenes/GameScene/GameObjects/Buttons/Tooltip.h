//
// Created by KRATSTOM on 21.05.21.
//

#pragma once
#include "../../../../../Engine/UI/VerticalLayoutGroup.h"
#include "../../../../../Engine/UI/Text.h"

/**
 * Tooltip is GameObject with background and text. By default, tooltip is hidden.
 */
class Tooltip: public VerticalLayoutGroup {
public:
    Tooltip();
    void addText(Text * text);
};


