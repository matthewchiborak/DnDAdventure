#ifndef BATTLEMENUSTATEACCESS_H
#define BATTLEMENUSTATEACCESS_H

#include "battlemenustate.h"

class BattleMenuStateAccess : public BattleMenuState
{
public:
    BattleMenuStateAccess(BattleModel * model);

    void moveMenuCursor(int x, int y);
    BattleMenuState * enterMenu();
    BattleMenuState * closeMenu();
    BattleMenuState * passTime(float value);
    void drawBattleMenu(std::vector<DrawInformation> * items);


};

#endif // BATTLEMENUSTATEACCESS_H
