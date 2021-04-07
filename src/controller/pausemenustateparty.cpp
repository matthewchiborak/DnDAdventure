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
    if(!swapping)
    {
        firstSwapSelection = currentPos;
        swapping = true;
    }
    else
    {
        PlayerCharacterStats * temp1 = model->playerCharacters.at(firstSwapSelection);
        PlayerCharacterStats * temp2 = model->playerCharacters.at(currentPos);
        model->playerCharacters.at(firstSwapSelection) = temp2;
        model->playerCharacters.at(currentPos) = temp1;
        swapping = false;
    }

    return this;
}

PauseMenuDrawState *PauseMenuStateParty::closeMenu()
{
    return new PauseMenuStateMain(model);
}

void PauseMenuStateParty::drawPauseMenu(std::vector<DrawInformation> *items)
{
    //images first
    for(int i = 0; i < model->playerCharacters.size(); i++)
    {
        DrawInformation port(-700, (300 - (i*200)), 200, 200, model->playerCharacters.at(i)->getMenuSpriteKey(), false);
        items->push_back(port);
    }

    //Text second
    for(int i = 0; i < model->playerCharacters.size(); i++)
    {
        //150 - 850 , + 450
        //DrawInformation port(-700, (300 - (i*200)), 200, 200, model->playerCharacters.at(i)->getMenuSpriteKey(), false);
        //items->push_back(port);
        DrawInformation info2(265, (50 + (i*200)), 200, 100, "", false, model->playerCharacters.at(i)->getName(), true);
        items->push_back(info2);
        DrawInformation info3(450, (50 + (i*200)), 1000, 100, "", false,
                              "Level: " + std::to_string(model->playerCharacters.at(i)->getLevel()) + "     XP: " + std::to_string(model->playerCharacters.at(i)->getXP())
                              + "   [HP: " + std::to_string(model->playerCharacters.at(i)->getCurrentHealth()) + " / " + std::to_string(model->playerCharacters.at(i)->getMaxHealth())
                              + "] [MP: " + std::to_string(model->playerCharacters.at(i)->getCurrentMP()) + " / " + std::to_string(model->playerCharacters.at(i)->getMaxMP())
                              + "]",
                              true, 42.f);
        items->push_back(info3);
        DrawInformation info4(450, (150 + (i*200)), 1400, 100, "", false,
                              "[Att: " + std::to_string(model->playerCharacters.at(i)->getAttack())
                              + "] [Def: " + std::to_string(model->playerCharacters.at(i)->getDefence())
                              + "] [Magic: " + std::to_string(model->playerCharacters.at(i)->getMagicAttack())
                              + "] [MagicDef: " + std::to_string(model->playerCharacters.at(i)->getMagicDefence())
                              + "] [Speed: " + std::to_string(model->playerCharacters.at(i)->getSpeed())
                              + "]",
                              true,
                              36.f
                              );
        items->push_back(info4);
    }
    DrawInformation info7(0, (50 + (currentPos*200)), 100, 100, "", false, ">", true);
    items->push_back(info7);
    if(swapping)
    {
        DrawInformation info7(0, (50 + (firstSwapSelection*200)), 100, 100, "", false, "?", true);
        items->push_back(info7);
    }
}
