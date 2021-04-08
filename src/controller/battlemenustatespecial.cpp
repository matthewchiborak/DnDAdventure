#include "battlemenustatespecial.h"

BattleMenuStateSpecial::BattleMenuStateSpecial(BattleModel *model)
    : BattleMenuState(model)
{

}

void BattleMenuStateSpecial::moveMenuCursor(int x, int y)
{

}

BattleMenuState *BattleMenuStateSpecial::enterMenu()
{
    return nullptr;
}

BattleMenuState *BattleMenuStateSpecial::closeMenu()
{
    return nullptr;
}

BattleMenuState *BattleMenuStateSpecial::passTime(float value)
{
    return this;
}

void BattleMenuStateSpecial::drawBattleMenu(std::vector<DrawInformation> *items)
{

}
