#include "attackmodel.h"

#include "../filemanagment/fileReader.h"

AttackModel::AttackModel(std::string info)
{
    std::vector<std::string> split = FileReader::splitString(info, ',');

    name = split.at(1);
    castTime = std::stoi(split.at(2));
    mpcost = std::stoi(split.at(3));
    power = std::stoi(split.at(4));
    accuracy = std::stoi(split.at(5));
    description = split.at(6);
    attackType = std::stoi(split.at(7));
    element = std::stoi(split.at(8));

    if(split.size() > 9)
        additionalEffect = split.at(9);
    else
        additionalEffect = "None";
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

int AttackModel::getAccuracy()
{
    return accuracy;
}
