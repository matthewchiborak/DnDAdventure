#include "shopmodel.h"

#include  "../filemanagment/fileReader.h"

#include "../display/drawinformation.h"
#include "equipmentmodel.h"

#include <QDebug>

ShopModel::ShopModel()
{

}

void ShopModel::load(std::string info, int *gold, int *numberOfPotions, int *numberOfRemedies, int *numberOfEthers, int *numberOfPickleJars, std::vector<EquipmentModel *> *equipment)
{
    clear();

    this->gold = gold;
    this->numberOfPotions = numberOfPotions;
    this->numberOfRemedies = numberOfRemedies;
    this->numberOfEthers = numberOfEthers;
    this->numberOfPickleJars = numberOfPickleJars;
    this->equipment = equipment;

    std::vector<std::string> cutMessage = FileReader::splitString(info, '@');

    if(cutMessage.at(0) != "Shop")
        return;

    //Prices, names, invenotry

    //potion$25@ether$25@remedy$25@jar
    for(int i = 1; i < cutMessage.size(); i++)
    {
        numberofItems++;
        std::vector<std::string> cutMessage2 = FileReader::splitString(cutMessage.at(i), '$');

        if(cutMessage2.at(0) == "equipment")
        {
            names.push_back(FileReader::replaceCharacter(cutMessage2.at(3), '_', ' '));
            prices.push_back(std::stoi(cutMessage2.at(7)));
            desc.push_back(FileReader::replaceCharacter(cutMessage2.at(4), '_', ' '));

            std::string buildString = cutMessage2.at(1);
            for(int j = 2; j < cutMessage2.size(); j++)
                buildString = buildString + "," + cutMessage2.at(j);
            inventory.push_back(buildString);
        }
        else if(cutMessage2.at(0) == "potion")
        {
            names.push_back("Potion");
            desc.push_back("Heals for 50 HP");
            prices.push_back(std::stoi(cutMessage2.at(1)));
            inventory.push_back(cutMessage2.at(0));
        }
        else if(cutMessage2.at(0) == "remedy")
        {
            names.push_back("Remedy");
            desc.push_back("Cures all status effects");
            prices.push_back(std::stoi(cutMessage2.at(1)));
            inventory.push_back(cutMessage2.at(0));
        }
        else if(cutMessage2.at(0) == "ether")
        {
            names.push_back("Ether");
            desc.push_back("Heals for 50 MP");
            prices.push_back(std::stoi(cutMessage2.at(1)));
            inventory.push_back(cutMessage2.at(0));
        }
        else if(cutMessage2.at(0) == "jar")
        {
            names.push_back("Pickle Jar");
            desc.push_back("Fills the party gauge");
            prices.push_back(std::stoi(cutMessage2.at(1)));
            inventory.push_back(cutMessage2.at(0));
        }
    }



}

void ShopModel::confirm()
{
    if(inventory.at(cursorPos) == "potion")
    {
        if((*gold) >= prices.at(cursorPos))
        {
            (*numberOfPotions) = (*numberOfPotions) + 1;
            (*gold) = (*gold) - prices.at(cursorPos);
        }
    }
    else if(inventory.at(cursorPos) == "remedy")
    {
        if((*gold) >= prices.at(cursorPos))
        {
            (*numberOfRemedies) = (*numberOfRemedies) + 1;
            (*gold) = (*gold) - prices.at(cursorPos);
        }
    }
    else if(inventory.at(cursorPos) == "ether")
    {
        if((*gold) >= prices.at(cursorPos))
        {
            (*numberOfEthers) = (*numberOfEthers) + 1;
            (*gold) = (*gold) - prices.at(cursorPos);
        }
    }
    else if(inventory.at(cursorPos) == "jar")
    {
        if((*gold) >= prices.at(cursorPos))
        {
            (*numberOfPickleJars) = (*numberOfPickleJars) + 1;
            (*gold) = (*gold) - prices.at(cursorPos);
        }
    }
    else
    {
        if((*gold) >= prices.at(cursorPos))
        {
            equipment->push_back(new EquipmentModel(inventory.at(cursorPos), equipment->size()));
            (*gold) = (*gold) - prices.at(cursorPos);
        }
    }
}

void ShopModel::moveMenuCursor(int x, int y)
{
    cursorPos -= y;

    if(cursorPos < 0)
        cursorPos = (numberofItems-1);
    if(cursorPos >= numberofItems)
        cursorPos = 0;
}

void ShopModel::draw(std::vector<DrawInformation> *items)
{
    DrawInformation infoBG(-800, -400, 1700, 900, "PauseMenuBG", false);
    items->push_back(infoBG);

    DrawInformation topTextBox(-700, -375, 1500, 140, "BattleMenuBG", false);
    items->push_back(topTextBox);

    DrawInformation info7(25, 25 + (cursorPos*25), 100, 100, "", false, ">", true, 24.f);
    items->push_back(info7);

    DrawInformation info(50, 25 + (-1 * 25), 400, 100, "", false, "Gold: " + std::to_string((*gold)), true, 24.f);
    items->push_back(info);

    for(int i = 0; i < names.size(); i++)
    {
        DrawInformation info2(50, 25 + (i * 25), 400, 100, "", false, names.at(i) + ": " + std::to_string(prices.at(i)) + "G", true, 24.f);
        items->push_back(info2);
    }

    DrawInformation attackDesc(0, 730, 1500, 140, "",
                            false, desc.at(cursorPos));
    items->push_back(attackDesc);
}

void ShopModel::clear()
{
    cursorPos = 0;
    numberofItems = 0;

    prices.clear();
    names.clear();
    desc.clear();
    inventory.clear();
}
