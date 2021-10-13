//
// Created by KRATSTOM on 06.05.2021.
//

#include "../GameScene.h"
#include "Computer.h"

Computer::Computer() noexcept
: Player(20, 20) {}

/**
 * Deletes allocated prefabs.
 */
Computer::~Computer() {
    for(auto & it : prefabs)
        delete it.second;
    prefabs.clear();
}

/**
 * Prepares prefabs of towers.
 */
void Computer::start() {
    Player::start();
    auto config = ResourceManager::getConfig("towers");
    try {
        auto tnt = new BombTower();
        prefabs.insert({"bomb_tower", tnt});

        auto archerTower = new ArcherTower();
        prefabs.insert({"archer_tower", archerTower});
        
    } catch(std::exception & e) {
        Logger::severe("Computer::start: ");
        Logger::severe( e.what());
        return;
    }
}

/**
 * Build a tower if cooldown is 0.
 * @param deltaTime 
 */
void Computer::update(const double & deltaTime) {
    Player::update(deltaTime);
    if(!nextTower) {
        int id;
        if(prefabs.size() > 1)
            id = std::rand() % prefabs.size();
        else
            id = 0;
        auto iterator = prefabs.begin();
        std::advance(iterator, id);
        nextTower = iterator->second;
    }
    if(buildDelayCooldown <= 0) {
        if(buildTower()) {
            buildDelayCooldown = buildDelay;
            nextTower = nullptr;
        }
    } else {
        buildDelayCooldown -= (float)deltaTime;
    }
}

/**
 * If computer has enough money, builds a tower.
 * @return 
 */
bool Computer::buildTower() {
    if(!nextTower)
        return false;
    if(money != nextTower->getPrice())
        return false;
    pay(nextTower->getPrice());
    for(auto tile : GameScene::map->getTowerSlots()) {
        auto slot = dynamic_cast<TowerSlot *>(tile->getStructure());
        if(!slot->hasTower()) {
            Logger::info("Tower built");
            auto tower = dynamic_cast<Tower *>(nextTower->clone());
            slot->buildTower(tower);
            return true;
        }
    }
    
    return false;
}

/**
 * Loads data from the save.
 * @param node the root node of the computer's data
 */
void Computer::deserialize(xmlNode *node) {
    Player::deserialize(node);
    auto computerStructure = node->children;
    while(computerStructure) {
        if(computerStructure->type != XML_ELEMENT_NODE) {
            computerStructure = computerStructure->next;
            continue;
        }
        if(xmlStrEqual(computerStructure->name, BAD_CAST "base") == 1) {
            auto baseHealthString = xmlGetProp(computerStructure, BAD_CAST "health");
            int health = std::stoi(reinterpret_cast<const char*>(baseHealthString));
            xmlFree(baseHealthString);
            dynamic_cast<Base*>(GameScene::map->baseTile->getStructure())->setHealth(health);
        } else if(xmlStrEqual(computerStructure->name, BAD_CAST "towers") == 1) {
            deserializeTowers(computerStructure);
        }
        computerStructure = computerStructure->next;
    }
}

/**
 * Loads towers from the save
 * @param towersNode the root node of towers
 */
void Computer::deserializeTowers(xmlNode *towersNode) {
    auto towerNode = towersNode->children;
    while(towerNode) {
        if(towerNode->type != XML_ELEMENT_NODE) {
            towerNode = towerNode->next;
            continue;
        }

        std::string towerName(reinterpret_cast<const char *>(towerNode->name));
        auto it = prefabs.find(towerName);
        if(it == prefabs.end())
            throw std::invalid_argument("Unknown tower " + towerName + " in saveFile");

        auto xString = xmlGetProp(towerNode, BAD_CAST "x");
        auto yString = xmlGetProp(towerNode, BAD_CAST "y");
        auto healthString = xmlGetProp(towerNode, BAD_CAST "health");
        try {
            float x = std::stof(reinterpret_cast<const char *>(xString));
            float y = std::stof(reinterpret_cast<const char *>(yString));
            int health = std::stoi(reinterpret_cast<const char *>(healthString));

            auto mapPos = GameScene::map->screenToMap({x,y});
            auto tile = GameScene::map->getTileAt(mapPos);
            if(!tile->getStructure()) {
                xmlFree(xString);
                xmlFree(yString);
                xmlFree(healthString);
                Logger::warn("Could not instantiate tower " + towerName + " at " + mapPos.toString());
                continue;
            }
            auto tower = dynamic_cast<Tower*>(it->second->clone());
            auto slot = dynamic_cast<TowerSlot *>(tile->getStructure());
            slot->buildTower(tower);
            tower->start();
            tower->setHealth(health);
        } catch(std::exception & e) {
            xmlFree(xString);
            xmlFree(yString);
            xmlFree(healthString);
            throw std::exception(e);
        }

        xmlFree(xString);
        xmlFree(yString);
        xmlFree(healthString);

        towerNode = towerNode->next;
    }
}

