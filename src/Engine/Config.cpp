//
// Created by KRATSTOM on 01.06.21.
//


#include "Config.h"
using namespace std;
Config::Config(const std::string & path): path(path) {
    load();
}

/**
 * @param key the key of values
 * @return values of the key or empty vector if not found.
 */
std::vector<std::string> Config::getValues(const std::string &key) const {
    if(config.find(key) == config.end())
        return std::vector<std::string>();
    return config.find(key)->second;
}

/**
 * Change or insert config values.
 * @param key the key of values
 * @param values the values to change / insert
 */
void Config::setValues(const std::string & key, const std::vector<std::string> & values) {
    if(config.find(key) != config.end())
        config[key] = values;
    else
        config.insert({key, values});
}

/**
 * Saves data from the map into the config file.
 */
void Config::save() {
    ofstream out(path);
    if(!out.is_open())
        throw runtime_error("Could not save config file " + path);
    for(auto & it : config) {
        out << it.first << " ";
        for (size_t i = 0; i < it.second.size(); ++i) {
            out << it.second[i];
            if (i < it.second.size() - 1)
                out << " ";
            out << endl;
        }
    }
    out.close();
}

/**
 * Loads data from config into a map.
 */
void Config::load() {
    ifstream in(path);
    if(in.is_open()) {
        string line, segment;
        while(getline(in, line)) {
            if(in.fail()) {
                in.close();
                throw runtime_error("Error has occurred while reading config file " + path);
            }
            stringstream lineStream(line);
            vector<string> seglist;
            if(line[line.find_first_not_of(' ')] == '#' || line[line.find_first_not_of('\t')] == '#')
                continue;
            while (getline(lineStream, segment, ' ')) {
                seglist.push_back(segment);
            }
            if(seglist.size() == 0)
                continue;
            if(seglist.size() == 1)
                throw invalid_argument("Config " + path + " has no value at line " + to_string(config.size() + 1));
                
            string key = seglist[0];
            if(config.find(key) != config.end())
                throw invalid_argument("Config " + path + " has duplicate keys.");
            
            seglist.erase(seglist.begin());
            config.insert({key, seglist});
        }        
        in.close();
    } else {
        throw runtime_error("Could not open config file " + path);
    }
}

