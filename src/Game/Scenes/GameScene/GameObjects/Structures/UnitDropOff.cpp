//
// Created by KRATSTOM on 21.05.21.
//

#include "UnitDropOff.h"
#include "../../GameScene.h"

/**
 * Create a circle for unit summoning
 */
UnitDropOff::UnitDropOff(): Structure() {
    auto circleTexture = ResourceManager::getTexture("circle");
    if(!circleTexture)
        return;

    circle = new GameObject();
    circle->setTexture(circleTexture->texture);
    circle->setScale({64, 64});
    circle->setParent(this);
    circle->setRelativePosition({-16, -16});
}


/**
 * Summon a unit.
 */
void UnitDropOff::onClick() {
    GameObject::onClick();
    GameScene::getPlayer()->completeSummoning(GameScene::map, getAbsolutePosition());
}

/**
 * If player is summoning, show the circle.
 * @param deltaTime 
 */
void UnitDropOff::update(const float &deltaTime) {
    GameObject::update(deltaTime);
    if(circle)
        circle->setVisibility(GameScene::getPlayer()->isSummoning());
}



