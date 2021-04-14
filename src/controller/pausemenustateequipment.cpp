#include "pausemenustateequipment.h"

#include <QDebug>

#include "../model/modelabstract.h"
#include "../display/drawinformation.h"
#include "pausemenustatemain.h"

PauseMenuStateEquipment::PauseMenuStateEquipment(ModelAbstract *model)
    : PauseMenuDrawState(model)
{
    numberOfCharatersInput = 0;
    for(int i = 0; i < model->playerCharacters.size(); i++)
    {
        if(!model->playerCharacters.at(i)->getIsActive())
            continue;

        numberOfCharatersInput++;
        characters[model->playerCharacters.at(i)->getEquipmentID()] = model->playerCharacters.at(i);
    }
}

void PauseMenuStateEquipment::moveMenuCursor(int x, int y)
{
    if(listIsOpen)
    {
        equipmentPos -= y;

        if(equipmentPos > (focusNumberOfItems-1))
            equipmentPos = 0;
        if(equipmentPos < 0)
            equipmentPos = (focusNumberOfItems-1);
        return;
    }

    currentPosY -= y;

    if(numberOfCharatersInput > 1)
    {
        currentPosX += x;

        if(currentPosX > 1)
            currentPosX = 0;
        if(currentPosX < 0)
            currentPosX = 1;

        if(numberOfCharatersInput < 3)
        {
            if(currentPosY < 0)
                currentPosY = 3;
            if(currentPosY > 3)
                currentPosY = 0;
        }
    }

    if(numberOfCharatersInput > 2 && numberOfCharatersInput < 4)
    {
        if(currentPosX > 0)
        {
            if(currentPosY < 0)
                currentPosY = 3;
            if(currentPosY > 3)
                currentPosY = 0;
        }
        else
        {
            if(currentPosY < 0)
                currentPosY = 7;
            if(currentPosY > 7)
                currentPosY = 0;
        }
    }

    if(numberOfCharatersInput > 3)
    {
        if(currentPosY < 0)
            currentPosY = 7;
        if(currentPosY > 7)
            currentPosY = 0;
    }

}

PauseMenuDrawState *PauseMenuStateEquipment::enterMenu()
{
    if(listIsOpen)
    {
        //Equip the equipment
        if(focusType == "Weapon")
        {
            characters[focusPartyMemberLimit]->setWeapon(&model->getEquipment()->at(indexesOfFocusType.at(equipmentPos)));
            listIsOpen = false;
        }
        else if(focusType == "Armor")
        {
            characters[focusPartyMemberLimit]->setArmor(&model->getEquipment()->at(indexesOfFocusType.at(equipmentPos)));
            listIsOpen = false;
        }
        else if(focusType == "Accessory")
        {
            if(selectedAccessory1)
                characters[focusPartyMemberLimit]->setAccessory1(&model->getEquipment()->at(indexesOfFocusType.at(equipmentPos)));
            else
                characters[focusPartyMemberLimit]->setAccessory2(&model->getEquipment()->at(indexesOfFocusType.at(equipmentPos)));
            listIsOpen = false;
        }
        return this;
    }

    if(currentPosY == 0 || currentPosY == 4)
        focusType = "Weapon";
    if(currentPosY == 1 || currentPosY == 5)
        focusType = "Armor";
    if(currentPosY == 2 || currentPosY == 3 || currentPosY == 6 || currentPosY == 7)
    {
        focusType = "Accessory";
        selectedAccessory1 = (currentPosY == 2 || currentPosY == 6);
    }

    if(currentPosX == 0 && currentPosY < 4)
        focusPartyMemberLimit = 0; //Bullent
    if(currentPosX == 1 && currentPosY < 4)
        focusPartyMemberLimit = 1; //Chad
    if(currentPosX == 0 && currentPosY > 3)
        focusPartyMemberLimit = 2; //Allura
    if(currentPosX == 1 && currentPosY > 3)
        focusPartyMemberLimit = 3; //Duke

    focusNumberOfItems = 0;
    indexesOfFocusType.clear();
    for(int i = 0; i < model->getEquipment()->size(); i++)
    {
        if(model->getEquipment()->at(i).getType() == focusType)
        {
            bool itsOkay = false;
            if((focusPartyMemberLimit == 0) &&
                    (model->getEquipment()->at(i).getPartyMemberLimit()==0
                     || model->getEquipment()->at(i).getPartyMemberLimit()==1
                     || model->getEquipment()->at(i).getPartyMemberLimit()==5
                     ))
                itsOkay = true;
            if((focusPartyMemberLimit == 1) &&
                    (model->getEquipment()->at(i).getPartyMemberLimit()==0
                     || model->getEquipment()->at(i).getPartyMemberLimit()==2
                     || model->getEquipment()->at(i).getPartyMemberLimit()==6
                     ))
                itsOkay = true;
            if((focusPartyMemberLimit == 2) &&
                    (model->getEquipment()->at(i).getPartyMemberLimit()==0
                     || model->getEquipment()->at(i).getPartyMemberLimit()==3
                     || model->getEquipment()->at(i).getPartyMemberLimit()==6
                     ))
                itsOkay = true;
            if((focusPartyMemberLimit == 3) &&
                    (model->getEquipment()->at(i).getPartyMemberLimit()==0
                     || model->getEquipment()->at(i).getPartyMemberLimit()==4
                     || model->getEquipment()->at(i).getPartyMemberLimit()==5
                     ))
                itsOkay = true;

            //If its already equipped by someone. its not okay
            for(int j = 0; j < numberOfCharatersInput; j++)
            {
                if(focusType == "Weapon")
                {
                    if(characters[j]->getWeapon() != nullptr)
                    {
                        if(characters[j]->getWeapon()->getIndexInBag() == i)
                        {
                            itsOkay = false;
                        }
                    }
                }
                else if(focusType == "Armor")
                {
                    if(characters[j]->getArmor() != nullptr)
                    {
                        if(characters[j]->getArmor()->getIndexInBag() == i)
                        {
                            itsOkay = false;
                        }
                    }
                }
                else if(focusType == "Accessory")
                {
                    if(characters[j]->getAccessory1() != nullptr)
                    {
                        if(characters[j]->getAccessory1()->getIndexInBag() == i)
                        {
                            itsOkay = false;
                        }
                    }

                    if(characters[j]->getAccessory2() != nullptr)
                    {
                        if(characters[j]->getAccessory2()->getIndexInBag() == i)
                        {
                            itsOkay = false;
                        }
                    }
                }
            }

            if(itsOkay)
            {
                indexesOfFocusType.push_back(i);
                focusNumberOfItems++;
            }
        }
    }

    if(indexesOfFocusType.size() <= 0)
        return this;

    equipmentPos = 0;
    listIsOpen = true;

    return this;
}

