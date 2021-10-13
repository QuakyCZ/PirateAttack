//
// Created by KRATSTOM on 12.04.21.
//

#pragma once
#include "../../../Engine/Managers/SceneManager.h"
#include "GameObjects/Map/Map.h"
#include "./Players/Human.h"
#include "./Players/Computer.h"
#include "GameObjects/Buttons/MonsterButton.h"


class GameScene: public Scene {
private:
    static Human * player;
    static Computer * computer;
    static GameScene * instance;
    static int level;
    
    void loadMap();
    void loadMapConfig();
    
    void save() const;
    void loadFromSave();
    
    void loadMonsterButtons();
public:
    static Map * map;
    static std::string savePath;
    explicit GameScene(SDL_Renderer * renderer);
    void load() override;
    void unload() override;
    void pollEvent(SDL_Event & event) override;
    void update(const float &deltaTime) override;
    static void onHumanWin();
    static void onComputerWin();
    
    /**
     * @return instance of the player
     */
    static Human * getPlayer() {
        return player;
    }

    /**
     * @return instance of the computer
     */
    static Computer * getComputer() {
        return computer;
    }
    
    /**
     * Set the level that should be loaded.
     * @param val the number of the level
     */
    static void setLevel(const int & val) {
        if(level == -1)
            level = val;
    }
    
    /**
     * Set the path to the save that should be loaded.
     * @param path the path to the save xml file.
     */
    static void loadSave(std::string path) {
        GameScene::savePath = std::move(path);
    }

};


