//
// Created by KRATSTOM on 21.05.21.
//

#pragma once
#include "../../../../../Engine/UI/Button.h"
#include "../Units/Unit.h"
#include "Tooltip.h"

class MonsterButton: public Button {
private:
    Tooltip * tooltip = nullptr;
    int amount = 0;
protected:
    std::string monsterName;
    void onClick() override;
    void onHoverEnter() override;
    void onHoverExit() override;
public:
    MonsterButton() = delete;
    MonsterButton(SDL_Renderer * renderer, const std::string & monsterName, const Vector2D & position, const Vector2D & scale);
};


