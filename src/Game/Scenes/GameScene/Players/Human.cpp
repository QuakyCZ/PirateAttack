//
// Created by KRATSTOM on 06.05.2021.
//

#include "Human.h"
#include "../GameScene.h"

/**
 * Constructor of Human. Prepares prefabs of units.
 * @param moneyText a pointer to the money text
 * @param scoreText a pointer to the score text
 */
Human::Human(Text * moneyText, Text * scoreText)
: Player(0, 0){
    this->moneyText = moneyText;
    this->scoreText = scoreText;
    prefabs.clear();
    prefabs.insert({"goblin", new Goblin()});
    prefabs.insert({"troll", new Troll()});
    
    unitCounts.insert({"goblin", 0});
    unitCounts.insert({"troll", 0});
}

Human::~Human() {
    for(auto & it : prefabs)
        delete it.second;
    prefabs.clear();
}

/**
 * Update the text with money
 * @param deltaTime 
 */
void Human::update(const double & deltaTime) {
    Player::update(deltaTime);
    if(moneyText)
        moneyText->setText("Money: " + std::to_string(money));    
    

}

/**
 * @return true if player is now summoning a unit.
 */
bool Human::isSummoning() const {
    return !summoningUnitName.empty();
}

/**
 * Set a unit to be summoned next.
 * @param name the name of the unit to summon 
 */
void Human::summon(const std::string & name) {
    summoningUnitName = name;
}

/**
 * Cancel summoning of an unit
 */
void Human::cancelSummoning() {
    summoningUnitName.clear();
}

/**
 * Instantiate the unit and place it into the battlefield
 * @param parent the parent of the unit
 * @param position the position of the unit
 */
bool Human::completeSummoning(GameObject * parent, const Vector2D & position) {
    if(!isSummoning()) 
        return false;
    
    auto unitPrefabIterator = prefabs.find(summoningUnitName);
    if(unitPrefabIterator == prefabs.end()) {
        Logger::severe("Unit " + summoningUnitName + " is not in prefabs.");
        summoningUnitName.clear();
        return false;
    }
    
    auto unitPrefab = unitPrefabIterator->second;
    int max = unitPrefab->getMaxAmount();
    
    if(unitCounts[summoningUnitName] == max) {
        Logger::warn("Player has summoned max number of " + summoningUnitName);
        summoningUnitName.clear();
        return false;
    }
       
    
    if(pay(unitPrefab->getPrice())) {
        auto go = dynamic_cast<Unit*>(unitPrefab->clone());
        go->setParent(parent);
        go->setAbsolutePosition(position);
        go->getSprite()->setLayer(100);
        units.push_back(go);
        go->start();
        ++unitCounts[summoningUnitName];
    } else {
        Logger::warn("Player does not have enough money to summon the unit.");
        summoningUnitName.clear();
        return false;
    }

    summoningUnitName.clear();
    return true;
}

/**
 * If a unit was killed, remove it from the vector.
 * @param unit The unit that was killed.
 */
void Human::unregisterUnit(Unit *unit) {
    for(auto iterator = units.begin(); iterator != units.end(); ++iterator) {
        if(*iterator == unit) {
            units.erase(iterator);
            break;
        }
    }

    if(units.empty()) {
        for(auto & it : prefabs) {
            if(unitCounts[it.first] != it.second->getMaxAmount())
                return;
        }
        GameScene::onComputerWin();
    }
}

/**
 * Add amount of score.
 * @param value the value to add
 */
void Human::registerScore(const int & value) {
    score += value;
    scoreText->setText("Score: " + std::to_string(score));
}

/**
 * Save money, score and units. 
 * @param writer 
 */
void Human::serialize(xmlTextWriterPtr &writer) const {
    xmlTextWriterStartElement(writer, BAD_CAST "human");
    xmlTextWriterWriteAttribute(writer, BAD_CAST "money", BAD_CAST std::to_string(money).c_str());
    xmlTextWriterWriteAttribute(writer, BAD_CAST "score", BAD_CAST std::to_string(score).c_str());
    xmlTextWriterStartElement(writer, BAD_CAST "units");
    for(auto & it : unitCounts) {
        xmlTextWriterWriteAttribute(writer, BAD_CAST it.first.c_str(), BAD_CAST std::to_string(it.second).c_str());
    }
    for(auto unit : units) {
        unit->serialize(writer);
    }    
    xmlTextWriterEndElement(writer); //units
    xmlTextWriterEndElement(writer); //human
}

