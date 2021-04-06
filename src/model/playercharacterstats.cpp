#include "playercharacterstats.h"

#include "../filemanagment/fileReader.h"

#include <string>
#include <vector>

PlayerCharacterStats::PlayerCharacterStats(std::string filepath)
{
    FileReader fr(filepath);

    while(fr.hasNext())
    {
        std::vector<std::string> splits = fr.splitString(fr.next(), ',');

        if(splits.at(0) == "BaseHP")
        {
            maxHealth = std::stoi(splits.at(1));
            currentHealth = maxHealth;
        }
        if(splits.at(0) == "Name")
            name = splits.at(1);
        if(splits.at(0) == "BaseAtt")
            attack = std::stoi(splits.at(1));
        if(splits.at(0) == "BaseDef")
            defence = std::stoi(splits.at(1));
        if(splits.at(0) == "BaseMAtt")
            magicAttack = std::stoi(splits.at(1));
        if(splits.at(0) == "BaseMDef")
            magicDefence = std::stoi(splits.at(1));
        if(splits.at(0) == "BaseSpeed")
            speed = std::stoi(splits.at(1));
        if(splits.at(0) == "Sprite")
            spriteKey = splits.at(1);
    }

    isActive = true;
}

int PlayerCharacterStats::getCurrentHealth()
{
    return currentHealth;
}

int PlayerCharacterStats::getMaxHealth()
{
    //NEED to caled this based on base and level
    return -1;
}

int PlayerCharacterStats::getAttack()
{
    return -1;
}

int PlayerCharacterStats::getDefence()
{
    return -1;
}

int PlayerCharacterStats::getMagicAttack()
{
    return -1;
}

int PlayerCharacterStats::getMagicDefence()
{
    return -1;
}

int PlayerCharacterStats::getSpeed()
{
    return -1;
}

int PlayerCharacterStats::getLevel()
{
    return level;
}

int PlayerCharacterStats::getXP()
{
    return xp;
}

bool PlayerCharacterStats::getIsActive()
{
    return isActive;
}

std::string PlayerCharacterStats::getName()
{
    return name;
}

std::string PlayerCharacterStats::getSpriteKey()
{
    return spriteKey;
}

void PlayerCharacterStats::setLevel(int lvl)
{
    this->level = lvl;
}

void PlayerCharacterStats::setXP(int xp)
{
    this->xp = xp;
}

void PlayerCharacterStats::changeXP(int amount)
{
    this->xp += amount;
}

void PlayerCharacterStats::setCurrentHealth(int hp)
{
    this->currentHealth = hp;
}

void PlayerCharacterStats::changeCurrentHealth(int amount)
{
    this->currentHealth += amount;
}

void PlayerCharacterStats::setIsActive(bool value)
{
    this->isActive = value;
}
