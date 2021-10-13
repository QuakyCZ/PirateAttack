//
// Created by KRATSTOM on 18.05.21.
//

#include "Credits.h"
#include <fstream>
#include <iostream>
#include "../../../Engine/UI/Text.h"

Credits::Credits(SDL_Renderer * renderer):Scene(renderer) {
    createBackground();
    createCredits();
    createMainMenuButton();
}

/**
 * Create background texture
 */
void Credits::createBackground() {
    auto bg = ResourceManager::getTexture("main_menu_background");
    if(!bg) return;

    auto bgObject = new GameObject("Background", {0,0}, bg->originalScale);
    bgObject->setTexture(bg->texture);
    this->gameObjects.push_back(bgObject);
}

/**
 * Show the text with credits.
 */
void Credits::createCredits() {
    auto creditsGO = new GameObject("Credits");
    auto texture = ResourceManager::getTexture("credits_background");
    if(texture)
        creditsGO->setTexture(texture->texture);
    else
        creditsGO->getSprite()->setColor({0,0,0,255});

    creditsGO->setAbsolutePosition({759, 200});
    creditsGO->setScale({402, 446});

    std::ifstream in(SceneManager::getAppPath() + "/assets/config/credits.cnf");
    if(in.is_open()) {
        std::string line;
        std::string result;

        while(std::getline(in, line)) {
            result += line + "\n";
        }

        Logger::info(result);
        auto text = new Text(getRenderer(), "Torii", result, 16, 402);
        text->setForeColor({255, 255, 255, 255});
        text->setParent(creditsGO);
        in.close();
    } else {
        Logger::severe("Credits config at " + SceneManager::getAppPath() + "/assets/config/credits.cnf was not found.");
    }
    gameObjects.push_back(creditsGO);
}

/**
 * Create button that loads Main Menu.
 */
void Credits::createMainMenuButton() {
    auto button = new Button();
    auto buttonTexture = ResourceManager::getTexture("back_button");
    if(buttonTexture)
        button->setTexture(MouseState::NORMAL, buttonTexture->texture);
    else
        button->getSprite()->setColor({201, 174, 115, 255});


    auto hoverTexture = ResourceManager::getTexture("back_button_hover");
    if(hoverTexture)
        button->setTexture(MouseState::HOVER, hoverTexture->texture);

    auto clickTexture = ResourceManager::getTexture("back_button_click");
    if(clickTexture)
        button->setTexture(MouseState::CLICKED, clickTexture->texture);

    button->setAbsolutePosition({800, 900});
    button->setScale({320, 70});
    button->registerCallback([](){
        SceneManager::loadScene("MainMenu");
    });

    gameObjects.push_back(button);
}
