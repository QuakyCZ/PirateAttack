//
// Created by KRATSTOM on 13.04.21.
//

#include "SceneManager.h"

std::string SceneManager::appPath = "";
std::map<std::string, Scene *> SceneManager::scenes = std::map<std::string, Scene *>();
Scene * SceneManager::currentScene = nullptr;
Scene * SceneManager::nextScene = nullptr;


void SceneManager::init(const std::string & appPath) {
    SceneManager::appPath = appPath;
}

/**
 * Clean all scenes.
 */
void SceneManager::quit() {
    for(auto & it : scenes) {
        delete it.second;
    }
    scenes.clear();
}

/**
 * Pass user event to the current scene.
 * @param event user's event
 */
void SceneManager::pollEvent(SDL_Event &event) {
    if(nextScene)
        loadScene();
    if(currentScene) {
        currentScene->pollEvent(event);
        if (currentScene->wantsQuit())
            currentScene = nullptr;
    }
}

/**
 * Updates current scene
 * @param deltaTime the time of the last frame in ms
 */
void SceneManager::updateScene(const float & deltaTime) {
    if(nextScene)
        loadScene();
    if(currentScene) {
        currentScene->update(deltaTime);
        if (currentScene->wantsQuit())
            currentScene = nullptr;
    }
}

/**
 * Renders current scene
 */
void SceneManager::renderScene() {
    if(currentScene)
        currentScene->render();
}

/**
 * Register a scene
 * @param name the name of the scene
 * @param scene the pointer to the scene
 * @return true if it was registered, false if a scene with the name already exists.
 */
bool SceneManager::registerScene(const std::string &name, Scene * scene) {
    if(scenes.find(name) != scenes.end())
        return false;
    scenes.insert(std::pair<std::string, Scene*>(name, scene));
    return true;
}

/**
 * Unregister scene.
 * @param name the name of the scene to unregister.
 * @return true if the scene has been unregistered and deleted. False if the scene does not exist.
 */
bool SceneManager::unregisterScene(const std::string &name) {
    auto it = scenes.find(name);
    if(it == scenes.end())
        return false;
    delete it->second;
    scenes.erase(it);
    return true;
}

/**
 * Unload current scene and load a scene with the name.
 * @param name the name of the scene.
 * @return true if it was loaded, false if it was not found or any exception has occurred.
 */
bool SceneManager::loadScene(const std::string &name) {
    if(!name.empty()) {
        if(scenes.find(name) == scenes.end()) {
            Logger::warn("Scene " + name + " was not found.");
            return false;
        }
        nextScene = scenes[name];
    }
    try {
        nextScene->load();
        if(currentScene)
            currentScene->unload();
        currentScene = nextScene;
        nextScene = nullptr;
    } catch(std::exception & e) {
        Logger::severe("Could not load scene " + name + ": " + e.what());
        nextScene->unload();
        nextScene = nullptr;
        return false;
    }
    return true;
}

/**
 * @return true if any scene is loaded and active.
 */
bool SceneManager::isSceneLoaded() {
    return currentScene != nullptr;
}

/**
 * @return a path to the game's folder
 */
std::string SceneManager::getAppPath() {
    return appPath;
}

/**
 * Prepares a scene to be loaded before next frame.
 * @param name the name of the scene to load
 * @return true if it was prepared, false if it was not found.
 */
bool SceneManager::prepareScene(const std::string & name) {
    if(scenes.find(name) == scenes.end()) {
        Logger::warn("Scene " + name + " was not found.");
        return false;
    }
    nextScene = scenes[name];
    return true;
}




