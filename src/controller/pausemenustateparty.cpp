#include "pausemenustateparty.h"

#include "../display/drawinformation.h"
#include "../model/modelabstract.h"
#include "pausemenustatemain.h"

PauseMenuStateParty::PauseMenuStateParty(ModelAbstract *model)
    : PauseMenuDrawState(model)
{

}

void PauseMenuStateParty::moveMenuCursor(int x, int y)
{
    int enableCount = 0;
    for(int i = 0; i < model->playerCharacters.size(); i++)
    {
        if(model->playerCharacters.at(i)->getIsActive())
            enableCount++;
    }

    currentPos -= y;

    if(currentPos < 0)
        currentPos = (enableCount - 1);
    if(currentPos >= enableCount)
        currentPos = 0;
}

PauseMenuDrawState *PauseMenuStateParty::enterMenu()
{
    return this;
}

PauseMenuDrawState *PauseMenuStateParty::closeMenu()
{
    return new PauseMenuStateMain(model);
}

void PauseMenuStateParty::drawPauseMenu(std::vector<DrawInformation> *items)
{
    //Options
    for(int i = 0; i < model->playerCharacters.size(); i++)
    {
        DrawInformation info2(7, (7 - i), 2, 1, "", false, model->playerCharacters.at(i)->getName());
        items->push_back(info2);
    }
    DrawInformation info7(6, (7 - currentPos), 1, 1, "", false, ">");
    items->push_back(info7);
}
