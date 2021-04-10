#include "equipmentmodel.h"

#include "../filemanagment/fileReader.h"

EquipmentModel::EquipmentModel(std::string creationInfo, int index)
{
    std::vector<std::string> vec = FileReader::splitString(creationInfo, ',');

    type = vec.at(0);
    partyMemberLimit = std::stoi(vec.at(1));
    name = FileReader::replaceCharacter(vec.at(2), '_', ' ');
    desc = FileReader::replaceCharacter(vec.at(3), '_', ' ');
    effect = vec.at(4);
    mulitplier = std::stoi(vec.at(5));
    indexInBag = index;
}

std::string EquipmentModel::getName()
{
    return name;
}

std::string EquipmentModel::getType()
{
    return type;
}

int EquipmentModel::getPartyMemberLimit()
{
    return partyMemberLimit;
}

std::string EquipmentModel::getEffect()
{
    return effect;
}

float EquipmentModel::getMultiplier()
{
    return mulitplier;
}

std::string EquipmentModel::getDescription()
{
    return desc;
}

int EquipmentModel::getIndexInBag()
{
    return indexInBag;
}
