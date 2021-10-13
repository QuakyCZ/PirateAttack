//
// Created by KRATSTOM on 09.04.21.
//

#pragma once

#include <vector>
#include <libxml2/libxml/encoding.h>
#include <libxml2/libxml/xmlwriter.h>

#include "Managers/AudioManager.h"
#include "Managers/ResourceManager.h"
#include "Sprite.h"

enum MouseState {
    NORMAL = 0,
    HOVER = 1,
    CLICKED = 2,
    DISABLED = 3
};

class GameObject {
private:
    Sprite sprite;
    Vector2D absolutePosition;
    Vector2D relativePosition;
    Vector2D scale;
    bool visible = true;

    void updatePosition();
    void updateLayer();

protected:
    bool destroyed = false;
    GameObject *parent = nullptr;
    std::vector<GameObject *> children;

    MouseState currentState = NORMAL;

    /**
     * Called when the button is pressed.
     */
    virtual void onClickEnter();

    /**
     * Called when the button is released.
     */
    virtual void onClickExit();

    virtual void onClick() {}

    /**
     * Called when the mouse entered the area of the game object.
     */
    virtual void onHoverEnter();

    /**
     * Called when the mouse left the area of the game object.
     */
    virtual void onHoverExit();


    /**
     * @return true if button is being hovered
     */
    bool isHovered();

    /**
     * @return true if button is not DISABLED
     */
    bool isEnabled() const;

    void destroy() {
        destroyed = true;
    }

public:
    /**
     * The name of this game object.
     */
    std::string name;

    /**
     * Creates empty game object. <br>
     * width = height = 10 <br>
     * x = y = 0 <br>
     * COLOR = Black
     */
    GameObject();

    /**
     * Creates empty game object with name. <br>
     * width = height = 10 <br>
     * x = y = 0 <br>
     * COLOR = Black
     * @param name the name of the game object
     */
    explicit GameObject(const std::string &name);

    GameObject(const std::string &name, const Vector2D &position, const Vector2D &scale);
    GameObject(GameObject * other);

    virtual ~GameObject();

    virtual GameObject * clone();
    
    virtual void start(){}

    virtual void pollEvent(SDL_Event &event);

    virtual void update(const float &deltaTime);

    void setTexture(SDL_Texture *texture);

    void setScale(const int &width, const int &height);

    void setScale(const Vector2D &scale);

    Vector2D getScale() const;

    void setAbsolutePosition(const Vector2D &position);

    void setRelativePosition(const Vector2D &position);

    Vector2D getAbsolutePosition() const;

    GameObject *getParent();

    void setParent(GameObject *parent);

    virtual void appendChild(GameObject *gameObject);
    
    std::vector<GameObject *> & getChildren() {
        return children;
    }
    GameObject * getChildByName(const std::string & name) const;

    Sprite *getSprite();

    void setVisibility(const bool &val);
    bool isVisible() const {
        return visible;
    }

    bool isDestroyed() const {
        return destroyed;
    }
    
    
    virtual void serialize(xmlTextWriterPtr & writer) {}
};