#ifndef BATTLEMENUSTATESPECIAL_H
#define BATTLEMENUSTATESPECIAL_H

#include "battlemenustate.h"

class BattleMenuStateSpecial : public BattleMenuState
{
public:
    BattleMenuStateSpecial(BattleModel * model);

    void moveMenuCursor(int x, int y);
    BattleMenuState * enterMenu();
    BattleMenuState * closeMenu();
    BattleMenuState * passTime(float value);
    void drawBattleMenu(std::vector<DrawInformation> * items);
    BattleMenuState * qrPressed(bool wasQ);

private:
    int currentPos = 0;
    int accessPos = 0;

    bool isSelecting = false;

    void drawEnemyStatusEffect(std::vector<DrawInformation> * items);
};

#endif // BATTLEMENUSTATESPECIAL_H
