//
// Created by KRATSTOM on 21.05.21.
//

#include "MonsterButton.h"
#include "../../GameScene.h"

/**
 * A button for unit summoning.
 * @param renderer 
 * @param monsterName the name of the monster 
 * @param position the absolute position of the button
 * @param scale the scale of the button
 */
MonsterButton::MonsterButton(SDL_Renderer * renderer, const std::string &monsterName, const Vector2D & position, const Vector2D & scale)
: Button("button_"+monsterName, position, scale ), monsterName(monsterName) {
    tooltip = new Tooltip();
    tooltip->getSprite()->setColor({97, 54, 14, 255});
    tooltip->setParent(this);
    tooltip->setSpacing({5,5});

    auto nameText = new Text(renderer, "Torii", monsterName, 20);
    tooltip->addText(nameText);
    nameText->setForeColor({255,255,255,255});
    auto values = ResourceManager::getConfig("units").getValues(monsterName);
    auto price = values[1];
    
    auto moneyText = new Text(renderer, "Torii", "$" + price, 14);
    
    tooltip->addText(moneyText);
    moneyText->setForeColor({255,255,255,255});
        
    auto maxAmountText = new Text(renderer, "Torii", "MAX: " + std::to_string(GameScene::getPlayer()->getMaxCountOfUnit(monsterName)), 14);
    tooltip->addText(maxAmountText);
    
    tooltip->setRelativePosition({0, -(tooltip->getScale().y) - 5});
}

/**
 * Show tooltip.
 */
void MonsterButton::onHoverEnter() {
    Button::onHoverEnter();
    if(tooltip)
        tooltip->setVisibility(true);
}

/**
 * Close tooltip.
 */
void MonsterButton::onHoverExit() {
    Button::onHoverExit();
    if(tooltip)
        tooltip->setVisibility(false);
}

/**
 * Start summoning a unit.
 */
void MonsterButton::onClick() {
    Button::onClick();
    GameScene::getPlayer()->summon(monsterName);
}


