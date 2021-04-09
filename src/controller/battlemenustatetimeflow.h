#ifndef BATTLEMENUSTATETIMEFLOW_H
#define BATTLEMENUSTATETIMEFLOW_H

#include "battlemenustate.h"

class BattleMenuStateTimeFlow : public BattleMenuState
{
public:
    BattleMenuStateTimeFlow(BattleModel * model);

    void moveMenuCursor(int x, int y);
    BattleMenuState * enterMenu();
    BattleMenuState * closeMenu();
    BattleMenuState * passTime(float value);
    void drawBattleMenu(std::vector<DrawInformation> * items);

private:
    long long theTimeNow;
    long long timeOfLastEvent;
    double elapsed_millies;

    void drawStatusEffects(std::vector<DrawInformation> * items);
};

#endif // BATTLEMENUSTATETIMEFLOW_H
