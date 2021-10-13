//
// Created by KRATSTOM on 28.03.2021.
//

#pragma once

#include <string>
#include <iostream>
#include <ctime>
#include "Color.h"

class Logger {

private:
    enum LogType {INFO, WARN, SEVERE};
    static bool debugMode;
    
    static void printColor(LogType prefix);

    static void printTimeStamp();

    static void printPrefix(LogType prefix);
public:
    static void setDebugMode(const bool & val);
    
    static void log(LogType type, const std::string & text);

    static void info(const std::string & text);

    static void warn(const std::string & text);
    
    static void severe(const std::string & text);
};
