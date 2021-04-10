#ifndef PAUSEMENUSTATEEQUIPMENT_H
#define PAUSEMENUSTATEEQUIPMENT_H

#include "pausemenustate.h"

#include "../model/equipmentmodel.h"
#include "../model/playercharacterstats.h"

class PauseMenuStateEquipment : public PauseMenuDrawState
{
public:
    PauseMenuStateEquipment(ModelAbstract * model);

    void moveMenuCursor(int x, int y);
    PauseMenuDrawState * enterMenu();
    PauseMenuDrawState * closeMenu();
    void drawPauseMenu(std::vector<DrawInformation> * items);

    bool isMain();

    void speicalMessage(std::string message);

private:
    void drawEquipmentList(std::vector<DrawInformation> * items);

    int currentPosY = 0;
    int currentPosX = 0;

    bool listIsOpen = false;

    std::string focusType;
    int focusPartyMemberLimit = 0;

    int equipmentPos = 0;
    int focusNumberOfItems = 0;
    int focusLimit = 0;

    std::vector<int> indexesOfFocusType;
    int numberOfCharatersInput = 0;
    PlayerCharacterStats* characters[4];

    bool selectedAccessory1 = false;

};

#endif // PAUSEMENUSTATEEQUIPMENT_H
