#ifndef BATTLEMENUSTATE_H
#define BATTLEMENUSTATE_H

class BattleModel;
class DrawInformation;

#include <vector>

class BattleMenuState
{
public:
    BattleMenuState(BattleModel * model);

    virtual void moveMenuCursor(int x, int y);
    virtual BattleMenuState * enterMenu();
    virtual BattleMenuState * closeMenu();
    virtual BattleMenuState * passTime(float value);
    virtual void drawBattleMenu(std::vector<DrawInformation> * items);

protected:
    BattleModel * model;

};

#endif // BATTLEMENUSTATE_H
