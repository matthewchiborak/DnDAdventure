#include "playercharacterstatsbattle.h"

PlayerCharacterStatsBattle::PlayerCharacterStatsBattle(PlayerCharacterStats *characterInfo)
{
    this->stats = characterInfo;
}

void PlayerCharacterStatsBattle::applyTime(float t)
{
    statusEffectModel.applyTime(t);
}

void PlayerCharacterStatsBattle::justGotToEndOfTimeLine()
{
    if(statusEffectModel.poison)
        changeCurrentHealth(-1 * statusEffectModel.poisonDamagePercentagePerAction * getMaxHealth());
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
    if(statusEffectModel.SE_att != 0)
        return statusEffectModel.SE_att * 1.5f * stats->getAttack();

    return stats->getAttack();
}

int PlayerCharacterStatsBattle::getDefence()
{
    if(statusEffectModel.guard)
        return stats->getDefence() * 0.5f;

    if(statusEffectModel.SE_def != 0)
        return statusEffectModel.SE_def * 1.5f * stats->getDefence();

    return stats->getDefence();
}

int PlayerCharacterStatsBattle::getMagicAttack()
{
    if(statusEffectModel.SE_magic != 0)
        return statusEffectModel.SE_magic * 1.5f * stats->getMagicAttack();

    return stats->getMagicAttack();
}

int PlayerCharacterStatsBattle::getMagicDefence()
{
    if(statusEffectModel.guard)
        return stats->getMagicDefence() * 0.5f;

    if(statusEffectModel.SE_magicDef != 0)
        return statusEffectModel.SE_magicDef * 1.5f * stats->getMagicDefence();

    return stats->getMagicDefence();
}

int PlayerCharacterStatsBattle::getSpeed()
{
    if(statusEffectModel.sleep)
        return 0;

    if(statusEffectModel.SE_speed != 0)
        return statusEffectModel.SE_speed * 1.5f * stats->getSpeed();

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

void PlayerCharacterStatsBattle::applyStatusEffect(std::string se)
{
    statusEffectModel.applyStatusEffect(se);
}

StatusEffectModel *PlayerCharacterStatsBattle::getStatusEffectModel()
{
    return &statusEffectModel;
}




