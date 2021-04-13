#include "attackmodel.h"

#include "../filemanagment/fileReader.h"

AttackModel::AttackModel(std::string info)
{
    std::vector<std::string> split = FileReader::splitString(info, ',');

    //name, castTime, mpcost, power, acc, desc, type, element, additonal, chance, multi
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
    if(additionalEffect == "WildMagic")
        return (500 + rand()%7000);

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
    if(additionalEffect == "WildMagic")
        return (-150 + rand()%300);

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
    if(additionalEffect == "WildMagic")
        return (rand()%10);

    if(element == 10)
    {
        //1-6
        return ((rand()%6) + 1);
    }

    return element;
}

std::string AttackModel::getAdditionalEffect()
{
    if(additionalEffect == "Cappuccino" || additionalEffect == "WildMagic")
    {
        return lastAddEffect;
    }

    return additionalEffect;
}

std::string AttackModel::getAdditionalEffectRoll()
{
    if(additionalEffect == "Cappuccino")
    {
        doACappuccino();

        return lastAddEffect;
    }
    if(additionalEffect == "WildMagic")
    {
        doAWildMagic();
        return lastAddEffect;
    }

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
    if(additionalEffect == "WildMagic")
        return (1 + rand()%2);

    return multitarget;
}

bool AttackModel::isUnlocked()
{
    return unlocked;
}

void AttackModel::unlock()
{
    unlocked = true;
}

void AttackModel::doACappuccino()
{
    int value = rand()%200;

    if(value < 20)
    {
        lastAddEffect = "AttackUp";
    }
    else if(value >= 20 && value < 40)
    {
        lastAddEffect = "DefenceUp";
    }
    else if(value >= 40 && value < 60)
    {
        lastAddEffect = "MagicUp";
    }
    else if(value >= 60 && value < 80)
    {
        lastAddEffect = "MagicDefenceUp";
    }
    else if(value >= 80 && value < 100)
    {
        lastAddEffect = "Haste";
    }
    else if(value >= 100 && value < 105)
    {
        lastAddEffect = "Slow";
    }
    else if(value >= 105 && value < 110)
    {
        lastAddEffect = "AttackDown";
    }
    else if(value >= 110 && value < 115)
    {
        lastAddEffect = "DefenceDown";
    }
    else if(value >= 115 && value < 120)
    {
        lastAddEffect = "MagicDown";
    }
    else if(value >= 120 && value < 125)
    {
        lastAddEffect = "MagicDefenceDown";
    }
    else if(value >= 125 && value < 130)
    {
        lastAddEffect = "Poison";
    }
    else if(value >= 130 && value < 135)
    {
        lastAddEffect = "Blind";
    }
    else if(value >= 135 && value < 140)
    {
        lastAddEffect = "Silence";
    }
    else if(value >= 140 && value < 145)
    {
        lastAddEffect = "Sleep";
    }
    else if(value >= 145 && value < 150)
    {
        lastAddEffect = "Stance";
    }
    else if(value >= 150 && value < 160)
    {
        lastAddEffect = "AttackUp";
    }
    else if(value >= 160 && value < 170)
    {
        lastAddEffect = "DefenceUp";
    }
    else if(value >= 170 && value < 180)
    {
        lastAddEffect = "MagicUp";
    }
    else if(value >= 180 && value < 190)
    {
        lastAddEffect = "MagicDefenceUp";
    }
    else if(value >= 190 && value < 200)
    {
        lastAddEffect = "Haste";
    }

}

void AttackModel::doAWildMagic()
{
    int value = rand()%200;

    if(value < 10)
    {
        lastAddEffect = "AttackUp";
    }
    else if(value < 20)
    {
        lastAddEffect = "DefenceUp";
    }
    else if(value < 30)
    {
        lastAddEffect = "MagicUp";
    }
    else if(value < 40)
    {
        lastAddEffect = "MagicDefenceUp";
    }
   else if(value < 50)
    {
        lastAddEffect = "Haste";
    }
    else if(value < 60)
    {
        lastAddEffect = "Slow";
    }
    else if(value < 70)
    {
        lastAddEffect = "AttackDown";
    }
    else if(value < 80)
    {
        lastAddEffect = "DefenceDown";
    }
    else if(value < 90)
    {
        lastAddEffect = "MagicDown";
    }
    else if(value < 100)
    {
        lastAddEffect = "MagicDefenceDown";
    }
    else if(value < 110)
    {
        lastAddEffect = "Poison";
    }
    else if(value < 120)
    {
        lastAddEffect = "Blind";
    }
    else if(value < 130)
    {
        lastAddEffect = "Silence";
    }
    else if(value < 140)
    {
        lastAddEffect = "Sleep";
    }

    lastAddEffect = "None";
}
