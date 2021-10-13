//
// Created by KRATSTOM on 01.06.21.
//

#pragma once
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "Logger/Logger.h"
class Config {
private:
    std::string path;
    std::map<std::string, std::vector<std::string>> config;
public:
    Config(const std::string & path);
    std::vector<std::string> getValues(const std::string & key) const;
    void setValues(const std::string & key, const std::vector<std::string> & values);
    void save();
    void load();
};


