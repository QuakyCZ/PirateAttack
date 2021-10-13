//
// Created by KRATSTOM on 28.03.2021.
//

#include "Logger.h"

bool Logger::debugMode = false;

void Logger::setDebugMode(const bool &val) {
    Logger::debugMode = val;
}

/**
 * Set the color of the log.
 * @param prefix the type of prefix
 */
void Logger::printColor(LogType prefix) {
    switch (prefix) {
        case INFO:
            std::cout << Color(Color::Code::BLUE);
            break;
        case WARN:
            std::cout << Color(Color::Code::YELLOW);
            break;
        case SEVERE:
            std::cout << Color(Color::Code::RED);
            break;
    }
}

/**
 * Print current timestamp. Format: hh:mm:ss
 */
void Logger::printTimeStamp() {
    std::time_t t = std::time(0);
    std::tm * time = std::localtime(&t);
    std::cout << (time->tm_hour < 10 ? "0" : "") << time->tm_hour
        << ":" << (time->tm_min < 10 ? "0" : "") << time->tm_min
        << ":" << (time->tm_sec < 10 ? "0" : "") << time->tm_sec;
}

/**
 * Print prefix to the console. Format: [PREFIX]
 * @param prefix the type of prefix to print.
 */
void Logger::printPrefix(LogType prefix) {
    std::cout << "[";
    switch (prefix) {
        case INFO:
            std::cout << "INFO";
            break;
        case WARN:
            std::cout << "WARN";
            break;
        case SEVERE:
            std::cout << "SEVERE";
            break;
    }

    std::cout << "]";
}

/**
 * Print a text to the console if debug mode is enabled.
 * @param prefix the type of the prefix
 * @param text the text to print
 */
void Logger::log(LogType prefix, const std::string &text) {
    if(!debugMode)
        return;
    printColor(prefix);
    printTimeStamp();
    std::cout << " ";
    printPrefix(prefix);
    std::cout << " " << text << Color(Color::Code::DEFAULT) << std::endl;
}

/**
 * Print info to the console.
 * @param text the text to print
 */
void Logger::info(const std::string &text) {
    log(INFO, text);
}

/**
 * Print warning to the console.
 * @param text the text to print
 */
void Logger::warn(const std::string &text) {
    log(WARN, text);
}

/**
 * Print severe / error to the console.
 * @param text the text to print
 */
void Logger::severe(const std::string &text) {
    log(SEVERE, text);
}






