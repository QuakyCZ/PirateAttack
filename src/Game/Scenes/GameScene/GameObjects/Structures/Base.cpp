//
// Created by KRATSTOM on 31.05.21.
//

#include "Base.h"
#include "../../GameScene.h"
void Base::onDestroy() {
    LivingStructure::onDestroy();
    GameScene::onHumanWin();
}

/**
 * Save base info (health) to the xml file
 * @param writer the writer of the xml file
 */
void Base::serialize(xmlTextWriterPtr &writer) {
    xmlTextWriterStartElement(writer, BAD_CAST "base");
    xmlTextWriterWriteAttribute(writer, BAD_CAST "health", BAD_CAST std::to_string(health).c_str());
    xmlTextWriterEndElement(writer);
}
