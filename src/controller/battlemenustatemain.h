#ifndef BATTLEMENUSTATEMAIN_H
#define BATTLEMENUSTATEMAIN_H

#include "battlemenustate.h"

class BattleMenuStateMain : public BattleMenuState
{
public:
    BattleMenuStateMain(BattleModel * model);

    void moveMenuCursor(int x, int y);
    BattleMenuState * enterMenu();
    BattleMenuState * closeMenu();
    BattleMenuState * passTime(float value);
    void drawBattleMenu(std::vector<DrawInformation> * items);

private:
    int currentPos = 4;

    void drawStatusEffects(std::vector<DrawInformation> *items);
};

#endif // BATTLEMENUSTATEMAIN_H
