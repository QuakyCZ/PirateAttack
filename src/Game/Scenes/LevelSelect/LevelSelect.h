//
// Created by KRATSTOM on 04.06.21.
//

#pragma once
#include "../../../Engine/Managers/SceneManager.h"

class LevelSelect: public Scene {
private:
    void showLevels();
    void showSaves();
public:
    explicit LevelSelect(SDL_Renderer * renderer);
    void load() override;
    void unload() override;
    
    void pollEvent(SDL_Event &event) override;
};


