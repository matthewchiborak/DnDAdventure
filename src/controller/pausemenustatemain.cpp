#include "pausemenustatemain.h"

#include "../display/drawinformation.h"
#include "pausemenustateparty.h"
#include "pausemenustateequipment.h"
#include "pausemenustatebag.h"
#include "pausemenustatemonstermanual.h"
#include "pausemenustateskills.h"
#include <QCoreApplication>

PauseMenuStateMain::PauseMenuStateMain(ModelAbstract *model)
    : PauseMenuDrawState(model)
{

}

void PauseMenuStateMain::moveMenuCursor(int x, int y)
{
    currentPos += y;

    if(currentPos > 5)
        currentPos = 0;
    if(currentPos < 0)
        currentPos = 5;
}

PauseMenuDrawState * PauseMenuStateMain::enterMenu()
{
    if(currentPos == 5)
        return new PauseMenuStateParty(model);
    if(currentPos == 4)
        return new PauseMenuStateSkills(model);
    if(currentPos == 3)
        return new PauseMenuStateEquipment(model);
    if(currentPos == 2)
        return new PauseMenuStateBag(model);
    if(currentPos == 1)
        return new PauseMenuStateMonsterManual(model);
    if(currentPos == 0)
    {
        QCoreApplication::quit();
        return this;
    }

    return this;
}

PauseMenuDrawState *PauseMenuStateMain::closeMenu()
{
    return this;
}

void PauseMenuStateMain::drawPauseMenu(std::vector<DrawInformation> *items)
{
    //Options
    DrawInformation info2(700, 250, 200, 100, "", false, "Party");
    items->push_back(info2);
    DrawInformation info9(700, 300, 200, 100, "", false, "Skills");
    items->push_back(info9);
    DrawInformation info3(700, 350, 250, 100, "", false, "Equipment");
    items->push_back(info3);
    DrawInformation info4(700, 400, 200, 100, "", false, "Bag");
    items->push_back(info4);
    DrawInformation info5(700, 450, 200, 100, "", false, "DDMM");
    items->push_back(info5);
    DrawInformation info6(700, 500, 200, 100, "", false, "Quit");
    items->push_back(info6);
    DrawInformation info7(600, 500 - (currentPos*50), 100, 100, "", false, ">");
    items->push_back(info7);
}

bool PauseMenuStateMain::isMain()
{
    return true;
}

void PauseMenuStateMain::speicalMessage(std::string message)
{

}
