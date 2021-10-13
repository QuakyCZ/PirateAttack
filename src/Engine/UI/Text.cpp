//
// Created by KRATSTOM on 13.04.21.
//

#include "Text.h"
#include "../Managers/ResourceManager.h"

Text::Text(SDL_Renderer *renderer, const std::string &font, const std::string &text, const int &size, const int &wrapWidth)
:GameObject("Text_" + text), renderer(renderer), font(ResourceManager::getFont(font, size)), wrapWidth(wrapWidth), text(text) {
    createTextSurface();
}

Text::Text(SDL_Renderer * renderer, const std::string &fontName, const std::string &text, const int & size, const SDL_Color & foreColor, const int & wrapWidth)
: Text(renderer, fontName, text, size, wrapWidth) {
    this->foreColor = foreColor;
}

Text::~Text() {
    if(font)
        TTF_CloseFont(font);
    if(surface)
        SDL_FreeSurface(surface);
}

/**
 * Creates a surface from current text properties (text, fore color, size).
 */
void Text::createTextSurface() {
    if(!font) {
        Logger::severe("Text " + text + " has null font!");
        return;
    }

    if(surface)
        SDL_FreeSurface(surface);
    if(wrapWidth > 0)
        surface = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), foreColor, wrapWidth);
    else
        surface = TTF_RenderUTF8_Blended(font, text.c_str(), foreColor);

    setTexture(SDL_CreateTextureFromSurface(renderer, surface));
    setScale(surface->w, surface->h);
}

/**
 * @return the text that is currently displayed
 */
std::string Text::getText() const {
    return text;
}

/**
 * Set new text
 * @param newText the text to display
 */
void Text::setText(const std::string & newText) {
    this->text = newText;
    createTextSurface();
}

/**
 * Set new fore color
 * @param color new fore color
 */
void Text::setForeColor(const SDL_Color & color) {
    this->foreColor = color;
    createTextSurface();
}