PauseMenuDrawState *PauseMenuStateEquipment::closeMenu()
{
    if(listIsOpen)
    {
        equipmentPos = 0;
        listIsOpen = false;
        return this;
    }

    return new PauseMenuStateMain(model);
}

void PauseMenuStateEquipment::drawPauseMenu(std::vector<DrawInformation> *items)
{


    if(listIsOpen)
    {
        //Bottom background for effects
        DrawInformation topTextBox(-700, -375, 1500, 140, "BattleMenuBG", false);
        items->push_back(topTextBox);

        drawEquipmentList(items);

        DrawInformation attackDesc(0, 730, 1500, 140, "",
                                false, model->getEquipment()->at(indexesOfFocusType.at(equipmentPos)).getDescription());
        items->push_back(attackDesc);

        return;
    }

    //Images
    for(int i = 0; i < numberOfCharatersInput; i++)
    {
        DrawInformation port(-700 + ((i%2)*700), (300 - ((i/2)*400)), 200, 200, characters[i]->getMenuSpriteKey(), false);
        items->push_back(port);

        DrawInformation weaponIcon(-700 + ((i%2)*700) +225, (300 - ((i/2)*400)) + 50, 50, 50, "WeaponIcon", false);
        items->push_back(weaponIcon);
        DrawInformation armorIcon(-700 + ((i%2)*700) +225, (300 - ((i/2)*400)) - 0, 50, 50, "ArmorIcon", false);
        items->push_back(armorIcon);
        DrawInformation access1Icon(-700 + ((i%2)*700) +225, (300 - ((i/2)*400)) - 50, 50, 50, "AccessoryIcon", false);
        items->push_back(access1Icon);
        DrawInformation access2Icon(-700 + ((i%2)*700) +225, (300 - ((i/2)*400)) - 100, 50, 50, "AccessoryIcon", false);
        items->push_back(access2Icon);
    }


    //Text
    for(int i = 0; i < numberOfCharatersInput; i++)
    {
        DrawInformation info2(275 + ((i%2) * 700), 25 + ((i/2) * 400), 200, 100, "", false, characters[i]->getName(), true);
        items->push_back(info2);

        //Display the equiped equipment
        if(characters[i]->getWeapon() == nullptr)
        {
            DrawInformation info2(275 + ((i%2) * 700) + 75, 25 + ((i/2) * 400) + 70 + 12, 200, 100, "", false, "-", true, 24.f);
            items->push_back(info2);
        }
        else
        {
            DrawInformation info2(275 + ((i%2) * 700) + 75, 25 + ((i/2) * 400) + 70 + 12, 200, 100, "", false, characters[i]->getWeapon()->getName(), true, 24.f);
            items->push_back(info2);
        }
        if(characters[i]->getArmor() == nullptr)
        {
            DrawInformation info2(275 + ((i%2) * 700) + 75, 25 + ((i/2) * 400) + 70 + 50 + 12, 200, 100, "", false, "-", true, 24.f);
            items->push_back(info2);
        }
        else
        {
            DrawInformation info2(275 + ((i%2) * 700) + 75, 25 + ((i/2) * 400) + 70 + 50 + 12, 200, 100, "", false, characters[i]->getArmor()->getName(), true, 24.f);
            items->push_back(info2);
        }
        if(characters[i]->getAccessory1() == nullptr)
        {
            DrawInformation info2(275 + ((i%2) * 700) + 75, 25 + ((i/2) * 400) + 70 + 100 + 12, 200, 100, "", false, "-", true, 24.f);
            items->push_back(info2);
        }
        else
        {
            DrawInformation info2(275 + ((i%2) * 700) + 75, 25 + ((i/2) * 400) + 70 + 100 + 12, 200, 100, "", false, characters[i]->getAccessory1()->getName(), true, 24.f);
            items->push_back(info2);
        }
        if(characters[i]->getAccessory2() == nullptr)
        {
            DrawInformation info2(275 + ((i%2) * 700) + 75, 25 + ((i/2) * 400) + 70 + 150 + 12, 200, 100, "", false, "-", true, 24.f);
            items->push_back(info2);
        }
        else
        {
            DrawInformation info2(275 + ((i%2) * 700) + 75, 25 + ((i/2) * 400) + 70 + 150 + 12, 200, 100, "", false, characters[i]->getAccessory2()->getName(), true, 24.f);
            items->push_back(info2);
        }
    }

    DrawInformation info7(240 + ((currentPosX) * 700), 95 + (currentPosY*50) + ((currentPosY/4) * 200) + 12, 100, 100, "", false, ">", true, 24.f);
    items->push_back(info7);
}

