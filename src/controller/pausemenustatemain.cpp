#include "pausemenustatemain.h"

#include "../display/drawinformation.h"
#include "pausemenustateparty.h"

PauseMenuStateMain::PauseMenuStateMain(ModelAbstract *model)
    : PauseMenuDrawState(model)
{

}

void PauseMenuStateMain::moveMenuCursor(int x, int y)
{
    currentPos += y;

    if(currentPos > 4)
        currentPos = 0;
    if(currentPos < 0)
        currentPos = 4;
}

PauseMenuDrawState * PauseMenuStateMain::enterMenu()
{
    if(currentPos == 4)
        return new PauseMenuStateParty(model);

    return this;
}

PauseMenuDrawState *PauseMenuStateMain::closeMenu()
{
    return this;
}

void PauseMenuStateMain::drawPauseMenu(std::vector<DrawInformation> *items)
{
    //Options
    DrawInformation info2(7, 7, 2, 1, "", false, "Party");
    items->push_back(info2);
    DrawInformation info3(7, 6, 2, 1, "", false, "Bag");
    items->push_back(info3);
    DrawInformation info4(7, 5, 2, 1, "", false, "DDMM");
    items->push_back(info4);
    DrawInformation info5(7, 4, 2, 1, "", false, "Save");
    items->push_back(info5);
    DrawInformation info6(7, 3, 2, 1, "", false, "Quit");
    items->push_back(info6);
    DrawInformation info7(6, (currentPos + 3), 1, 1, "", false, ">");
    items->push_back(info7);
}
