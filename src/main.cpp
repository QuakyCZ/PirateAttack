//
// Created by KRATSTOM on 28.03.2021.
//
#include "Game/Game.h"

/**
 * Parse app path from argv
 * @param argv path to executable program
 * @return a string with the path to the game folder
 */
std::string getAppPath(char * argv[]) {
    std::string executablePath = std::string(argv[0]);
    size_t lastIndex = executablePath.find_last_of('/');
    std::string appPath = executablePath.substr(0, lastIndex);
    Logger::info("Application directory: " + appPath);
    return appPath;
}

/**
 * Update and render game
 * @param game the instance of the game
 * @param deltaTime the delta time
 */
void updateGame(Game & game, const float & deltaTime) {
    game.pollEvents();
    game.update(deltaTime);
    game.render();
}

/**
 * Update delta time
 * @param deltaTime - the time of the last frame in ms
 * @param last the absolute time to the last frame
 */
void updateDeltaTime(float & deltaTime, const Uint32 & last) {
    Uint32 now = SDL_GetPerformanceCounter();
    deltaTime = (float)((float)(now - last)*1000.0F / (float)SDL_GetPerformanceFrequency() );
}

/**
 * Update frame time and wait if the loop is faster.
 * @param frameTime 
 * @param frameStart 
 * @param frameDelay 
 */
void updateFrameTime(Uint32 & frameTime, const Uint32 & frameStart, const Uint32 & frameDelay) {
    frameTime = SDL_GetTicks() - frameStart;

    if(frameDelay > frameTime){
        SDL_Delay(frameDelay - frameTime);
    }
}

/**
 * Main function with the main loop of the game.
 * @param argc path to the program
 * @param argv program arguments
 * @return the exit code.
 */
int main(int argc, char* argv[]) {

    if(argc > 1 && std::string(argv[1]) == "DEBUG")
        Logger::setDebugMode(true);

    Logger::info("Args " + std::to_string(argc));

    Logger::info("Starting the game Pirate Attack");
    try {
        Game game(getAppPath(argv));
        const int FPS = 60;
        const int frameDelay = 1000 / FPS;

        Uint32 frameStart;
        Uint32 frameTime;
        Uint64 now = SDL_GetPerformanceCounter();
        Uint64 last = 0;
        float deltaTime = 0;
        Logger::info("Starting game loop");
        while(game.isRunning()) {
            last = now;
            now = SDL_GetPerformanceCounter();

            frameStart = SDL_GetTicks();

            updateDeltaTime(deltaTime, last);
            updateGame(game, deltaTime);

            updateFrameTime(frameTime, frameStart, frameDelay);
        }
    } catch (std::exception & e) {
        Logger::severe("Unhandled exception occurred.");
        Logger::severe(e.what());
    }
    Logger::info("Closed Pirate Attack");
    return 0;
}