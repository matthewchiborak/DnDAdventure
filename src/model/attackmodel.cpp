#include "attackmodel.h"

#include "../filemanagment/fileReader.h"

AttackModel::AttackModel(std::string info)
{
    std::vector<std::string> split = FileReader::splitString(info, ',');

    name = split.at(1);
    castTime = std::stoi(split.at(2));
    mpcost = std::stoi(split.at(3));
    damage = std::stoi(split.at(4));
    description = split.at(5);
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

int AttackModel::getDamage()
{
    return damage;
}

std::string AttackModel::getDescription()
{
    return description;
}
