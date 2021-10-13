//
// Created by KRATSTOM on 09.04.21.
//

#include "GameObject.h"

GameObject::GameObject() :
        name("Blank GameObject") {}


GameObject::GameObject(const std::string &name) :
        sprite(10, 10, 0, 0, 0, 0, 0, 255),
        name(name) {}

GameObject::GameObject(const std::string &name, const Vector2D &position, const Vector2D &scale) :
        sprite(position, scale, nullptr),
        name(name) {
    setAbsolutePosition(position);
    setScale(scale);
}

/**
 * The copy constructor of the game object
 * @param other the game object to copy
 */
GameObject::GameObject(GameObject *other) :
        sprite(other->sprite),
        absolutePosition(other->absolutePosition),
        relativePosition(other->relativePosition),
        scale(other->scale),
        visible(other->visible),
        children(other->children),
        name(other->name) {
    parent = other->parent;
}


GameObject::~GameObject() {
    for (auto *go : children) {
        delete go;
    }
    children.clear();
}

/**
 * @return a deep copy of the game object
 */
GameObject *GameObject::clone() {
    return new GameObject(this);
}

/**
 * handle user's input
 * @param event the user event
 */
void GameObject::pollEvent(SDL_Event &event) {
    if (currentState == DISABLED)
        return;
    switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            onClickEnter();
            break;
        case SDL_MOUSEBUTTONUP:
            onClickExit();
            break;
    }
    for (GameObject *go : children) {
        go->pollEvent(event);
    }
}

/**
 * Checks the MouseState and updates children. If any child is destroyed, it is also removed from children.
 * @param deltaTime 
 */
void GameObject::update(const float &deltaTime) {
    if (currentState == DISABLED)
        return;

    bool hovered = isHovered();
    if (hovered && currentState < HOVER) {
        onHoverEnter();
    } else if (!hovered && currentState == HOVER) {
        onHoverExit();
    }

    for (auto it = children.begin(); it != children.end(); ++it) {
        auto gameObject = *it;
        gameObject->update(deltaTime);
        if (gameObject->isDestroyed()) {
            delete gameObject;
            children.erase(it);
            --it;
        }
    }
}

/**
 * Assigns a texture to the sprite.
 * @param texture 
 */
void GameObject::setTexture(SDL_Texture *texture) {
    sprite.setTexture(texture);
}

/**
 * Assign the scale of the game object
 * @param width new width
 * @param height new height
 */
void GameObject::setScale(const int &width, const int &height) {
    scale.x = (float) width;
    scale.y = (float) height;
    sprite.setScale(width, height);
}

/**
 * Assign the scale of the game object
 * @param newScale a vector with the new scale
 */
void GameObject::setScale(const Vector2D &newScale) {
    setScale((int) newScale.x, (int) newScale.y);
}

/**
 * @return the scale of the game object
 */
Vector2D GameObject::getScale() const {
    return scale;
}

/**
 * Set absolute position of the game object on the screen.
 * @param position a vector with new position
 */
void GameObject::setAbsolutePosition(const Vector2D &position) {
    this->absolutePosition = position;
    if (parent)
        this->relativePosition = position - parent->getAbsolutePosition();
    else
        this->relativePosition = position;

    this->sprite.setPosition(position);
    for (auto go : children)
        go->updatePosition();
}

/**
 * @return the absolute position of the game object
 */
Vector2D GameObject::getAbsolutePosition() const {
    return this->absolutePosition;
}

/**
 * Set relative position to parent of the game object. Updates absolute position and also positions of all children. 
 * @param position vector of new position
 */
void GameObject::setRelativePosition(const Vector2D &position) {
    relativePosition = position;
    updatePosition();
}

/**
 * Updates positions of all children.
 */
void GameObject::updatePosition() {
    setAbsolutePosition(parent->getAbsolutePosition() + relativePosition);
    for (auto go : children)
        go->updatePosition();
}

/**
 * Increment the layer of the game object and his children by one.
 */
void GameObject::updateLayer() {
    getSprite()->setLayer(parent->getSprite()->getLayer() + 1);
    for(auto child : children)
        child->updateLayer();
}


/**
 * @return parent game object of the game object or nullptr
 */
GameObject *GameObject::getParent() {
    return parent;
}

/**
 * Set parent for the game object. Updates relative position of the game object the to 0 vector.
 * @param parent a pointer to the parent
 */
void GameObject::setParent(GameObject *parent) {
    if(!parent) {
        this->parent = nullptr;
        return;
    }
    parent->appendChild(this);
    this->absolutePosition += parent->getAbsolutePosition();
    this->sprite.setPosition(this->absolutePosition);
    this->parent = parent;
    updateLayer();
}

/**
 * Add a child to the game object
 * @param child a game object to add as child
 */
void GameObject::appendChild(GameObject * child) {
    children.push_back(child);
}

/**
 * @param name the name of the game object
 * @return game object with the name that is direct child of the game object or nullptr if it was not found.
 */
GameObject * GameObject::getChildByName(const std::string &name) const {
    for(auto child : children) {
        if(child->name == name)
            return child;
    }
    return nullptr;
}

/**
 * @return a pointer to the sprite of the game object
 */
Sprite *GameObject::getSprite() {
    return &sprite;
}

/**
 * Toggle visibility of the game object. It affects all children.
 * @param val the value of visibility
 */
void GameObject::setVisibility(const bool &val) {
    this->visible = val;
    sprite.visible = val;
}

void GameObject::onClickEnter() {
    if (!isHovered())
        return;
    if (currentState >= CLICKED)
        return;
    currentState = CLICKED;
}

void GameObject::onClickExit() {
    if (isHovered()) {
        onHoverEnter();
        onClick();
    } else {
        onHoverExit();
    }
}

void GameObject::onHoverEnter() {
    if (!isEnabled())
        return;

    if (currentState != HOVER) {
        currentState = HOVER;
    }
}

void GameObject::onHoverExit() {
    currentState = NORMAL;
}

bool GameObject::isHovered() {
    SDL_Point p;
    SDL_GetMouseState(&p.x, &p.y);

    auto sdlSprite = getSprite()->getSDLRect();
    return SDL_PointInRect(&p, &sdlSprite);
}

/**
 * @return true if button is not DISABLED
 */
bool GameObject::isEnabled() const {
    return currentState != DISABLED;
}



