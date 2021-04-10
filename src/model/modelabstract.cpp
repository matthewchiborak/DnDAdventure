#include "modelabstract.h"

ModelAbstract::ModelAbstract()
{
    addEquipment("Weapon,1,Test_Weapon1,Bullent_Only,9,1000");
    addEquipment("Weapon,2,TestWeapon2,Chad_Only,AttackUp,50");
    addEquipment("Weapon,3,TestWeapon3,Allura_Only,AttackUp,50");
    addEquipment("Weapon,4,TestWeapon4,Duke_Only,AttackUp,50");

    addEquipment("Armor,5,Test_Armor1NoFire,Light,1,100");
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

