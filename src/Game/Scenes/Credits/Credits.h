//
// Created by KRATSTOM on 18.05.21.
//

#pragma once
#include "../../../Engine/Managers/SceneManager.h"

class Credits: public Scene {
private:
    void createBackground();
    void createCredits();
    void createMainMenuButton();
public:
    explicit Credits(SDL_Renderer * renderer);

};


