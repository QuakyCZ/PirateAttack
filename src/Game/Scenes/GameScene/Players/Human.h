//
// Created by KRATSTOM on 06.05.2021.
//
#pragma once

#include <map>

#include "Player.h"
#include "../../../../Engine/UI/Text.h"
#include "../GameObjects/Units/Unit.h"
#include "../GameObjects/Units/Goblin.h"
#include "../GameObjects/Units/Troll.h"


class Human: public Player {
private:
    Text * moneyText = nullptr;
    Text * scoreText = nullptr;
    std::string summoningUnitName;
    std::vector<Unit *> units;
    std::map<std::string, Unit*> prefabs;
    std::map<std::string, int> unitCounts;
    int score = 0;
public:
    Human() = default;
    explicit Human(Text * moneyText, Text * scoreText);
    ~Human() override;
    
    void update(const double & deltaTime) override;
    bool isSummoning() const;
    void summon(const std::string & name);
    void cancelSummoning();
    bool completeSummoning(GameObject * parent, const Vector2D & position);
    std::vector<Unit *> getUnits() const {
        return units;
    }
    void unregisterUnit(Unit * unit);

    void registerScore(const int & score);
    int getScore() const {
        return score;
    }
    
    void serialize(xmlTextWriterPtr &writer) const override;
    void deserialize(xmlNode *node) override;
    void deserializeConfig(xmlNode *node) override;
    
    int getCountOfUnit(const std::string & unitName) const;
    
    int getMaxCountOfUnit(const std::string & unitName) const;
};