bool PauseMenuStateEquipment::isMain()
{
    return false;
}

void PauseMenuStateEquipment::speicalMessage(std::string message)
{
    if(!listIsOpen)
    {
        if(message == "RemoveEquipment")
        {
            std::string removefocusType;
            bool removeSelectedAccessory1;
            int removePartyIndex;

            if(currentPosY == 0 || currentPosY == 4)
                removefocusType = "Weapon";
            if(currentPosY == 1 || currentPosY == 5)
                removefocusType = "Armor";
            if(currentPosY == 2 || currentPosY == 3 || currentPosY == 6 || currentPosY == 7)
            {
                removefocusType = "Accessory";
                removeSelectedAccessory1 = (currentPosY == 2 || currentPosY == 6);
            }

            if(currentPosX == 0 && currentPosY < 4)
                removePartyIndex = 0; //Bullent
            if(currentPosX == 1 && currentPosY < 4)
                removePartyIndex = 1; //Chad
            if(currentPosX == 0 && currentPosY > 3)
                removePartyIndex = 2; //Allura
            if(currentPosX == 1 && currentPosY > 3)
                removePartyIndex = 3; //Duke

            if(removefocusType == "Weapon")
            {
                characters[removePartyIndex]->setWeapon(nullptr);
                listIsOpen = false;
            }
            else if(removefocusType == "Armor")
            {
                characters[removePartyIndex]->setArmor(nullptr);
                listIsOpen = false;
            }
            else if(removefocusType == "Accessory")
            {
                if(removeSelectedAccessory1)
                    characters[removePartyIndex]->setAccessory1(nullptr);
                else
                    characters[removePartyIndex]->setAccessory2(nullptr);
                listIsOpen = false;
            }
        }
    }
}

void PauseMenuStateEquipment::drawEquipmentList(std::vector<DrawInformation> *items)
{
    DrawInformation info7(25, 25 + (equipmentPos*25), 100, 100, "", false, ">", true, 24.f);
    items->push_back(info7);

    int numberOfItems = 0;
    //for(int i = 0; i < model->getEquipment()->size(); i++)
    for(int i = 0; i < indexesOfFocusType.size(); i++)
    {
        //if(model->getEquipment()->at(i).getType() == focusType)
        {
            DrawInformation info2(50, 25 + (numberOfItems * 25), 200, 100, "", false, model->getEquipment()->at(indexesOfFocusType.at(i)).getName(), true, 24.f);
            items->push_back(info2);
            numberOfItems++;
        }
    }
}
