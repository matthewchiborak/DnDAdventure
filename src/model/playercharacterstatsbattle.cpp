#include "playercharacterstatsbattle.h"

PlayerCharacterStatsBattle::PlayerCharacterStatsBattle(PlayerCharacterStats *characterInfo)
{
    this->stats = characterInfo;
}

int PlayerCharacterStatsBattle::getCurrentHealth()
{
    return stats->getCurrentHealth();
}

int PlayerCharacterStatsBattle::getMaxHealth()
{
    return stats->getMaxHealth();
}

int PlayerCharacterStatsBattle::getAttack()
{
    return stats->getAttack();
}

int PlayerCharacterStatsBattle::getDefence()
{
    return stats->getDefence();
}

int PlayerCharacterStatsBattle::getMagicAttack()
{
    return stats->getMagicAttack();
}

int PlayerCharacterStatsBattle::getMagicDefence()
{
    return stats->getMagicDefence();
}

int PlayerCharacterStatsBattle::getSpeed()
{
    return stats->getSpeed();
}

int PlayerCharacterStatsBattle::getLevel()
{
    return stats->getLevel();
}

int PlayerCharacterStatsBattle::getXP()
{
    return stats->getXP();
}

bool PlayerCharacterStatsBattle::getIsActive()
{
    return stats->getIsActive();
}

int PlayerCharacterStatsBattle::getCurrentMP()
{
    return stats->getCurrentMP();
}

int PlayerCharacterStatsBattle::getMaxMP()
{
    return stats->getMaxMP();
}

std::string PlayerCharacterStatsBattle::getName()
{
    return stats->getName();
}

std::string PlayerCharacterStatsBattle::getSpriteKey()
{
    return stats->getSpriteKey();
}

std::string PlayerCharacterStatsBattle::getMenuSpriteKey()
{
    return stats->getMenuSpriteKey();
}

std::string PlayerCharacterStatsBattle::getTimelineSpriteKey()
{
    return stats->getTimelineSpriteKey();
}

void PlayerCharacterStatsBattle::setLevel(int lvl)
{
    stats->setLevel(lvl);
}

void PlayerCharacterStatsBattle::setXP(int xp)
{
    stats->setXP(xp);
}

void PlayerCharacterStatsBattle::changeXP(int amount)
{
    stats->changeXP(amount);
}

void PlayerCharacterStatsBattle::setCurrentHealth(int hp)
{
    stats->setCurrentHealth(hp);
}

void PlayerCharacterStatsBattle::changeCurrentHealth(int amount)
{
    stats->changeCurrentHealth(amount);
}

void PlayerCharacterStatsBattle::setIsActive(bool value)
{
    stats->setIsActive(value);
}

std::vector<AttackModel *> *PlayerCharacterStatsBattle::getAttacks()
{
    return stats->getAttacks();
}

void PlayerCharacterStatsBattle::stopCasting()
{
    isCasting = false;
}

void PlayerCharacterStatsBattle::beginCasting(int attackIndex, int attackTarget)
{
    this->attackIndex = attackIndex;
    this->attackTarget = attackTarget;
    isCasting = true;
}

bool PlayerCharacterStatsBattle::getIsCasting()
{
    return isCasting;
}

AttackModel *PlayerCharacterStatsBattle::getCastingAttack()
{
    return stats->getAttacks()->at(attackIndex);
}

int PlayerCharacterStatsBattle::getAttackTarget()
{
    return attackTarget;
}

float PlayerCharacterStatsBattle::getElementalMultiplier(int element)
{
    return 1;
}


