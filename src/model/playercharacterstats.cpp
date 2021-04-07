#include "playercharacterstats.h"

#include "../filemanagment/fileReader.h"

#include <string>
#include <vector>
#include <math.h>

PlayerCharacterStats::PlayerCharacterStats(std::string filepath)
{
    FileReader fr(filepath);

    while(fr.hasNext())
    {
        std::vector<std::string> splits = fr.splitString(fr.next(), ',');

        if(splits.at(0) == "BaseHP")
        {
            baseHealth = std::stoi(splits.at(1));
        }
        if(splits.at(0) == "BaseMP")
        {
            baseMP = std::stoi(splits.at(1));
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
        if(splits.at(0) == "MenuSprite")
            menuSpriteKey = splits.at(1);
        if(splits.at(0) == "IVHP")
            IVHP = std::stoi(splits.at(1));
        if(splits.at(0) == "IVAtt")
            IVAtt = std::stoi(splits.at(1));
        if(splits.at(0) == "IVDef")
            IVDef = std::stoi(splits.at(1));
        if(splits.at(0) == "IVMAtt")
            IVMAtt = std::stoi(splits.at(1));
        if(splits.at(0) == "IVMDef")
            IVMDef = std::stoi(splits.at(1));
        if(splits.at(0) == "IVSpeed")
            IVSpeed = std::stoi(splits.at(1));
        if(splits.at(0) == "IVMP")
            IVMP = std::stoi(splits.at(1));

    }

    isActive = true;
    level = 1;
    xp = 0;

    currentHealth = getMaxHealth();
    currentMP = getMaxMP();
}

int PlayerCharacterStats::getCurrentHealth()
{
    return currentHealth;
}

int PlayerCharacterStats::getMaxHealth()
{
    //NEED to caled this based on base and level
    //HP = floor(0.01 x (2 x Base + IV + floor(0.25 x EV)) x Level) + Level + 10
    return floor(0.01f * (2.f * baseHealth + IVHP + floor(0.25f * 0)) * (level + 15)) + level + 35;
    //return floor(0.01f * (2 * baseHealth + 0 + floor(0.25 * 0)) * level) + level + 10;
}

int PlayerCharacterStats::getAttack()
{
    //floor(0.01 x (2 x Base + IV + floor(0.25 x EV)) x Level) + 5) * nature (10 percent up or down)
    return floor(0.01f * (2.f * attack + IVAtt + floor(0.25f * 0)) * (level + 15)) + 5;
}

int PlayerCharacterStats::getDefence()
{
    return floor(0.01f * (2.f * defence + IVDef + floor(0.25f * 0)) * (level + 15)) + 5;
}

int PlayerCharacterStats::getMagicAttack()
{
    return floor(0.01f * (2.f * magicAttack + IVMAtt + floor(0.25f * 0)) * (level + 15)) + 5;
}

int PlayerCharacterStats::getMagicDefence()
{
    return floor(0.01f * (2.f * magicDefence + IVMDef + floor(0.25f * 0)) * (level + 15)) + 5;
}

int PlayerCharacterStats::getSpeed()
{
    return floor(0.01f * (2.f * speed + IVSpeed + floor(0.25f * 0)) * (level + 15)) + 5;
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

int PlayerCharacterStats::getCurrentMP()
{
    return currentMP;
}

int PlayerCharacterStats::getMaxMP()
{
    if(baseMP == 0)
        return 0;

    return floor(0.01f * (2.f * baseMP + IVMP + floor(0.25f * 0)) * (level + 15)) + 5;
}

std::string PlayerCharacterStats::getName()
{
    return name;
}

std::string PlayerCharacterStats::getSpriteKey()
{
    return spriteKey;
}

std::string PlayerCharacterStats::getMenuSpriteKey()
{
    return menuSpriteKey;
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
