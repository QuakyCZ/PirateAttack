//
// Created by KRATSTOM on 16.04.21.
//

#include "AudioManager.h"
#include "../Logger/Logger.h"

std::string AudioManager::appPath = std::string();
std::map<std::string, Mix_Chunk *> AudioManager::soundEffects = std::map<std::string, Mix_Chunk *>();
std::map<std::string, Mix_Music *> AudioManager::soundtrack = std::map<std::string, Mix_Music *>();

std::map<std::string, Mix_Music *>::iterator AudioManager::currentSong = soundtrack.begin();

bool AudioManager::initialized = false;

/**
 * Inits SDL Audio
 * @param appPath the path to the game's folder
 */
void AudioManager::init(const std::string &appPath) {
    AudioManager::appPath = appPath;
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        Logger::warn("Audio initialization failed.");
        return;
    }

    int flags = MIX_INIT_MP3;
    int result = 0;
    if (flags != (result = Mix_Init(flags))) {
        Logger::warn("MP3 initialization failed.");
        return;
    }

    initialized = true;
}

/**
 * Clean SDL audio
 */
void AudioManager::destroy() {
    Mix_HaltMusic();
    Mix_CloseAudio();
    for (auto &it : soundtrack)
        Mix_FreeMusic(it.second);

    for (auto &it : soundEffects)
        Mix_FreeChunk(it.second);

    soundtrack.clear();
    soundEffects.clear();
    Mix_Quit();
}

/**
 * Load sound from the path
 * @param name the name of the sound
 * @param path the path to the sound
 */
void AudioManager::loadSound(std::string &name, const std::string &path) {
    int audioRate = 44100;
    Uint16 audioFormat = AUDIO_S16;
    int audioChannels = 2;
    int audioBuffers = 640;
    Mix_OpenAudio(audioRate, audioFormat, audioChannels, audioBuffers);
    auto music = Mix_LoadWAV((appPath + path).c_str());
    if (!music) {
        Logger::warn("Could not load sound " + name + " from " + path);
        Logger::severe(Mix_GetError());
        return;
    }

    soundEffects.insert(std::pair<std::string, Mix_Chunk *>(name, music));
    Logger::info("Loaded sound " + name + " from " + path);
}

/**
 * Load sound effects from the config
 * @param configPath a path to the config with sound effects
 */
void AudioManager::loadSoundEffects(const std::string &configPath) {
    std::ifstream in = std::ifstream(configPath);
    if (in.is_open()) {
        std::string name;
        std::string path;
        while (in >> name) {
            in >> path;
            if (in.eof()) {
                Logger::warn("Malformed sfx config " + configPath);
                return;
            }
            loadSound(name, path);
        }
        in.close();
    } else {
        Logger::warn("Couldn't open sfx config " + configPath);
    }
}

/**
 * Load music from the file
 * @param name the name of the music
 * @param path the path to the music
 */
void AudioManager::loadMusicFile(std::string &name, const std::string &path) {
    auto music = Mix_LoadMUS((appPath + path).c_str());
    if (!music) {
        Logger::warn("Could not load sound " + name + " from " + path);
        Logger::severe(Mix_GetError());
        return;
    }

    soundtrack.insert(std::pair<std::string, Mix_Music *>(name, music));
    Logger::info("Loaded music " + name + " from " + path);
}

/**
 * Load all music from the config.
 * @param configPath the path to the config
 */
void AudioManager::loadSoundtrack(const std::string &configPath) {
    std::ifstream in = std::ifstream(configPath);
    if (in.is_open()) {
        std::string name;
        std::string path;
        while (in >> name) {
            in >> path;
            if (in.eof()) {
                Logger::warn("Malformed soundtrack config " + configPath);
                return;
            }
            loadMusicFile(name, path);
        }
        currentSong = soundtrack.begin();
        in.close();
    } else {
        Logger::warn("Couldn't open soundtrack config " + configPath);
    }
}

/**
 * Plays a sound with provided name.
 * @param name the name of the sound to play
 * @param loops the number of loops the sound will be played. Default - 0
 */
void AudioManager::playSound(const std::string &name, const int &loops) {
    if (!initialized)
        return;

    auto it = soundEffects.find(name);
    if (it == soundEffects.end()) {
        Logger::warn("Sound " + name + " was not loaded.");
        return;
    }
    Mix_Volume(1, 128);
    Mix_PlayChannel(1, it->second, loops);
}

/**
 * Play a music with provided name.
 * @param name the name of the music
 */
void AudioManager::playMusic(const std::string &name) {
    if (!initialized) {
        Logger::warn("AudioManager has not been initialized yet. Call AudioManager::init() before any action.");
        return;
    }

    pauseSoundtrack();

    auto it = soundtrack.find(name);
    if (it == soundtrack.end()) {
        Logger::warn("Music " + name + " is not loaded.");
        return;
    }
    Mix_PlayMusic(it->second, -1);
}

/**
 * Play soundtrack.
 */
void AudioManager::playSoundtrack() {
    if (!initialized)
        return;

    if (Mix_PlayingMusic()) {
        if (Mix_PausedMusic() == 1) {
            Mix_ResumeMusic();
        } else {
            return;
        }
    }

    if (soundtrack.empty())
        return;
    
    Mix_PlayMusic(currentSong->second, 1);
}

/**
 * Switch music if the previous has been played.
 */
void AudioManager::updateSoundtrack() {
    if (!initialized || Mix_PlayingMusic())
        return;

    currentSong++;
    if (currentSong == soundtrack.end())
        currentSong = soundtrack.begin();
    playSoundtrack();
}

/**
 * Pause the music.
 */
void AudioManager::pauseSoundtrack() {
    Mix_PauseMusic();
}

/**
 * Set global volume.
 * @param val value of volume
 */
void AudioManager::setVolume(const int & val) {
    Mix_Volume(-1,val);
}

/**
 * Set volume of the music
 * @param val value of volume
 */
void AudioManager::setMusicVolume(const int &val) {
    Mix_VolumeMusic(val);
}