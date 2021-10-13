//
// Created by KRATSTOM on 13.04.21.
//

#pragma once


#include <SDL2/SDL.h>
#include <map>
#include <string>
#include "../Scene.h"

class SceneManager {
private:
    static std::string appPath;
    static std::map<std::string, Scene *> scenes;
    static Scene * currentScene;
    static Scene * nextScene;
public:
    static void init(const std::string & appPath);
    static void quit();

    static void pollEvent(SDL_Event & event);
    static void updateScene(const float & deltaTime);
    static void renderScene();
    
    static std::string getAppPath();

    static bool registerScene(const std::string & name, Scene * scene);
    static bool unregisterScene(const std::string & name);
    static bool loadScene(const std::string & name = "");
    static bool prepareScene(const std::string & name);

    static bool isSceneLoaded();
};


