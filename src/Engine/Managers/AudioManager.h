//
// Created by KRATSTOM on 16.04.21.
//

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>
#include <iostream>
#include <fstream>


class AudioManager {
private:
    static std::string appPath;

    static std::map<std::string, Mix_Music *> soundtrack;
    static std::map<std::string, Mix_Chunk *> soundEffects;
    static std::map<std::string, Mix_Music *>::iterator currentSong;

    static bool initialized;
public:
    static void init(const std::string &appPath);

    static void destroy();

    static void loadSound(std::string &name, const std::string &path);

    static void loadSoundEffects(const std::string &configPath);
    
    static void loadMusicFile(std::string &name, const std::string &path);
    
    static void loadSoundtrack(const std::string &configPath);
    
    static void playSound(const std::string &name, const int &loops = 0);

    static void playMusic(const std::string &name);

    static void playSoundtrack();

    static void updateSoundtrack();

    static void pauseSoundtrack();

    static void setVolume(const int &val);

    static void setMusicVolume(const int &val);
};


