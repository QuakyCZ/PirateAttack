//
// Created by KRATSTOM on 10.04.21.
//

#include "MainMenu.h"

/**
 * Constructor of Main Menu
 * @param renderer the renderer of the game
 */
MainMenu::MainMenu(SDL_Renderer * renderer):
Scene(renderer, {255, 255, 255, 255}) {
    AudioManager::playSoundtrack();
    createBackground();

    createLogo();

    createNavigation();
    createPlayButton();
    createCreditsButton();
    createQuitButton();
}

/**
 * Create game object with the background texture.
 */
void MainMenu::createBackground() {
    auto bg = ResourceManager::getTexture("main_menu_background");

    if(!bg)
        return;

    auto gameObject = new GameObject("Main Menu background", Vector2D(0,0), bg->originalScale);
    gameObject->setTexture(bg->texture);
    gameObject->getSprite()->setLayer(-1);
    gameObjects.push_back(gameObject);
}

/**
 * Create game object with the texture of logo.
 */
void MainMenu::createLogo() {
    auto logoTexture = ResourceManager::getTexture("main_menu_logo");
    if(!logoTexture)
        return;

    float x = 1920.0F / 2 - logoTexture->originalScale.x / 2;
    float y = 1080.0F / 4 - logoTexture->originalScale.y / 2 + 50;
    Vector2D pos(x,y);
    auto go = new GameObject("Logo", pos, logoTexture->originalScale);
    go->setTexture(logoTexture->texture);
    gameObjects.push_back(go);
}

/**
 * Create navigation buttons.
 */
void MainMenu::createNavigation() {
    auto navBG = ResourceManager::getTexture("main_menu_nav_background");
    if(!navBG)
        throw std::runtime_error("MainMenu::createNavigation(): main_menu_nav_background null");

    float x = 1920.0F / 2 - navBG->originalScale.x / 2;
    float y = 1080.0F / 2 - navBG->originalScale.y / 2 + 100;
    Vector2D pos(x, y);
    Vector2D spacing(10, 10);
    navigation = new VerticalLayoutGroup("Nav", pos, navBG->originalScale, spacing);
    navigation->setTexture(navBG->texture);
    gameObjects.push_back(navigation);
}

/*
 * Create play button
 */
void MainMenu::createPlayButton() {
    auto texture = ResourceManager::getTexture("play_button");
    if(!texture)
        throw std::runtime_error("MainMenu::createNavigation(): play_button null");
    auto playButton = new Button(
            "play button",
            Vector2D(0, 0),
            texture->originalScale
            );

    auto callback = []()->void {
        Logger::info("Play");
        SceneManager::loadScene("LevelSelect");
    };

    playButton->registerCallback(callback);
    playButton->setTexture(MouseState::NORMAL, texture->texture);

    auto hoverTexture = ResourceManager::getTexture("play_button_hover");
    if(hoverTexture)
        playButton->setTexture(MouseState::HOVER, hoverTexture->texture);
    else
        playButton->setTexture(MouseState::HOVER, texture->texture);

    auto clickTexture = ResourceManager::getTexture("play_button_clicked");
    if(clickTexture)
        playButton->setTexture(MouseState::CLICKED, clickTexture->texture);
    else
        playButton->setTexture(MouseState::CLICKED, texture->texture);

    playButton->setParent(navigation);
}

/**
 * Create credits button
 */
void MainMenu::createCreditsButton() {
    auto texture = ResourceManager::getTexture("credits_button");
    if(!texture)
        throw std::runtime_error("MainMenu::createCreditsButton(): credits_button null");

    auto quitButton = new Button(
            "credits button",
            Vector2D(0, 0),
            texture->originalScale
    );

    auto callback = []()->void {
        Logger::info("Credits");
        SceneManager::loadScene("CreditsScene");
    };

    quitButton->registerCallback(callback);
    quitButton->setTexture(MouseState::NORMAL, texture->texture);

    auto hoverTexture = ResourceManager::getTexture("credits_button_hover");
    if(hoverTexture)
        quitButton->setTexture(MouseState::HOVER, hoverTexture->texture);
    else
        quitButton->setTexture(MouseState::HOVER, texture->texture);

    auto clickTexture = ResourceManager::getTexture("credits_button_clicked");
    if(clickTexture)
        quitButton->setTexture(MouseState::CLICKED, clickTexture->texture);
    else
        quitButton->setTexture(MouseState::CLICKED, texture->texture);

    quitButton->setParent(navigation);
}

/**
 * Create quit button
 */
void MainMenu::createQuitButton() {
    auto texture = ResourceManager::getTexture("quit_button");
    if(!texture)
        throw std::runtime_error("MainMenu::createQuitButton(): quit_button null");

    auto quitButton = new Button(
            "quit button",
            Vector2D(0, 0),
            texture->originalScale
    );

    auto callback = [this]()->void {
        close();
    };

    quitButton->registerCallback(callback);
    quitButton->setTexture(MouseState::NORMAL, texture->texture);

    auto hoverTexture = ResourceManager::getTexture("quit_button_hover");
    if(hoverTexture)
        quitButton->setTexture(MouseState::HOVER, hoverTexture->texture);
    else
        quitButton->setTexture(MouseState::HOVER, texture->texture);

    auto clickTexture = ResourceManager::getTexture("quit_button_clicked");

    if(clickTexture)
        quitButton->setTexture(MouseState::CLICKED, clickTexture->texture);
    else
        quitButton->setTexture(MouseState::CLICKED, texture->texture);

    quitButton->setParent(navigation);
}



