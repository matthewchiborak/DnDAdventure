#include "modelabstract.h"

#include "../filemanagment/fileReader.h"

#include "../model/monstermanualentry.h"

#include <vector>

ModelAbstract::ModelAbstract()
{
    addEquipment("Weapon,1,Test_Weapon1,Bullent_Only,9,1000");
    addEquipment("Weapon,2,TestWeapon2,Chad_Only,AttackUp,50");
    addEquipment("Weapon,3,TestWeapon3,Allura_Only,AttackUp,50");
    addEquipment("Weapon,4,TestWeapon4,Duke_Only,AttackUp,50");

    addEquipment("Armor,5,No_Fire,Light,1,100");
    addEquipment("Armor,5,Testarm2,Light,AttackUp,50");
    addEquipment("Armor,6,TestWArm3,Heavy,AttackUp,50");
    addEquipment("Armor,6,TestArm4,Heavy,AttackUp,50");

    addEquipment("Accessory,0,No_Poison,Test Description 7,Poison,100");
    addEquipment("Accessory,0,Water_Resist,Test Description 8,-4,100");
    addEquipment("Accessory,0,TestAccessory3,Test_Description 9,AttackUp,50");
}

ModelAbstract::~ModelAbstract()
{
    for(int i = 0; i < playerCharacters.size(); i++)
    {
        delete playerCharacters.at(i);
    }
}

void ModelAbstract::addPlayerCharacter(PlayerCharacterStats *character)
{
    playerCharacters.push_back(character);
}


void ModelAbstract::drawBoardModel(std::vector<DrawInformation> * items, float *xOffset, float *yOffset)
{

}
void ModelAbstract::loadBoardModel(std::string loadInfo)
{

}

std::string ModelAbstract::handleBoardCollisionTriggers()
{
    return "None";
}

void ModelAbstract::movePlayer(int x, int y, float t)
{

}

void ModelAbstract::drawPauseMenu(std::vector<DrawInformation> *items)
{

}

void ModelAbstract::moveMenuCursor(int x, int y, std::string key)
{

}

void ModelAbstract::enterMenu(std::string key)
{

}

void ModelAbstract::closeMenu(std::string key)
{

}

bool ModelAbstract::tryToStartABattle()
{
    return false;
}

void ModelAbstract::drawBattleModel(std::vector<DrawInformation> *items)
{

}

void ModelAbstract::passTime(float value)
{

}

bool ModelAbstract::isBattleDone()
{
    return true;
}

bool ModelAbstract::isGameOver()
{
    return false;
}

void ModelAbstract::qrPressed(bool wasQ)
{

}

void ModelAbstract::specialMessage(std::string message, std::string key)
{

}

void ModelAbstract::addEquipment(std::string info)
{
    EquipmentModel temp(info, equipment.size());
    equipment.push_back(temp);
}

std::vector<EquipmentModel> *ModelAbstract::getEquipment()
{
    return &equipment;
}

bool ModelAbstract::getPauseIsDone()
{
    return pauseIsDone;
}

void ModelAbstract::setPauseIsDone(bool value)
{
    pauseIsDone = value;
}

int ModelAbstract::getNumberOfPotions()
{
    return numberOfPotions;
}

void ModelAbstract::setNumberOfPotions(int value)
{
    numberOfPotions = value;
}

void ModelAbstract::changePotionAmount(int amount)
{
    numberOfPotions += amount;

    if(numberOfPotions < 0)
        numberOfPotions = 0;
}

int ModelAbstract::getNumberOfRemedies()
{
    return numberOfRemedies;
}

void ModelAbstract::setNumberOfRemedies(int value)
{
    numberOfRemedies = value;
}

void ModelAbstract::changeRemedyAmount(int amount)
{
    numberOfRemedies += amount;

    if(numberOfRemedies < 0)
        numberOfRemedies = 0;
}

int ModelAbstract::getGold()
{
    return gold;
}

void ModelAbstract::changeGold(int amount)
{
    gold += amount;

    if(gold < 0)
        gold = 0;
}

void ModelAbstract::setGold(int value)
{
    gold = value;
}

int ModelAbstract::getNumberOfEthers()
{
    return numberOfEthers;
}

int ModelAbstract::getNumberOfJars()
{
    return numberOfPickleJars;
}

void ModelAbstract::setNumberOfEthers(int value)
{
    numberOfEthers = value;
}

void ModelAbstract::setNumberofJars(int value)
{
    numberOfPickleJars = value;
}

void ModelAbstract::changeEtherAmount(int amount)
{
    numberOfEthers += amount;

    if(numberOfEthers < 0)
        numberOfEthers = 0;
}

void ModelAbstract::changeJarAmount(int amount)
{
    numberOfPickleJars += amount;

    if(numberOfPickleJars < 0)
        numberOfPickleJars = 0;
}

void ModelAbstract::loadMonsterManual(std::string filepath)
{
    FileReader fr(filepath);

    while(fr.hasNext())
    {
        std::vector<std::string> spt = fr.splitString(fr.next(), ',');
        MonsterManualEntry en(spt.at(0), spt.at(1));
        monsterManual.push_back(en);
    }
}

std::vector<MonsterManualEntry> *ModelAbstract::getMonsterManual()
{
    return &monsterManual;
}



