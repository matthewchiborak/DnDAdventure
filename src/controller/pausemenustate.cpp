#include "pausemenustate.h"


PauseMenuDrawState::PauseMenuDrawState(ModelAbstract *model)
{
    this->model = model;
}

void PauseMenuDrawState::moveMenuCursor(int x, int y)
{

}

PauseMenuDrawState * PauseMenuDrawState::enterMenu()
{
        return nullptr;
}

PauseMenuDrawState *PauseMenuDrawState::closeMenu()
{
    return nullptr;
}

void PauseMenuDrawState::drawPauseMenu(std::vector<DrawInformation> *items)
{

}
