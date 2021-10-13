//
// Created by KRATSTOM on 06.05.2021.
//

#include "Goblin.h"
#include "../../GameScene.h"
int Goblin::count = 0;

Goblin::Goblin(): Unit("goblin") {}
Goblin::Goblin(Goblin *other): Unit(other) {}

/**
 * @return a deep clone of this.
 */
GameObject *Goblin::clone() {
    return new Goblin(this);
}

/**
 * Set the BASE as next target.
 */
void Goblin::getNextTarget() {
    if(GameScene::map->baseTile->getStructure())
        target = dynamic_cast<LivingStructure *>(GameScene::map->baseTile->getStructure());
}

/**
 * Destroy self when the target (BASE) has been destroyed.
 */
void Goblin::onTargetDestroyed() {
    Unit::onTargetDestroyed();
    destroyed = true;
    GameScene::getPlayer()->unregisterUnit(this);
}



