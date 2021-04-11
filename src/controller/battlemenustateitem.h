#ifndef BATTLEMENUSTATEITEM_H
#define BATTLEMENUSTATEITEM_H

#include "battlemenustate.h"

class BattleMenuStateItem : public BattleMenuState
{
public:
    BattleMenuStateItem(BattleModel * model);

    void moveMenuCursor(int x, int y);
    BattleMenuState * enterMenu();
    BattleMenuState * closeMenu();
    BattleMenuState * passTime(float value);
    void drawBattleMenu(std::vector<DrawInformation> * items);
    BattleMenuState * qrPressed(bool wasQ);

private:
    int currentPos = 0;
};

#endif // BATTLEMENUSTATEITEM_H
