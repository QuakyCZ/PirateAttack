//
// Created by KRATSTOM on 09.04.21.
//

#pragma once

#include "Logger/Logger.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class Window {
private:
    const int WIDTH = 1920;
    const int HEIGHT = 1080;
    SDL_Window * window = nullptr;
    SDL_Renderer * renderer = nullptr;

public:
    Window();
    ~Window();
    SDL_Renderer * getRenderer() const {
        return this->renderer;
    }

    void setIcon(SDL_Surface * surface);

    void clear();
    void render();

    bool isFocused() const;
};
