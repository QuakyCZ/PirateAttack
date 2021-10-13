//
// Created by KRATSTOM on 15.04.21.
//

#include "VerticalLayoutGroup.h"

VerticalLayoutGroup::VerticalLayoutGroup(const Vector2D &spacing): GameObject(), spacing(spacing)
{}

VerticalLayoutGroup::VerticalLayoutGroup(const std::string &name, Vector2D & position, Vector2D & scale, Vector2D & spacing):
    GameObject(name, position, scale),
    spacing(spacing)
{}

/**
 * Set spacing around game objects
 * @param nSpacing the vector of spacing
 */
void VerticalLayoutGroup::setSpacing(const Vector2D &nSpacing) {
    // TODO: update positions of all children after updating spacing
    this->spacing = nSpacing;
}

/**
 * Set x value of spacing 
 * @param x value
 */
void VerticalLayoutGroup::setSpacingX(float &x) {
    // TODO: update positions of all children after updating spacing X
    this->spacing.x = x;
}

/**
 * Set y value of spacing
 * @param y value
 */
void VerticalLayoutGroup::setSpacingY(float &y) {
    // TODO: update positions of all children after updating spacing Y
    this->spacing.y = y;
}

/**
 * Add a child to the VGroup and set the right absolute position to it.
 * @param child 
 */
void VerticalLayoutGroup::appendChild(GameObject *child) {
    GameObject::appendChild(child);

    Vector2D newPos = child->getAbsolutePosition();
    newPos.y += currentHeight + spacing.y;
    auto childScale = child->getSprite()->getScale();

    currentHeight += childScale.y + 2 * spacing.y;
    newPos.x += spacing.x;
    child->setAbsolutePosition(newPos);

    auto myScale = getScale();
    if(childScale.x + 2*spacing.x > myScale.x)
        myScale.x = childScale.x + 2*spacing.x;

    myScale.y = currentHeight;
    Logger::info(myScale.toString());
    setScale(myScale);
}










