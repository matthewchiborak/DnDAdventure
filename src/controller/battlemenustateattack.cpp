#include "battlemenustateattack.h"

BattleMenuStateAttack::BattleMenuStateAttack(BattleModel *model)
    : BattleMenuState(model)
{

}

void BattleMenuStateAttack::moveMenuCursor(int x, int y)
{

}

BattleMenuState *BattleMenuStateAttack::enterMenu()
{
    return nullptr;
}

BattleMenuState *BattleMenuStateAttack::closeMenu()
{
    return nullptr;
}

BattleMenuState *BattleMenuStateAttack::passTime(float value)
{
    return this;
}

void BattleMenuStateAttack::drawBattleMenu(std::vector<DrawInformation> *items)
{

}
