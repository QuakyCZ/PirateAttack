//
// Created by KRATSTOM on 10.04.21.
//

#pragma once

#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <fstream>
#include "../Logger/Logger.h"
#include "../Vector2D.h"
#include "../Config.h"


class ResourceManager {
private:
    struct Texture {
        Vector2D originalScale;
        SDL_Texture * texture;
        SDL_Surface * surface;
    };
    static SDL_Renderer * renderer;
    static std::map<std::string, Config> configs;
    static std::map<std::string, Texture> textures;
    static std::map<std::string, std::string> fontPaths;
    static std::string appPath;
public:
    ResourceManager() = delete;
    static void init(SDL_Renderer * nRenderer, const std::string & appPath);
    
    static void destroy();

    static void addTexture(const std::string & name, Texture texture);

    static Texture * loadTexture(const std::string & name, const std::string & path);

    static void loadTexturesFromConfig(const std::string & path);

    static Texture * getTexture(const std::string & name);

    static void loadFontPaths(const std::string & pathToConfig);

    static TTF_Font * getFont(const std::string & path, const int size);
    
    static Config & getConfig(const std::string & name);
};

