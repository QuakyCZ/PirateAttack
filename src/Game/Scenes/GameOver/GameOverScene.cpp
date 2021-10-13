//
// Created by KRATSTOM on 06.06.21.
//

#include "GameOverScene.h"

std::string GameOverScene::state;
int GameOverScene::score = 0;

GameOverScene::GameOverScene(SDL_Renderer *renderer) : Scene(renderer) {}

void GameOverScene::load() {
    if (state.empty())
        throw std::invalid_argument("GameOverScene: state (win / loose) was not specified!");

    createBackground();
    createResultText();
    createScoreText();
    createMainMenuButton();
}

/**
 * Create background texture.
 */
void GameOverScene::createBackground() {
    auto texture = ResourceManager::getTexture("main_menu_background");
    if (!texture)
        return;
    auto background = new GameObject("background");
    background->setTexture(texture->texture);
    background->setScale({1920, 1080});
    background->getSprite()->setLayer(-1);
    gameObjects.push_back(background);
}

/**
 * Create text that shows if player has won or lost the game.
 */
void GameOverScene::createResultText() {
    auto stateText = new Text(getRenderer(), "Torii", "You have " + state + " the game!", 30);
    stateText->setForeColor({255, 255, 255, 255});
    stateText->setAbsolutePosition({
                                           1920.0F / 2 - stateText->getScale().x / 2,
                                           500
                                   });
    gameObjects.push_back(stateText);
}

/**
 * Create text that shows player's score.
 */
void GameOverScene::createScoreText() {
    auto scoreText = new Text(getRenderer(), "Torii", "Score: " + std::to_string(score), 20);
    scoreText->setForeColor({255, 255, 255, 255});
    scoreText->setAbsolutePosition({
                                           1920.0F / 2 - scoreText->getScale().x / 2,
                                           550
                                   });
    gameObjects.push_back(scoreText);
}

/**
 * Create button that loads main menu scene.
 */
void GameOverScene::createMainMenuButton() {
    auto mainMenuButton = new Button();
    auto buttonTexture = ResourceManager::getTexture("back_button");
    if (!buttonTexture) {
        mainMenuButton->getSprite()->setColor({201, 174, 115, 255});
    } else {
        mainMenuButton->setTexture(MouseState::NORMAL, buttonTexture->texture);
    }

    auto hoverTexture = ResourceManager::getTexture("back_button_hover");
    if(hoverTexture)
        mainMenuButton->setTexture(MouseState::HOVER, hoverTexture->texture);

    auto clickTexture = ResourceManager::getTexture("back_button_click");
    if(clickTexture)
        mainMenuButton->setTexture(MouseState::CLICKED, clickTexture->texture);

    mainMenuButton->setAbsolutePosition({1920.0F / 2 - (float) 320 / 2, 900});
    mainMenuButton->setScale({320, 70});
    mainMenuButton->registerCallback([]() {
        SceneManager::loadScene("MainMenu");
    });
    gameObjects.push_back(mainMenuButton);
}