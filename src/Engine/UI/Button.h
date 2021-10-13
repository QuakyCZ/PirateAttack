//
// Created by KRATSTOM on 10.04.21.
//

#pragma once

#include <functional>
#include <map>
#include "../GameObject.h"



class Button : public GameObject {
private:

    /**
     * Vector with callbacks to call.
     */
    std::vector<std::function<void()>> callbacks;
    std::map<MouseState, SDL_Texture *> stateTextures;
protected:
    /**
     * Called when the button is pressed.
     */
    void onClickEnter() override;

    /**
     * Called when the button is released.
     */
    void onClick() override;

    /**
     * Called when the mouse entered the area of the button.
     */
    void onHoverEnter() override;

    /**
     * Called when the mouse left the area of the button.
     */
    void onHoverExit() override;

public:
    /**
     * The default constructor.
     * Creates basic game object with blank name.
     */
    Button();

    /**
     * Create game object with provided name.
     * @param name the name of the button
     */
    explicit Button(const std::string & name);

    Button(const std::string & name, const Vector2D & position, const Vector2D & scale);

    /**
     * Register callback that will be handled on click
     * @param callback the callback to call when the button is clicked
     */
    void registerCallback(const std::function<void()>& callback);


    /**
     * Set button texture for the state.
     * @param state the state of the button
     * @param texture the texture
     */
    void setTexture(const MouseState & state, SDL_Texture * texture);




    /**
     * Set state to NORMAL or DISABLED. <br>
     * If DISABLED, button cannot be clicked.
     * @param state new state
     */
    void setEnabled(const bool & state);
};