/**
 * Load money, score and units from the save.
 * @param node 
 */
void Human::deserialize(xmlNode *node) {
    Player::deserialize(node);
    auto scoreString = xmlGetProp(node, BAD_CAST "score");
    score = std::stoi(reinterpret_cast<const char *>(scoreString));
    xmlFree(scoreString);
    auto unitsRoot = node->children;
    while(unitsRoot && xmlStrEqual(unitsRoot->name, BAD_CAST "units") == 0)
        unitsRoot = unitsRoot->next;
    
    if(!unitsRoot)
        return;
    
    for(auto & it : unitCounts) {
        auto count = xmlGetProp(unitsRoot, BAD_CAST it.first.c_str());
        if(!count)
            continue;
        it.second = std::stoi(reinterpret_cast<const char*>(count));
        xmlFree(count);
    }
    
    auto unitNode = unitsRoot->children;
    while(unitNode) {
        if(unitNode->type != XML_ELEMENT_NODE) {
            unitNode = unitNode->next;
            continue;
        }
        std::string unitName(reinterpret_cast<const char *>(unitNode->name));
        auto unitIterator = prefabs.find(unitName);
        if(unitIterator == prefabs.end()) {
            Logger::warn("Skipped unknown unit " + unitName);
            unitNode = unitNode->next;
            continue;
        }
        int health;
        Vector2D pos;
        
        auto healthString = xmlGetProp(unitNode, BAD_CAST "health");
        auto xString = xmlGetProp(unitNode, BAD_CAST "x");
        auto yString = xmlGetProp(unitNode, BAD_CAST "y");
        try {
            health = std::stoi(reinterpret_cast<const char *>(healthString));
            pos.x = std::stof(reinterpret_cast<const char *>(xString));
            pos.y = std::stof(reinterpret_cast<const char *>(yString));
        } catch(std::invalid_argument & e) {
            xmlFree(healthString);
            xmlFree(xString);
            xmlFree(yString);
            throw e;
        } catch(std::out_of_range & e) {
            xmlFree(healthString);
            xmlFree(xString);
            xmlFree(yString);
            throw e;
        }
        
        xmlFree(healthString);
        xmlFree(xString);
        xmlFree(yString);
        
        auto unit = dynamic_cast<Unit*>(unitIterator->second->clone());
        units.push_back(unit);
        unit->setParent(GameScene::map);
        unit->setAbsolutePosition(pos);
        unit->getSprite()->setLayer(10);
        unit->start();
        unit->setHealth(health);
        
        unitNode = unitNode->next;
    }
}

/**
 * Get values from map config
 * @param node the root node of the human
 */
void Human::deserializeConfig(xmlNode *node) {
    Player::deserializeConfig(node);
    auto configProp = node->children;
    while(configProp) {
        if(configProp->type != XML_ELEMENT_NODE) {
            configProp = configProp->next;
            continue;
        }

        if(xmlStrEqual(configProp->name, BAD_CAST "units")) {
            for(auto & it : prefabs) {
                auto maxCountCnf = xmlGetProp(configProp, BAD_CAST it.first.c_str());
                if(!maxCountCnf)
                    continue;
                int count;
                try {
                    count = std::stoi(reinterpret_cast<const char *>(maxCountCnf));
                } catch(std::exception & e) {
                    xmlFree(maxCountCnf);
                    throw e;
                }
                it.second->setMaxAmount(count);
                xmlFree(maxCountCnf);
            }
            return;
        }

        configProp = configProp->next;
    }
}

/**
 * @param unitName the name of the unit
 * @return Current count of the unit with the name. If the unit does not exist, returns -1.
 */
int Human::getCountOfUnit(const std::string &unitName) const {
    auto it = unitCounts.find(unitName);
    if(it == unitCounts.end())
        return -1;
    return it->second;
}

/**
 * @param unitName the name of the unit
 * @return the maximum number of units of a name. If the unit does not exist, returns -1.
 */
int Human::getMaxCountOfUnit(const std::string &unitName) const {
    auto it = prefabs.find(unitName);
    if(it == prefabs.end())
        return -1;
    return it->second->getMaxAmount();
}