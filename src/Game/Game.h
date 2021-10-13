//
// Created by KRATSTOM on 28.03.2021.
//

#pragma once

#include <stdexcept>
#include <stack>
#include <filesystem>
#include <unistd.h>

#include "../Engine/Window.h"

#include "./Scenes/MainMenu/MainMenu.h"
#include "./Scenes/LevelSelect/LevelSelect.h"
#include "./Scenes/Credits/Credits.h"
#include "./Scenes/GameScene/GameScene.h"
#include "./Scenes/GameOver/GameOverScene.h"

class Game {
private:

    /**
     * The window with the game.
     */
    Window window;

    /**
     * If the game wants to quit.
     */
    bool quit = false;

    /**
     * The relative path to the build folder.
     */
    static std::string appPath;

    /**
     * Loads configs, maps etc.
     */
    void loadManagers();

public:
    Game(const std::string & appPath);
    virtual ~Game();

    /**
     * Handles user input
     */
    void pollEvents();

    /**
     * Updates scenes
     * @param deltaTime
     */
    void update(const float & deltaTime);

    /**
     * Renders scenes
     */
    void render();

    /**
     * @return if game is running
     */
    bool isRunning() const;

    /**
     * @return A relative path to the build folder from the directory the program was run.
     */
    static std::string getAppPath();

    /**
     * @return the window of the game
     */
    Window & getWindow();
};
