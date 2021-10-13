//
// Created by KRATSTOM on 06.06.21.
//

#pragma once
#include "../../../Engine/Managers/SceneManager.h"
#include "../../../Engine/UI/Text.h"

class GameOverScene: public Scene {
private:
public:
    GameOverScene() = delete;
    explicit GameOverScene(SDL_Renderer * renderer);
    
    static std::string state;
    static int score;
    
    void load() override;

    void createMainMenuButton();

    void createResultText();

    void createScoreText();

    void createBackground();
};


