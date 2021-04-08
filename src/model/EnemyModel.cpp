#include "EnemyModel.h"

EnemyModel::EnemyModel(int maxHP, int att, int def, int mAtt, int mDef, int speed)
{
    this->maxHealth = maxHP;
    this->currentHealth = maxHP;
    this->attack = att;
    this->defence = def;
    this->magicAttack = mAtt;
    this->magicDefence = mDef;
    this->speed = speed;
    this->timelinePos = 0;
}

EnemyModel::EnemyModel()
{
    this->timelinePos = 0;
}

void EnemyModel::setMaxHealth(int value)
{
    this->maxHealth = value;
    this->currentHealth = value;
}

void EnemyModel::setAttack(int value)
{
    this->attack = value;
}

void EnemyModel::setDefence(int value)
{
    this->defence = value;
}

void EnemyModel::setMagicAttack(int value)
{
    this->magicAttack = value;
}

void EnemyModel::setMagicDefence(int value)
{
    this->magicDefence = value;
}

void EnemyModel::setSpeed(int value)
{
    this->speed = value;
}

void EnemyModel::setSpriteKey(std::string value)
{
    this->spriteKey = value;
}

void EnemyModel::setName(std::string value)
{
    this->name = value;
}

int EnemyModel::getCurrentHealth()
{
    return currentHealth;
}
int EnemyModel::getMaxHealth()
{
    return maxHealth;
}
int EnemyModel::getAttack()
{
    return attack;
}
int EnemyModel::getDefence()
{
    return defence;
}
int EnemyModel::getMagicAttack()
{
    return magicAttack;
}
int EnemyModel::getMagicDefence()
{
    return magicDefence;
}
int EnemyModel::getSpeed()
{
    return speed;
}

std::string EnemyModel::getSpriteKey()
{
    return spriteKey;
}

std::string EnemyModel::getName()
{
    return name;
}

float EnemyModel::getTimeLinePos()
{
    return timelinePos;
}

void EnemyModel::setTimeLinePos(float value)
{
    timelinePos = value;
}
