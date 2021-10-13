//
// Created by KRATSTOM on 06.05.2021.
//

#pragma once
#include <map>
#include "Player.h"
#include "../GameObjects/Structures/Towers/ArcherTower.h"
#include "../GameObjects/Structures/Towers/BombTower.h"
class Computer: public Player {
private:
    float buildDelay = 5000;
    float buildDelayCooldown = 0;
    std::map<std::string, Tower *> prefabs;
    Tower * nextTower = nullptr;
    bool buildTower();
    void deserializeTowers(xmlNode * towersNode);
public:
    Computer() noexcept;
    ~Computer() override;
    void start() override;
    void update(const double & deltaTime) override;
    void deserialize(xmlNode *node) override;
};