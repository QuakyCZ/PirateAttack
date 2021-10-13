//
// Created by KRATSTOM on 04.06.21.
//

#include <iostream>
#include <dirent.h>
#include "LevelSelect.h"
#include "../GameScene/GameScene.h"

LevelSelect::LevelSelect(SDL_Renderer * renderer): Scene(renderer) {}

/**
 * Create buttons with levels and saves.
 */
void LevelSelect::load() {
    Scene::load();
    auto bgTexture = ResourceManager::getTexture("main_menu_background");
    if(bgTexture) {
        auto bgGO = new GameObject("background", {0, 0}, bgTexture->originalScale);
        bgGO->setTexture(bgTexture->texture);
        gameObjects.push_back(bgGO);
    }
    showLevels();
    showSaves();
}

/**
 * delete game objects
 */
void LevelSelect::unload() {
    Scene::unload();
    for(auto go : gameObjects)
        delete go;
    gameObjects.clear();
}

/**
 * Return to the MainMenu when ESC is pressed.
 * @param event 
 */
void LevelSelect::pollEvent(SDL_Event &event) {
    if(event.type == SDL_KEYDOWN) {
        if(event.key.keysym.sym == SDLK_ESCAPE) {
            SceneManager::loadScene("MainMenu");
        }
    } else
        Scene::pollEvent(event);
}

/**
 * Read folder with levels and show them in the scene.
 */
void LevelSelect::showLevels() {
    DIR * dir = nullptr;
    struct dirent * diread = nullptr;
    std::vector<std::string> files;
    if((dir = opendir((SceneManager::getAppPath() + "/assets/levels").c_str())) != nullptr) {
        while((diread = readdir(dir)) != nullptr) {
            auto it = std::lower_bound(files.begin(), files.end(), diread->d_name);
            files.insert(it, diread->d_name);
        }
        closedir(dir);        
    } else {
        Logger::severe("Exception while reading files in the levels folder!");
        return;
    }
    int levelsCount = 0;
    for(auto & file : files) {
        int dotPos = file.find_first_of('.');
        if(dotPos == 0)
            continue;
        int level;
        try {
            level = std::stoi(file.substr(0, dotPos));
        } catch(std::exception & e) {
            continue;
        }
        if(file != std::to_string(level) + ".level")
            continue;
        auto button = new Button("map_select_button_" + std::to_string(level));
        button->setScale({64, 64});
        button->setAbsolutePosition({((float)levelsCount) * 74, (float)((levelsCount / 30) * 64) * 11});
        button->getSprite()->setColor({150, 140, 116, 255});
        button->getSprite()->setLayer(2);
        button->registerCallback([level](){
            GameScene::setLevel(level);
            SceneManager::prepareScene("GameScene");
        });
        auto txt = new Text(getRenderer(), "Torii", std::to_string(level), 15, {0,0,0,255}, -1);
        txt->setParent(button);
        gameObjects.push_back(button);
        ++levelsCount;
    }
}


/**
 * Read folder with saves and show them in the scene.
 */
void LevelSelect::showSaves() {
    DIR * dir = nullptr;
    struct dirent * diread = nullptr;
    std::vector<std::string> files;
    if((dir = opendir((SceneManager::getAppPath() + "/assets/saves").c_str())) != nullptr) {
        while((diread = readdir(dir)) != nullptr) {
            files.emplace_back(diread->d_name);
        }
        closedir(dir);
    } else {
        Logger::severe("Exception while reading files in the levels folder!");
        return;
    }
    int levelsCount = 0;
    for(auto & file : files) {
        int dotPos = file.find_first_of('.');
        if(dotPos == 0)
            continue;
        
        std::string saveName = file.substr(0, dotPos);
        
        auto button = new Button("save_" + saveName);
        button->setScale({200, 64});
        button->setAbsolutePosition({((float)levelsCount) * 210, 540 + (float)((levelsCount / 30) * 64) * 11});
        button->getSprite()->setColor({150, 140, 116, 255});
        button->getSprite()->setLayer(2);
        button->registerCallback([file](){
            GameScene::savePath = SceneManager::getAppPath() + "/assets/saves/" + file;
            SceneManager::prepareScene("GameScene");
        });
        auto txt = new Text(getRenderer(), "Torii", saveName, 15, {0,0,0,255}, -1);
        txt->setParent(button);
        gameObjects.push_back(button);
        ++levelsCount;
    }
}


