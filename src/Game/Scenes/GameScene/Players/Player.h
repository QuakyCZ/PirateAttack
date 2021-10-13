//
// Created by KRATSTOM on 06.05.2021.
//

#pragma once
#include <string>
#include <libxml2/libxml/xmlreader.h>
#include <libxml2/libxml/xmlwriter.h>

class Player {
protected:
    int money = 0;
    int moneyPerSecond = 20;
    double moneyTimer = 1000;
public:
    Player() = default;
    Player(int money, int moneyPerSecond);
    virtual ~Player() = default;
    
    virtual void start() {}
    virtual void update(const double & deltaTime);

    virtual bool pay(const int & amount);
    
    int getMoney() const {
        return money;
    }
    
    virtual void serialize(xmlTextWriterPtr & writer) const;
    virtual void deserialize(xmlNode * node);
    virtual void deserializeConfig(xmlNode * node);
};