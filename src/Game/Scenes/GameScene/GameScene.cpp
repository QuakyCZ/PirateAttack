//
// Created by KRATSTOM on 12.04.21.
//

#include "GameScene.h"
#include <iostream>
#include <ctime>
#include "../GameOver/GameOverScene.h"

Human *GameScene::player = nullptr;
Computer *GameScene::computer = nullptr;
Map *GameScene::map = nullptr;
GameScene *GameScene::instance = nullptr;
int GameScene::level = -1;
std::string GameScene::savePath;

GameScene::GameScene(SDL_Renderer *renderer) :
        Scene(renderer, {153, 204, 237, 255}) {
    GameScene::instance = this;
}

void GameScene::load() {
    Scene::load();
    Logger::info("Loading gameScene");
    auto backGround = new GameObject();
    auto bg = ResourceManager::getTexture("game_background");
    backGround->setTexture(bg->texture);
    backGround->getSprite()->setLayer(-1);
    backGround->setScale(bg->originalScale);
    gameObjects.push_back(backGround);
    auto moneyText = new Text(getRenderer(), "Torii", "Money: 0", 15);
    moneyText->setAbsolutePosition({20, 20});
    gameObjects.push_back(moneyText);

    auto scoreText = new Text(getRenderer(), "Torii", "Score: 0", 15);
    scoreText->setAbsolutePosition({20, 50});
    gameObjects.push_back(scoreText);

    delete GameScene::player;
    delete GameScene::computer;
    GameScene::player = new Human(moneyText, scoreText);
    GameScene::computer = new Computer();

    player->start();
    computer->start();
    if (GameScene::savePath != "")
        loadFromSave();
    else {
        try {
            loadMap();
        } catch (std::invalid_argument &e) {
            for (auto go : gameObjects)
                delete go;
            gameObjects.clear();
            throw e;
        }
    }
    loadMonsterButtons();
}

/**
 * Put monster buttons in the scene.
 */
void GameScene::loadMonsterButtons() {
    auto goblinButtonTexture = ResourceManager::getTexture("goblin_button");
    auto goblinButton = new MonsterButton(getRenderer(), "goblin", {32, 980}, {64, 64});

    if(goblinButtonTexture) {
        goblinButton->setTexture(MouseState::NORMAL, goblinButtonTexture->texture);
        goblinButton->setTexture(MouseState::HOVER, goblinButtonTexture->texture);
        goblinButton->setTexture(MouseState::CLICKED, goblinButtonTexture->texture);
    } else {
        goblinButton->getSprite()->setColor({0, 0, 128, 255});
    }

    gameObjects.push_back(goblinButton);

    auto trollButtonTexture = ResourceManager::getTexture("troll_button");
    auto trollButton = new MonsterButton(getRenderer(), "troll", {106, 980},
                                         {64, 64});
    if(trollButtonTexture) {
        trollButton->setTexture(MouseState::NORMAL, trollButtonTexture->texture);
        trollButton->setTexture(MouseState::HOVER, trollButtonTexture->texture);
        trollButton->setTexture(MouseState::CLICKED, trollButtonTexture->texture);
    } else {
        trollButton->getSprite()->setColor({0, 0, 128, 255});
    }
    gameObjects.push_back(trollButton);
}

/**
 * Delete all game objects and players.
 */
void GameScene::unload() {
    for (auto go : gameObjects) {
        delete go;
    }
    gameObjects.clear();
    delete computer;
    computer = nullptr;
    delete player;
    player = nullptr;
    level = -1;
}

/**
 * Save and leave the game when ESC is pressed.
 * @param event 
 */
void GameScene::pollEvent(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            if (player->isSummoning())
                player->cancelSummoning();
            else {
                save();
                level = -1;
                SceneManager::loadScene("MainMenu");
            }
        }
    } else
        Scene::pollEvent(event);
}

/**
 * Loads a map. GameScene::level must be assigned before calling this.
 */
void GameScene::loadMap() {
    Logger::info("Loading map");
    if (level == -1)
        throw std::invalid_argument("Level was not declared!");
    map = new Map(
            "map",
            SceneManager::getAppPath() + "/assets/levels/" + std::to_string(level) + ".level");
    gameObjects.push_back(map);
    loadMapConfig();
}

/**
 * Load confing of the map.
 */
