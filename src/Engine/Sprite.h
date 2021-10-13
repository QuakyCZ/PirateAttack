//
// Created by KRATSTOM on 09.04.21.
//

#pragma once

#include "Window.h"
#include "Vector2D.h"

#include <string>
class Sprite {
private:
    Vector2D position, scale, dock = {-1, -1};
    SDL_Color color = SDL_Color{255, 6, 162, 255};
    SDL_Texture * texture = nullptr;
    int layer = 0;
    int angle = 0;
public:
    Sprite() = default;
    Sprite(const Vector2D & position, const Vector2D & scale, SDL_Color & color);
    Sprite(const Vector2D & position, const Vector2D & scale, SDL_Texture * texture);
    Sprite(int w, int h, int x, int y, int r, int g, int b, int a );
    Sprite(int w, int h, int x, int y, SDL_Texture * texture);
    Sprite(int x, int y, SDL_Texture * texture);
    Sprite(const Sprite & other);

    bool visible = true;
    
    void draw(SDL_Renderer * renderer);

    void setPosition(int x, int y);
    void setPosition(const Vector2D & position);
    Vector2D getPosition() const;
    
    void setAngle(const int & value) {
        angle = value;
    }
    
    void setLayer(const int & val) {
        layer = val;
    }
    
    int getLayer() const {
        return layer;
    }

    void setColor(const SDL_Color & color);
    
    void setTexture(SDL_Texture * texture);

    Vector2D & getScale();
    void setScale(const int & width, const int & height);

    SDL_Rect getSDLRect() const;
};
