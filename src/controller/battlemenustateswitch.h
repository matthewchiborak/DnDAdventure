#ifndef BATTLEMENUSTATESWITCH_H
#define BATTLEMENUSTATESWITCH_H

#include "battlemenustate.h"

class BattleMenuStateSwitch : public BattleMenuState
{
public:
    BattleMenuStateSwitch(BattleModel * model);

    void moveMenuCursor(int x, int y);
    BattleMenuState * enterMenu();
    BattleMenuState * closeMenu();
    BattleMenuState * passTime(float value);
    void drawBattleMenu(std::vector<DrawInformation> * items);

private:
    int currentPos = 0;
};

#endif // BATTLEMENUSTATESWITCH_H
