//
// Created by KRATSTOM on 10.04.21.
//

#include "Button.h"

/**
 * The default constructor.
 * Creates basic game object with blank name.
 */
Button::Button() : GameObject("Blank Button") {}


/**
 * Create game object with provided name.
 * @param name the name of the button
 */
Button::Button(const std::string & name) : GameObject(name) {}

Button::Button(const std::string & name, const Vector2D &position, const Vector2D &scale):
        GameObject(name, position, scale)
{}

/**
 * Called when the button is pressed.
 */
void Button::onClickEnter() {
    GameObject::onClickEnter();
    if(!isHovered())
        return;
    if (stateTextures.find(CLICKED) != stateTextures.end())
        getSprite()->setTexture(stateTextures[CLICKED]);
}

/**
 * Called when the button is released.
 */
void Button::onClick() {
    GameObject::onClick();
    for (auto &callback : callbacks) {
        callback();
    }
}

/**
 * Called when the mouse entered the area of the button.
 */
void Button::onHoverEnter() {
    GameObject::onHoverEnter();

    if (stateTextures.find(HOVER) != stateTextures.end())
        GameObject::setTexture(stateTextures[HOVER]);

    AudioManager::playSound("button_hover");
}

/**
 * Called when the mouse left the area of the button.
 */
void Button::onHoverExit() {
    GameObject::onHoverExit();
    if (stateTextures.find(NORMAL) != stateTextures.end())
        GameObject::setTexture(stateTextures[NORMAL]);
}



/**
 * Register callback that will be handled on click
 * @param callback the callback to call when the button is clicked
 */
void Button::registerCallback(const std::function<void()> &callback) {
    callbacks.push_back(callback);
}

/**
 * Set button texture for the state.
 * @param state the state of the button
 * @param texture the texture
 */
void Button::setTexture(const MouseState &state, SDL_Texture *texture) {
    if (state == currentState) {
        getSprite()->setTexture(texture);
    }
    auto it = stateTextures.find(state);
    if (it == stateTextures.end())
        stateTextures.insert(std::pair<MouseState, SDL_Texture *>(state, texture));
    else
        it->second = texture;
}



/**
 * Set state to NORMAL or DISABLED. <br>
 * If DISABLED, button cannot be clicked.
 * @param state new state
 */
void Button::setEnabled(const bool &state) {
    currentState = state ? NORMAL : DISABLED;
}







