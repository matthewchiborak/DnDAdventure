#include "attackmodel.h"

#include "../filemanagment/fileReader.h"

AttackModel::AttackModel(std::string info)
{
    std::vector<std::string> split = FileReader::splitString(info, ',');

    name = split.at(1);
    castTime = std::stoi(split.at(2));
    mpcost = std::stoi(split.at(3));
    power = std::stoi(split.at(4));
    description = split.at(5);
    attackType = std::stoi(split.at(6));
    element = std::stoi(split.at(7));
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
