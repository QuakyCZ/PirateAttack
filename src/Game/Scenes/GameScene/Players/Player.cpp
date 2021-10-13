//
// Created by KRATSTOM on 06.05.2021.
//

#include "Player.h"

Player::Player(int money, int moneyPerSecond)
: money(money), moneyPerSecond(moneyPerSecond) {

}

/**
 * Decreases amount of money of the player if he has enough.
 * @param amount the amount to pay.
 * @return true if the payment succeeded, false if the player does not have enough money.
 */
bool Player::pay(const int &amount) {
    if(money - amount < 0)
        return false;
    money -= amount;
    return true;
}


void Player::update(const double &deltaTime) {
    moneyTimer -= deltaTime;
    if(moneyTimer <= 0) {
        moneyTimer = 1000;
        money += moneyPerSecond;
    }
}

/**
 * Save money
 * @param writer 
 */
void Player::serialize(xmlTextWriterPtr &writer) const {
    xmlTextWriterStartElement(writer, BAD_CAST "player");
    xmlTextWriterWriteAttribute(writer, BAD_CAST "money", BAD_CAST std::to_string(money).c_str());
    xmlTextWriterEndElement(writer);
}

/**
 * Load money from the save.
 * @param node 
 */
void Player::deserialize(xmlNode * node) {
    auto moneyString = xmlGetProp(node, BAD_CAST "money");
    money = std::stoi(reinterpret_cast<const char *>(moneyString));
    xmlFree(moneyString);
}

/**
 * Get data from the map config
 * @param node the root node of player
 */
void Player::deserializeConfig(xmlNode *node) {
    auto configProp = node->children;
    while(configProp) {
        if(configProp->type != XML_ELEMENT_NODE) {
            configProp = configProp->next;
            continue;
        }
        
        if(xmlStrEqual(configProp->name, BAD_CAST "money")) {
            auto startMoney = xmlGetProp(configProp, BAD_CAST "start");
            money = std::stoi(reinterpret_cast<const char*>(startMoney));
            xmlFree(startMoney);
            
            auto mps = xmlGetProp(configProp, BAD_CAST "per_sec");
            moneyPerSecond = std::stoi(reinterpret_cast<const char*>(mps));
            xmlFree(mps);
            return;
        }
        
        configProp = configProp->next;
    }
}
