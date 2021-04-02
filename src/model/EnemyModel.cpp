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
