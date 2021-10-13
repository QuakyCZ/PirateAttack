//
// Created by KRATSTOM on 10.04.21.
//

#include "ResourceManager.h"


SDL_Renderer * ResourceManager::renderer = nullptr;

std::map<std::string, ResourceManager::Texture> ResourceManager::textures;
std::map<std::string, std::string> ResourceManager::fontPaths;
std::string ResourceManager::appPath = "";
std::map<std::string, Config> ResourceManager::configs;
/**
 * Assigns the renderer
 * @param appPath the absolute path to the folder with the game
 * @param nRenderer the renderer
 */
void ResourceManager::init(SDL_Renderer * nRenderer, const std::string & appPath) {
    ResourceManager::renderer = nRenderer;
    ResourceManager::appPath = appPath;
}

/**
* Destroys all textures in the map
*/
void ResourceManager::destroy() {
    for (auto &it : ResourceManager::textures) {
        SDL_DestroyTexture(it.second.texture);
        SDL_FreeSurface(it.second.surface);
    }

    ResourceManager::textures.clear();
}

/**
* Adds a texture to the map.
* @param name the name of the texture
* @param texture the ptr to existing texture
*/
void ResourceManager::addTexture(const std::string &name, Texture texture) {
    if (ResourceManager::textures.find(name) == ResourceManager::textures.end()) {
        ResourceManager::textures.insert(std::pair<std::string, Texture>(name, texture));
    } else {
        throw std::logic_error("Texture with name " + name + " already exists!");
    }
}


/**
* Loads the texture from file.
* @param name the name of the texture
* @param imagePath the path to the image
* @throws std::runtime_error when fails loading image from the path or when fails creating the texture
* @throws std::logic_error when a texture with provided name already exists
*/
ResourceManager::Texture * ResourceManager::loadTexture(const std::string &name, const std::string &imagePath) {

    auto surface = IMG_Load((appPath + imagePath).c_str());
    if (!surface)
        throw std::runtime_error("Couldn't load image " + imagePath);
    Texture sTexture{Vector2D((float)surface->w, (float)surface->h)};

    auto texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (!texture) {
        SDL_FreeSurface(surface);
        throw std::runtime_error("Failed to create texture from " + imagePath);
    }
    try {
        sTexture.texture = texture;
        sTexture.surface = surface;
        ResourceManager::addTexture(name, sTexture);
    } catch (const std::logic_error & er) {
        Logger::severe(er.what());
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
        return nullptr;
    }
    Logger::info("Loaded texture " + name + " from " + imagePath);
    return &textures[name];
}

/**
 * Loads all textures provided in the config
 * @param filePath the path to the config file
 * @throws std::runtime_error when fails loading a config or an image from the path or when fails creating the texture
 * @throws std::logic_error when a texture with provided name already exists
 */
void ResourceManager::loadTexturesFromConfig(const std::string &filePath) {
    std::ifstream in = std::ifstream(filePath);
    if(in.is_open()) {
        std::string name;
        std::string path;
        while(in >> name) {
            in >> path;
            if(in.eof()) {
                destroy();
                throw std::logic_error("Malformed textures config " + filePath);
            }
            loadTexture(name, path);
        }
        in.close();
    } else {
        destroy();
        throw std::runtime_error("Couldn't open textures config " + filePath);
    }
}

/**
* Finds a texture with the name.
* @param name the name of the texture
* @return a ptr to the texture or null if not preset.
*/
ResourceManager::Texture * ResourceManager::getTexture(const std::string &name) {
    if (ResourceManager::textures.find(name) != ResourceManager::textures.end())
        return &ResourceManager::textures[name];
    Logger::warn("Texture with name: " + name + " does not exist!");
    return nullptr;
}


/**
 * Load paths of fonts from the font config.
 */
void ResourceManager::loadFontPaths(const std::string & pathToConfig) {
    std::ifstream in = std::ifstream(pathToConfig);
    if(in.is_open()) {
        std::string name, path;
        while(in >> name) {
            in >> path;
            if(in.eof())
                throw std::logic_error("Malformed textures config " + pathToConfig);
            fontPaths.insert({name, appPath + path});
            Logger::info("Loaded font " + name + " from " + path);
        }
        in.close();
    } else {
        throw std::runtime_error("Couldn't open fonts config " + pathToConfig);
    }
}

/**
 * @param name the name of the font
 * @param size the size of the font
 * @return a pointer to the TTF_Font with the size and name
 */
TTF_Font *ResourceManager::getFont(const std::string &name, const int size) {
    auto it = ResourceManager::fontPaths.find(name);
    if(it == ResourceManager::fontPaths.end())
        return nullptr;

    return TTF_OpenFont(it->second.c_str(), size);
}

/**
 * Get config by the name. Try to load it from the config folder if it was not yet.
 * @param name the name of the config.
 * @return a reference to the config.
 */
Config & ResourceManager::getConfig(const std::string & name) {
    auto it = configs.find(name);
    if(it == configs.end()) {
        try {
            Config cnf(appPath + "/assets/config/" + name + ".cnf");
            configs.insert({name, cnf});
            return configs.find(name)->second;
        } catch(std::invalid_argument & e) {
            throw e;
        } catch(std::runtime_error & e) {
            throw e;
        }
    }
    return it->second;
}


