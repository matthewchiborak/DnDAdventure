#include "playercharacterstats.h"

#include "../filemanagment/fileReader.h"
#include "attackmodel.h"

#include <string>
#include <vector>
#include <QDebug>
#include <math.h>
#include <cmath>


PlayerCharacterStats::PlayerCharacterStats(std::string filepath)
{
    FileReader fr(filepath);

    while(fr.hasNext())
    {
        std::string nextLine = fr.next();
        std::vector<std::string> splits = fr.splitString(nextLine, ',');

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
        if(splits.at(0) == "EquipmentId")
            equipmentID = std::stoi(splits.at(1));
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
        if(splits.at(0) == "TimeLineSprite")
            timelineSpriteKey = splits.at(1);
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
        if(splits.at(0) == "Attack")
            attacks.push_back(new AttackModel(nextLine));

    }

    isActive = true;
    level = 1;
    xp = 0;

    currentHealth = getMaxHealth();
    currentMP = getMaxMP();

    equippedWeapon = nullptr;
    equippedArmor = nullptr;
    equippedAccessory1 = nullptr;
    equippedAccessory2 = nullptr;
}

PlayerCharacterStats::~PlayerCharacterStats()
{
    for(int i = 0; i < attacks.size(); i++)
    {
        delete attacks.at(i);
    }
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

std::string PlayerCharacterStats::getTimelineSpriteKey()
{
    return timelineSpriteKey;
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

    if(this->currentHealth > getMaxHealth())
        this->currentHealth = getMaxHealth();
    if(this->currentHealth < 0)
        this->currentHealth = 0;
}

void PlayerCharacterStats::changeCurrentMP(int mp)
{
    this->currentMP += mp;

    if(this->currentMP > getMaxMP())
        this->currentMP = getMaxMP();
    if(this->currentMP < 0)
        this->currentMP = 0;
}

void PlayerCharacterStats::setIsActive(bool value)
{
    this->isActive = value;
}

std::vector<AttackModel *> *PlayerCharacterStats::getAttacks()
{
    return &attacks;
}

void PlayerCharacterStats::setWeapon(EquipmentModel *weapon)
{
    this->equippedWeapon = weapon;
}

EquipmentModel *PlayerCharacterStats::getWeapon()
{
    return equippedWeapon;
}

void PlayerCharacterStats::setArmor(EquipmentModel *armor)
{
    this->equippedArmor = armor;
}

EquipmentModel *PlayerCharacterStats::getArmor()
{
    return equippedArmor;
}

void PlayerCharacterStats::setAccessory1(EquipmentModel *acc)
{
    this->equippedAccessory1 = acc;
}

EquipmentModel *PlayerCharacterStats::getAccessory1()
{
    return equippedAccessory1;
}

void PlayerCharacterStats::setAccessory2(EquipmentModel *acc)
{
    this->equippedAccessory2 = acc;
}

EquipmentModel *PlayerCharacterStats::getAccessory2()
{
    return equippedAccessory2;
}

int PlayerCharacterStats::getEquipmentID()
{
    return equipmentID;
}

int PlayerCharacterStats::getResistantValueBasedOnEquipmentAndAbilites(std::string key)
{
    int resValue = 0;

    if(equippedArmor != nullptr)
    {
        if(equippedArmor->getEffect() == key)
        {
            resValue += equippedArmor->getMultiplier();
        }
    }
    if(equippedAccessory1 != nullptr)
    {
        if(equippedAccessory1->getEffect() == key)
        {
            resValue += equippedAccessory1->getMultiplier();
        }
    }
    if(equippedAccessory2 != nullptr)
    {
        if(equippedAccessory2->getEffect() == key)
        {
            resValue += equippedAccessory2->getMultiplier();
        }
    }

    return resValue;
}

float PlayerCharacterStats::getAttackElementalMultiplier(int element)
{
    int resValue = 100;

    if(equippedWeapon != nullptr)
    {
        if(isAValidElement(equippedWeapon->getEffect()))
        {
            if(std::stoi(equippedWeapon->getEffect()) == element)
            {
                resValue += equippedWeapon->getMultiplier();
            }
        }
    }
    if(equippedAccessory1 != nullptr)
    {
        if(isAValidElement(equippedAccessory1->getEffect()))
        {
            if(std::stoi(equippedAccessory1->getEffect()) > 0)
            {
                if(std::stoi(equippedAccessory1->getEffect()) == element)
                {
                    resValue += equippedAccessory1->getMultiplier();
                }
            }
        }
    }
    if(equippedAccessory2 != nullptr)
    {
        if(isAValidElement(equippedAccessory2->getEffect()))
        {
            if(std::stoi(equippedAccessory2->getEffect()) > 0)
            {
                if(std::stoi(equippedAccessory2->getEffect()) == element)
                {
                    resValue += equippedAccessory2->getMultiplier();
                }
            }
        }
    }

    return resValue/100.f;
}

float PlayerCharacterStats::getDefenceElementalMultiplier(int element)
{
    int resValue = 100;

    if(equippedArmor != nullptr)
    {
        if(isAValidElement(equippedArmor->getEffect()))
        {
            if(std::stoi(equippedArmor->getEffect()) == element)
            {
                resValue -= equippedArmor->getMultiplier();
            }
        }
    }
    if(equippedAccessory1 != nullptr)
    {
        if(isAValidElement(equippedAccessory1->getEffect()))
        {
            if(std::stoi(equippedAccessory1->getEffect()) < 0)
            {
                if(std::abs(std::stoi(equippedAccessory1->getEffect())) == element)
                {
                    resValue -= equippedAccessory1->getMultiplier();
                }
            }
        }
    }
    if(equippedAccessory2 != nullptr)
    {
        if(isAValidElement(equippedAccessory2->getEffect()))
        {
            if(std::stoi(equippedAccessory2->getEffect()) < 0)
            {
                if(std::abs(std::stoi(equippedAccessory2->getEffect())) == element)
                {
                    resValue -= equippedAccessory2->getMultiplier();
                }
            }
        }
    }

    if(resValue < 0)
        resValue = 0;

    return resValue/100.f;
}

bool PlayerCharacterStats::isAValidElement(std::string input)
{
    if(input == "0")
        return true;
    if(input == "1")
        return true;
    if(input == "2")
        return true;
    if(input == "3")
        return true;
    if(input == "4")
        return true;
    if(input == "5")
        return true;
    if(input == "6")
        return true;
    if(input == "7")
        return true;
    if(input == "8")
        return true;
    if(input == "9")
        return true;
    if(input == "-1")
        return true;
    if(input == "-2")
        return true;
    if(input == "-3")
        return true;
    if(input == "-4")
        return true;
    if(input == "-5")
        return true;
    if(input == "-6")
        return true;
    if(input == "-7")
        return true;
    if(input == "-8")
        return true;
    if(input == "-9")
        return true;

    return false;
}



