#ifndef BATTLEMENUSTATEFLEE_H
#define BATTLEMENUSTATEFLEE_H

#include "battlemenustate.h"

class BattleMenuStateFlee : public BattleMenuState
{
public:
    BattleMenuStateFlee(BattleModel * model);
    BattleMenuState * enterMenu();
    BattleMenuState * closeMenu();
    BattleMenuState * passTime(float value);
    void drawBattleMenu(std::vector<DrawInformation> * items);
    BattleMenuState * qrPressed(bool wasQ);

private:
    void drawStatusEffects(std::vector<DrawInformation> *items);
};

#endif // BATTLEMENUSTATEFLEE_H
