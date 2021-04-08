#include "battlemenustate.h"


BattleMenuState::BattleMenuState(BattleModel *model)
{
    this->model = model;
}

void BattleMenuState::moveMenuCursor(int x, int y)
{

}

BattleMenuState *BattleMenuState::enterMenu()
{
    return nullptr;
}

BattleMenuState *BattleMenuState::closeMenu()
{
    return nullptr;
}

BattleMenuState *BattleMenuState::passTime(float value)
{
    return nullptr;
}

void BattleMenuState::drawBattleMenu(std::vector<DrawInformation> *items)
{

}
