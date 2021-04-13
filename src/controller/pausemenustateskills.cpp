#include "pausemenustateskills.h"

#include "../model/modelabstract.h"
#include "pausemenustatemain.h"
#include "../display/drawinformation.h"
#include "../model/attackmodel.h"

PauseMenuStateSkills::PauseMenuStateSkills(ModelAbstract *model)
    : PauseMenuDrawState(model)
{
    for(int i = 0; i < model->playerCharacters.size(); i++)
    {
        numberOfCharacters++;
    }
}

void PauseMenuStateSkills::moveMenuCursor(int x, int y)
{
    if(x > 0 || x < 0)
    {
        cursorPos += x;
        if(cursorPos < 0)
            cursorPos = (model->playerCharacters.at(pagePos)->getAttacks()->size() - 1);
        if(cursorPos > (model->playerCharacters.at(pagePos)->getAttacks()->size() - 1))
            cursorPos = 0;
    }
    else
    {
        cursorPos = cursorPos - (y*5);
        if(cursorPos < 0)
            cursorPos += ((model->playerCharacters.at(pagePos)->getAttacks()->size()));
        if(cursorPos > (model->playerCharacters.at(pagePos)->getAttacks()->size()-1))
            cursorPos -= ((model->playerCharacters.at(pagePos)->getAttacks()->size()));
    }
}

PauseMenuDrawState *PauseMenuStateSkills::enterMenu()
{
    if(model->playerCharacters.at(pagePos)->getAttacks()->at(cursorPos)->isUnlocked())
        return this;

    if((cursorPos%5) == 0)
        return this;

    if(model->playerCharacters.at(pagePos)->getAttacks()->at(cursorPos-1)->isUnlocked())
    {
        if(model->playerCharacters.at(pagePos)->getAP() > (cursorPos%5))
        {
            model->playerCharacters.at(pagePos)->spendAP(cursorPos%5);
            model->playerCharacters.at(pagePos)->getAttacks()->at(cursorPos)->unlock();
        }
    }

    return this;
}

PauseMenuDrawState *PauseMenuStateSkills::closeMenu()
{
    return new PauseMenuStateMain(model);
}

void PauseMenuStateSkills::drawPauseMenu(std::vector<DrawInformation> *items)
{
    //Bottom background for effects
    DrawInformation topTextBox(-700, -375, 1500, 140, "BattleMenuBG", false);
    items->push_back(topTextBox);

    //GaugeMarker
    DrawInformation line1(-400 + (200*(0)), (200 + 20 - (100 * (0))), 900, 10, "GaugeMarker", false);
    items->push_back(line1);
    DrawInformation line2(-500 + (200*(0)), (200 + 20 - (100 * (1))), 1000, 10, "GaugeMarker", false);
    items->push_back(line2);
    DrawInformation line3(-400 + (200*(0)), (200 + 20 - (100 * (2))), 900, 10, "GaugeMarker", false);
    items->push_back(line3);
    DrawInformation line4(-400 + (200*(0)), (200 + 20 - (100 * (2))), 10, 200, "VerticalLine", false);
    items->push_back(line4);

    DrawInformation port(-700, (300 - (0*200)), 200, 200, model->playerCharacters.at(pagePos)->getMenuSpriteKey(), false);
    items->push_back(port);
    DrawInformation port2(-550, (200 - (100)), 50, 50, model->playerCharacters.at(pagePos)->getMenuSpriteKey(), false);
    items->push_back(port2);

    for(int i = 0; i < model->playerCharacters.at(pagePos)->getAttacks()->size(); i++)
    {
        if(model->playerCharacters.at(pagePos)->getAttacks()->at(i)->isUnlocked())
        {
            DrawInformation attackIcon(-300 + (200*(i%5)), (200 - (100 * (i/5))), 50, 50, "SkillIcon", false);
            items->push_back(attackIcon);
        }
        else
        {
            DrawInformation attackIcon(-300 + (200*(i%5)), (200 - (100 * (i/5))), 50, 50, "Locked" + std::to_string(i%5), false);
            items->push_back(attackIcon);
        }
    }

    //Text
    DrawInformation info2(265, (50 + (0*200)), 400, 100, "", false, model->playerCharacters.at(pagePos)->getName()
                          + " [AP: " + std::to_string(model->playerCharacters.at(pagePos)->getAP()) + "]"
                          , true);
    items->push_back(info2);

    DrawInformation attackDesc(0, 760, 1500, 140, "",
                            false, model->playerCharacters.at(pagePos)->getAttacks()->at(cursorPos)->getDescription());
    items->push_back(attackDesc);

    DrawInformation nameDesc(0, 700, 1500, 140, "",
                            false, model->playerCharacters.at(pagePos)->getAttacks()->at(cursorPos)->getName());
    items->push_back(nameDesc);

    DrawInformation infoback(0, 650, 100, 100, "", false, "<Q");
    items->push_back(infoback);
    DrawInformation infoforw(1500, 650, 100, 100, "", false, "R>");
    items->push_back(infoforw);

    DrawInformation info7(468 + (200*(cursorPos%5)), (215 + ((cursorPos/5)*100)), 100, 100, "", false, "V", true, 24.f);
    items->push_back(info7);
}

bool PauseMenuStateSkills::isMain()
{
    return false;
}

void PauseMenuStateSkills::speicalMessage(std::string message)
{
    if(message == "PageForward")
        pagePos++;
    if(message == "PageBack")
        pagePos--;

    if(pagePos > (numberOfCharacters-1))
        pagePos = 0;
    if(pagePos < 0)
        pagePos = (numberOfCharacters-1);
}
