//
// Created by KRATSTOM on 28.03.2021.
//


#include "Game.h"



std::string Game::appPath = std::string();

/**
 * @return A relative path to the build folder from the directory the program was run.
 */
std::string Game::getAppPath() {
    return Game::appPath;
}

/**
 * Creates instance of the game.
 * @param appPath The relative path to the build folder.
 */
Game::Game(const std::string &appPath) :
        window() {
    Logger::info("Creating game");
    Game::appPath = appPath;
    ResourceManager::init(window.getRenderer(), appPath);
    AudioManager::init(appPath);
    SceneManager::init(appPath);
    try {
        loadManagers();
        window.setIcon(ResourceManager::getTexture("window_icon")->surface);
    } catch(std::exception & e) {
        Logger::severe("Error while loading the game: " + std::string(e.what()));
        quit = true;
    }

}

/**
 * Deletes pending scenes.
 */
Game::~Game() {
    ResourceManager::destroy();
    AudioManager::destroy();
    SceneManager::quit();
}

/**
 * Loads configs, maps etc.
 */
void Game::loadManagers() {
    try {
        ResourceManager::loadTexturesFromConfig(appPath + "/assets/config/textures.cnf");
        ResourceManager::loadFontPaths(appPath + "/assets/config/fonts.cnf");
    } catch (std::runtime_error & e) {
        ResourceManager::destroy();
        Logger::severe("Exception from ResourceManager: ");
        Logger::severe(e.what());
        throw e;
    } catch (std::logic_error & e) {
        throw e;
    }

    try {
        AudioManager::loadSoundEffects(appPath + "/assets/config/sfx.cnf");
        AudioManager::loadSoundtrack(appPath + "/assets/config/soundtrack.cnf");
        AudioManager::setMusicVolume(0);
        AudioManager::setVolume(100);
    } catch(std::exception & e) {
        Logger::severe("Exception from AudioManager: ");
        Logger::severe(e.what());
        AudioManager::destroy();
        return;
    }


    SceneManager::registerScene("MainMenu", new MainMenu(window.getRenderer()));
    SceneManager::registerScene("LevelSelect", new LevelSelect(window.getRenderer()));
    SceneManager::registerScene("CreditsScene", new Credits(window.getRenderer()));
    SceneManager::registerScene("GameScene", new GameScene(window.getRenderer()));
    SceneManager::registerScene("GameOverScene", new GameOverScene(window.getRenderer()));
    SceneManager::loadScene("MainMenu");

    Logger::info("Game loaded");
}

/**
 * Handles user input
 */
void Game::pollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if(!window.isFocused())
            continue;
        if (event.type == SDL_QUIT || (
            event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE
        )) {
            quit = true;
        } else {
            SceneManager::pollEvent(event);
        }
    }
}

/**
 * Updates scenes
 * @param deltaTime
 */
void Game::update(const float &deltaTime) {
    AudioManager::updateSoundtrack();
    if(!window.isFocused())
        return;
    SceneManager::updateScene(deltaTime);
}

/**
 * Renders all game objects
 */
void Game::render() {
    SceneManager::renderScene();
    window.render();
}

/**
 * @return if game is running
 */
bool Game::isRunning() const {
    return !quit && SceneManager::isSceneLoaded();
}

/**
 * @return the window of the game
 */
Window & Game::getWindow() {
    return window;
}

