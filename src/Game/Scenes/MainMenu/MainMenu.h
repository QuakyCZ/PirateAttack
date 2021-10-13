//
// Created by KRATSTOM on 10.04.21.
//

#pragma once

#include "../../../Engine/Managers/SceneManager.h"

class MainMenu : public Scene {
private:
    VerticalLayoutGroup * navigation = nullptr;
public:
    /**
     * Constructor of Main Menu
     * @param renderer the renderer of the game
     */
    explicit MainMenu(SDL_Renderer * renderer);

    void createBackground();

    void createLogo();

    void createNavigation();

    void createPlayButton();
    void createCreditsButton();
    void createQuitButton();
};