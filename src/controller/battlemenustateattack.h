#ifndef BATTLEMENUSTATEATTACK_H
#define BATTLEMENUSTATEATTACK_H

#include "battlemenustate.h"

class BattleMenuStateAttack : public BattleMenuState
{
public:
    BattleMenuStateAttack(BattleModel * model);

    void moveMenuCursor(int x, int y);
    BattleMenuState * enterMenu();
    BattleMenuState * closeMenu();
    BattleMenuState * passTime(float value);
    void drawBattleMenu(std::vector<DrawInformation> * items);

private:
    int currentPosX = 0;
    int currentPosY = 0;

    int currentTarget;

    bool isSelectingTarget = false;
};

#endif // BATTLEMENUSTATEATTACK_H
