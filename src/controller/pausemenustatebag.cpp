#include "pausemenustatebag.h"

#include "pausemenustatemain.h"
#include "../display/drawinformation.h"
#include "../model/modelabstract.h"

#include <string>

PauseMenuStateBag::PauseMenuStateBag(ModelAbstract *model)
    : PauseMenuDrawState(model)
{
    for(int i = 0; i < model->playerCharacters.size(); i++)
    {
        if(!model->playerCharacters.at(i)->getIsActive())
            continue;

        if(model->playerCharacters.at(i)->getWeapon() != nullptr)
            equippedItems.push_back(model->playerCharacters.at(i)->getWeapon()->getIndexInBag());
        if(model->playerCharacters.at(i)->getArmor() != nullptr)
            equippedItems.push_back(model->playerCharacters.at(i)->getArmor()->getIndexInBag());
        if(model->playerCharacters.at(i)->getAccessory1() != nullptr)
            equippedItems.push_back(model->playerCharacters.at(i)->getAccessory1()->getIndexInBag());
        if(model->playerCharacters.at(i)->getAccessory2() != nullptr)
            equippedItems.push_back(model->playerCharacters.at(i)->getAccessory2()->getIndexInBag());
    }
}

void PauseMenuStateBag::moveMenuCursor(int x, int y)
{
    cursorPos -= y;

    if(cursorPos < 0)
        cursorPos = model->getEquipment()->size() + 3;
    if(cursorPos > (model->getEquipment()->size() + 3))
        cursorPos = 0;
}

PauseMenuDrawState *PauseMenuStateBag::enterMenu()
{
    if(cursorPos == 0)
    {
        if(model->getNumberOfPotions() > 0)
        {
            model->changePotionAmount(-1);
            for(int i = 0; i < model->playerCharacters.size(); i++)
            {
                if(!model->playerCharacters.at(i)->getIsActive())
                    continue;

                model->playerCharacters.at(i)->changeCurrentHealth(50);
            }
        }
    }
    if(cursorPos == 2)
    {
        if(model->getNumberOfEthers() > 0)
        {
            model->changeEtherAmount(-1);
            for(int i = 0; i < model->playerCharacters.size(); i++)
            {
                if(!model->playerCharacters.at(i)->getIsActive())
                    continue;

                model->playerCharacters.at(i)->changeCurrentMP(50);
            }
        }
    }
    return this;
}

PauseMenuDrawState *PauseMenuStateBag::closeMenu()
{
    return new PauseMenuStateMain(model);
}

void PauseMenuStateBag::drawPauseMenu(std::vector<DrawInformation> *items)
{
    //Bottom background for effects
    DrawInformation topTextBox(-700, -375, 1500, 140, "BattleMenuBG", false);
    items->push_back(topTextBox);

    DrawInformation info7(25, 25 + (cursorPos*25), 100, 100, "", false, ">", true, 24.f);
    items->push_back(info7);

    DrawInformation info(50, 25 + (-1 * 25), 200, 100, "", false, "Gold: " + std::to_string(model->getGold()), true, 24.f);
    items->push_back(info);
    DrawInformation info2(50, 25 + (0 * 25), 200, 100, "", false, "Potion x" + std::to_string(model->getNumberOfPotions()), true, 24.f);
    items->push_back(info2);
    DrawInformation info3(50, 25 + (1 * 25), 200, 100, "", false, "Remedy x" + std::to_string(model->getNumberOfRemedies()), true, 24.f);
    items->push_back(info3);
    DrawInformation info4(50, 25 + (2 * 25), 200, 100, "", false, "Potion x" + std::to_string(model->getNumberOfEthers()), true, 24.f);
    items->push_back(info4);
    DrawInformation info5(50, 25 + (3 * 25), 200, 100, "", false, "Remedy x" + std::to_string(model->getNumberOfJars()), true, 24.f);
    items->push_back(info5);

    int numberOfItems = 4;
    for(int i = 0; i < model->getEquipment()->size(); i++)
    {
        bool isEquiped = false;
        for(int j = 0; j < equippedItems.size(); j++)
        {
            if(equippedItems.at(j) == i)
                isEquiped = true;
        }

        if(isEquiped)
        {
            DrawInformation info2(50, 25 + (numberOfItems * 25), 200, 100, "", false, model->getEquipment()->at(i).getName() + "[E]", true, 24.f);
            items->push_back(info2);
        }
        else
        {
            DrawInformation info2(50, 25 + (numberOfItems * 25), 200, 100, "", false, model->getEquipment()->at(i).getName(), true, 24.f);
            items->push_back(info2);
        }
        numberOfItems++;
    }

    if(cursorPos == 0)
    {
        DrawInformation attackDesc(0, 730, 1500, 140, "",
                                false,
                                   "Heals for 50 HP. Press E to use."
                                   );
        items->push_back(attackDesc);
    }
    else if(cursorPos == 1)
    {
        DrawInformation attackDesc(0, 730, 1500, 140, "",
                                false,
                                   "Cures all status effects"
                                   );
        items->push_back(attackDesc);
    }
    else if(cursorPos == 2)
    {
        DrawInformation attackDesc(0, 730, 1500, 140, "",
                                false,
                                   "Heals for 50 MP. Press E to use"
                                   );
        items->push_back(attackDesc);
    }
    else if(cursorPos == 3)
    {
        DrawInformation attackDesc(0, 730, 1500, 140, "",
                                false,
                                   "Fills the party gauge"
                                   );
        items->push_back(attackDesc);
    }
    else
    {
        DrawInformation attackDesc(0, 730, 1500, 140, "",
                                false, model->getEquipment()->at(cursorPos-4).getDescription());
        items->push_back(attackDesc);
    }
}

bool PauseMenuStateBag::isMain()
{
    return false;
}

void PauseMenuStateBag::speicalMessage(std::string message)
{

}
