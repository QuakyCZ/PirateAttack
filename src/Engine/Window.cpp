//
// Created by KRATSTOM on 09.04.21.
//

#include "Window.h"

/**
 * Constructor of window.
 */
Window::Window() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow(
            "Pirate Attack",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WIDTH,
            HEIGHT,
            SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN
            );
    if(window == nullptr)
        throw std::runtime_error("Window initialization failed.");


    renderer = SDL_CreateRenderer(window, 1, 0);
    if(renderer == nullptr) {
        throw std::runtime_error("Renderer initialization failed.");
    }

    SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
        throw std::runtime_error("Image initialization failed.");


    if(TTF_Init() != 0)
        throw std::runtime_error("TTF initialization failed.");



    Logger::info("SDL loaded.");
}

Window::~Window() {
    Logger::info("Destroy window");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

/**
 * Clean the window.
 */
void Window::clear() {
    SDL_RenderClear(renderer);
}

/**
 * Render window
 */
void Window::render() {
    SDL_RenderPresent(renderer);
}

/**
 * @return true if user is focused on the window.
 */
bool Window::isFocused() const {
    return SDL_GetWindowFlags(window) & SDL_WINDOW_INPUT_FOCUS;
}

/**
 * Set the icon of the window
 * @param surface 
 */
void Window::setIcon(SDL_Surface *surface) {
    SDL_SetWindowIcon(window, surface);
}