void GameScene::loadMapConfig() {
    std::string mapConfigFile = SceneManager::getAppPath() + "/assets/levels/" + std::to_string(level) + ".xml";
    xmlDoc *doc = xmlReadFile(mapConfigFile.c_str(), "utf-8", 0);
    if (!doc)
        throw std::invalid_argument("Could not load map config " + mapConfigFile);
    xmlNode *rootElement = xmlDocGetRootElement(doc);
    if (!rootElement)
        throw std::invalid_argument("Map config has not root element!");
    
    auto playerNode = rootElement->children;
    while (playerNode) {
        if (playerNode->type != XML_ELEMENT_NODE) {
            playerNode = playerNode->next;
            continue;
        }
        try {
            if (xmlStrEqual(playerNode->name, BAD_CAST "human"))
                player->deserializeConfig(playerNode);
            else if (xmlStrEqual(playerNode->name, BAD_CAST "computer"))
                computer->deserializeConfig(playerNode);
            else
                Logger::warn(
                        "Map config: Unknown player " + std::string(reinterpret_cast<const char *>(playerNode->name)));
        } catch(std::exception & e) {
            xmlFreeDoc(doc);
            throw e;
        }

        playerNode = playerNode->next;
    }
    xmlFreeDoc(doc);
}

/**
 * Update game objects and players.
 * @param deltaTime 
 */
void GameScene::update(const float &deltaTime) {
    Scene::update(deltaTime);
    player->update(deltaTime);
    computer->update(deltaTime);
}

/**
 * Signalize human's win.
 */
void GameScene::onHumanWin() {
    Logger::info("Human won!");
    map->baseTile->destroyStructure();
    GameOverScene::state = "WON";
    GameOverScene::score = player->getScore();
    SceneManager::prepareScene("GameOverScene");
}

/**
 * Signalize computer's win.
 */
void GameScene::onComputerWin() {
    Logger::info("Computer won!");
    GameOverScene::state = "LOST";
    GameOverScene::score = player->getScore();
    SceneManager::prepareScene("GameOverScene");
}

/**
 * Save a xml file with the game progress.
 */
void GameScene::save() const {
    std::time_t t = std::time(0);
    std::tm *time = std::localtime(&t);
    std::string fileName = SceneManager::getAppPath() + "/assets/saves/save-"
                           + std::to_string(time->tm_year + 1900)
                           + std::to_string(time->tm_mon)
                           + std::to_string(time->tm_mday)
                           + std::to_string(time->tm_hour)
                           + std::to_string(time->tm_min)
                           + std::to_string(time->tm_sec) + ".xml";

    xmlTextWriterPtr writer = xmlNewTextWriterFilename(fileName.c_str(), 0);
    if (!writer) {
        Logger::warn("Could not save file " + fileName + ".");
        return;
    }
    if (xmlTextWriterStartDocument(writer, "1.0", "utf-8", nullptr) < 0)
        return;

    if (xmlTextWriterStartElement(writer, BAD_CAST "save") < 0)
        return;
    xmlTextWriterWriteAttribute(writer, BAD_CAST "level", BAD_CAST std::to_string(level).c_str());

    player->serialize(writer);

    xmlTextWriterStartElement(writer, BAD_CAST "computer");
    xmlTextWriterWriteAttribute(writer, BAD_CAST "money", BAD_CAST std::to_string(computer->getMoney()).c_str());
    map->baseTile->getStructure()->serialize(writer);

    xmlTextWriterStartElement(writer, BAD_CAST "towers");
    for (auto slot : map->getTowerSlots()) {
        slot->getStructure()->serialize(writer);
    }
    xmlTextWriterEndElement(writer); //towers

    xmlTextWriterEndElement(writer); //computer

    xmlTextWriterEndElement(writer); //root
    xmlTextWriterEndDocument(writer);
    xmlFreeTextWriter(writer);
}

void GameScene::loadFromSave() {
    xmlDoc *doc = xmlReadFile(savePath.c_str(), "utf-8", 0);
    if (!doc)
        throw std::invalid_argument("Could not load save file " + savePath);
    xmlNode *rootElement = xmlDocGetRootElement(doc);
    if (!rootElement)
        throw std::invalid_argument("Save file has not root element!");

    auto levelString = xmlGetProp(rootElement, BAD_CAST "level");
    if (!levelString)
        throw std::invalid_argument("Save file has not specified the level.");

    level = std::stoi(reinterpret_cast<const char *>(levelString));
    xmlFree(levelString);
    loadMap();

    xmlNode *currPlayer = rootElement->children;
    try {
        while (currPlayer) {
            if (currPlayer->type != XML_ELEMENT_NODE) {
                currPlayer = currPlayer->next;
                continue;
            }

            if (xmlStrEqual(currPlayer->name, BAD_CAST "human") == 1) {
                player->deserialize(currPlayer);
            } else if (xmlStrEqual(currPlayer->name, BAD_CAST "computer") == 1) {
                computer->deserialize(currPlayer);
            } else
                throw std::invalid_argument("Unknown player " + std::string(reinterpret_cast<const char *>(currPlayer->name)));
            currPlayer = currPlayer->next;
        }
    } catch(std::invalid_argument & e) {
        xmlFreeDoc(doc);
        savePath.clear();
        throw e;
    }

    xmlFreeDoc(doc);
    savePath.clear();

}


