#ifndef BATTLEMENUSTATEBATTLEOVER_H
#define BATTLEMENUSTATEBATTLEOVER_H

#include "battlemenustate.h"

class BattleMenuStateBattleOver : public BattleMenuState
{
public:
    BattleMenuStateBattleOver(BattleModel * model);
    BattleMenuState * enterMenu();
    BattleMenuState * closeMenu();
    BattleMenuState * passTime(float value);
    void drawBattleMenu(std::vector<DrawInformation> * items);
    BattleMenuState * qrPressed(bool wasQ);

private:
    void drawStatusEffects(std::vector<DrawInformation> *items);
};

#endif // BATTLEMENUSTATEBATTLEOVER_H
