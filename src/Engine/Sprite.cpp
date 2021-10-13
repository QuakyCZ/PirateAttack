//
// Created by KRATSTOM on 09.04.21.
//

#include "Sprite.h"

Sprite::Sprite(int w, int h, int x, int y, int r, int g, int b, int a) :
        position((float)x, (float)y), scale((float)w, (float)h) {
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
}

Sprite::Sprite(int w, int h, int x, int y, SDL_Texture *texture) {
    this->position = Vector2D(x,y);
    this->scale = Vector2D(w, h);
    this->texture = texture;
}

Sprite::Sprite(const Vector2D &position, const Vector2D &scale, SDL_Color &color):
        position(position),
        scale(scale),
        color(color) {}

Sprite::Sprite(const Vector2D & position, const Vector2D & scale, SDL_Texture * texture):
        position(position),
        scale(scale),
        texture(texture) {}


Sprite::Sprite(int x, int y, SDL_Texture *texture) :
        position(x, y) {
    setTexture(texture);
}

Sprite::Sprite(const Sprite & other):
        position(other.position),
        scale(other.scale),
        color(other.color),
        texture(other.texture),
        layer(other.layer),
        angle(other.angle)
{}

void Sprite::draw(SDL_Renderer *mRenderer) {
    if(!visible)
        return;
    auto rect = getSDLRect();
    if (texture) {
        //Logger::info("Drawing texture at " + std::to_string(x) + " "  + std::to_string(y) + " size " + std::to_string(width) + " " + std::to_string(height));
        SDL_RenderCopyEx(mRenderer, texture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
    } else {
        //Logger::info("Drawing Rectangle at " + std::to_string(x) + " "  + std::to_string(y) + " size " + std::to_string(width) + " " + std::to_string(height));
        SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(mRenderer, &rect);
    }
}

/**
 * Set the screen position of the sprite.
 * @param x x-pos
 * @param y y-pos
 */
void Sprite::setPosition(int x, int y) {
    this->position.x = x;
    this->position.y = y;
}

/**
 * Set the screen position of the sprite.
 * @param position Vector2D with position
 */
void Sprite::setPosition(const Vector2D &position) {
    this->position = position;
}

/**
 * @return Vector2D with the screen position of the sprite.
 */
Vector2D Sprite::getPosition() const {
    return this->position;
}

/**
 * Set texture to the sprite.
 * @param texture the texture
 */
void Sprite::setTexture(SDL_Texture *texture) {
    this->texture = texture;
}

/**
 * @return scale of the sprite
 */
Vector2D &Sprite::getScale() {
    return scale;
}

/**
 * Set scale of the sprite
 * @param width width in pixels
 * @param height height in pixels
 */
void Sprite::setScale(const int &width, const int &height) {
    //Logger::info("Sprite::setScale " + std::to_string(width) + " " + std::to_string(height));
    this->scale.x = width;
    this->scale.y = height;
}

/**
 * Set the color of the sprite.
 * @param color the co.
 */
void Sprite::setColor(const SDL_Color &color) {
    this->color = color;
}

/**
 * @return sdl rect with position and scale of the sprite
 */
SDL_Rect Sprite::getSDLRect() const {
    SDL_Rect rect;
    rect.h = (int)scale.y;
    rect.w = (int)scale.x;
    rect.x = (int)position.x;
    rect.y = (int)position.y;
    return rect;
}





