//
// Created by KRATSTOM on 10.04.21.
//

#pragma once
#include <queue>
#include <vector>

#include "UI/Button.h"
#include "UI/VerticalLayoutGroup.h"

struct RenderPriorityComparer {
    inline bool operator () (Sprite * s1, Sprite * s2) const {
        return s1->getLayer() > s2->getLayer();
    }
};

class Scene {
private:
    SDL_Renderer * renderer;
    SDL_Color backgroundColor;
    std::priority_queue<Sprite *, std::vector<Sprite *>, RenderPriorityComparer> renderQueue;
protected:
    bool quit = false;
    std::vector<GameObject *> gameObjects;
    SDL_Renderer * getRenderer();
public:
    /**
     * Constructor of the scene. Sets background color to black
     * @param renderer a pointer to the SDL_Renderer
     */
    explicit Scene(SDL_Renderer * renderer);

    /**
     * Constructor of the scene. Sets custom background color
     * @param renderer
     * @param backgroundColor
     */
    Scene(SDL_Renderer * renderer, const SDL_Color & backgroundColor);

    /**
     * Destructor
     */
    virtual ~Scene();
    
    /**
     * Loads the scene
     */
    virtual void load() {}
    
    /**
     * Unloads the scene
     */
    virtual void unload() {}

    /**
     * Poll event and push it to game objects
     * @param event the event to handle
     */
    virtual void pollEvent(SDL_Event & event);

    /**
     * update the scene and all game objects
     * @param deltaTime
     */
    virtual void update(const float & deltaTime);

    /**
     * Render the scene and all game objects
     * @param renderer
     */
    void render(SDL_Renderer * renderer = nullptr);
    
    void enqueueChildren(GameObject * target);

    /**
     * @return true if the scene wants to quit
     */
    bool wantsQuit() const;

    /**
     * Close this scene
     */
    void close();
};
