#include "attackmodel.h"

#include "../filemanagment/fileReader.h"

AttackModel::AttackModel(std::string info)
{
    std::vector<std::string> split = FileReader::splitString(info, ',');

    name = FileReader::replaceCharacter(split.at(1), '_', ' ');
    castTime = std::stoi(split.at(2));
    mpcost = std::stoi(split.at(3));
    power = std::stoi(split.at(4));
    accuracy = std::stoi(split.at(5));
    description = FileReader::replaceCharacter(split.at(6), '_', ' ');
    attackType = std::stoi(split.at(7));
    element = std::stoi(split.at(8));

    if(split.size() > 9)
        additionalEffect = split.at(9);
    else
        additionalEffect = "None";

    if(split.size() > 10)
        chanceOfAdditionalEffect = std::stoi(split.at(10));
    else
        chanceOfAdditionalEffect = 100;

    if(split.size() > 11)
        multitarget = std::stoi(split.at(11));
    else
        multitarget = 0;


}

std::string AttackModel::getName()
{
    return name;
}

int AttackModel::getCastTime()
{
    return castTime;
}

int AttackModel::getMpcost()
{
    return mpcost;
}

std::string AttackModel::getMPCostString()
{
    if(mpcost <= 0)
        return "";

    return "  MP: " + std::to_string(mpcost);
}

int AttackModel::getPower()
{
    return power;
}

std::string AttackModel::getDescription()
{
    return description;
}

int AttackModel::getAttackType()
{
    return attackType;
}

int AttackModel::getElement()
{
    return element;
}

std::string AttackModel::getAdditionalEffect()
{
    return additionalEffect;
}

std::string AttackModel::getAdditionalEffectRoll()
{
    //if chance is less than 100 do a roll for it
    if(chanceOfAdditionalEffect >= 100)
        return additionalEffect;

    if(rand()%100 > chanceOfAdditionalEffect)
    {
        return "None";
    }

    return additionalEffect;
}

int AttackModel::getAccuracy()
{
    return accuracy;
}

int AttackModel::getMultitarget()
{
    return multitarget;
}
