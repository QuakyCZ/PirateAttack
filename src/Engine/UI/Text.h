//
// Created by KRATSTOM on 13.04.21.
//

#pragma once

#include <string>
#include <SDL2/SDL_ttf.h>
#include "../GameObject.h"

class Text: public GameObject {
private:
    SDL_Surface * surface = nullptr;
    SDL_Renderer * renderer = nullptr;
    TTF_Font * font = nullptr;
    SDL_Color foreColor = {0, 0, 0, 255};
    int wrapWidth = -1;
    std::string text;

    void createTextSurface();
public:
    Text() = default;
    explicit Text(SDL_Renderer * renderer, const std::string & font, const std::string & text, const int & size, const int & wrapWidth = -1);
    explicit Text(SDL_Renderer * renderer, const std::string & font, const std::string & text, const int & size, const SDL_Color & foreColor, const int & wrapWidth);

    ~Text() override;

    std::string getText() const;
    void setText(const std::string & newText);

    void setForeColor(const SDL_Color & color);
};


