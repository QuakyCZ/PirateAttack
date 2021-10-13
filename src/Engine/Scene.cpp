//
// Created by KRATSTOM on 10.04.21.
//

#include "Scene.h"

Scene::Scene(SDL_Renderer *renderer) : backgroundColor() {
    this->renderer = renderer;
    backgroundColor.a = 255;
}

Scene::Scene(SDL_Renderer *mRenderer, const SDL_Color &backgroundColor) : backgroundColor(backgroundColor) {
    this->renderer = mRenderer;
}

Scene::~Scene() {
    for(auto go : gameObjects)
        delete go;
    gameObjects.clear();
}

SDL_Renderer *Scene::getRenderer() {
    return renderer;
}

void Scene::update(const float & deltaTime) {
    for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
        auto gameObject = *it;
        gameObject->update(deltaTime);
        if(gameObject->isDestroyed()) {
            delete gameObject;
            gameObjects.erase(it);
        }
    }
}

void Scene::render(SDL_Renderer * mRenderer) {
    if(mRenderer == nullptr)
        mRenderer = renderer;

    SDL_SetRenderDrawColor(
            mRenderer,
            backgroundColor.r,
            backgroundColor.g,
            backgroundColor.b,
            backgroundColor.a
            );

    SDL_RenderClear(mRenderer);
    for (GameObject * gameObject : gameObjects) {
        renderQueue.push(gameObject->getSprite());
        enqueueChildren(gameObject);
    }
    while(!renderQueue.empty()) {
        auto sprite = renderQueue.top();
        renderQueue.pop();
        sprite->draw(renderer);
    }
}

void Scene::enqueueChildren(GameObject *target) {
    if(!target || !target->isVisible())
        return;
    for(auto child : target->getChildren()) {
        renderQueue.push(child->getSprite());
        enqueueChildren(child);
    }
}

void Scene::pollEvent(SDL_Event & event) {
    for(auto go : gameObjects) {
        go->pollEvent(event);
    }
}

bool Scene::wantsQuit() const {
    return quit;
}

/**
 * Close this scene
 */
void Scene::close() {
    quit = true;
}


