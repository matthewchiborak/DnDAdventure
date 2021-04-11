#include "playercharacterstatsbattle.h"

PlayerCharacterStatsBattle::PlayerCharacterStatsBattle(PlayerCharacterStats *characterInfo)
{
    this->stats = characterInfo;
    this->isVisible = true;
}

void PlayerCharacterStatsBattle::applyTime(float t)
{
    statusEffectModel.applyTime(t);
}

int PlayerCharacterStatsBattle::justGotToEndOfTimeLine()
{
    int totalDamnage = 0;

    if(statusEffectModel.poison)
       totalDamnage = (-1 * statusEffectModel.poisonDamagePercentagePerAction * getMaxHealth());

    changeCurrentHealth(totalDamnage);

    return totalDamnage;
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
    if(statusEffectModel.overdrive)
        return stats->getAttack() * 2.f;

    if(statusEffectModel.SE_att != 0)
        return (1.f + (statusEffectModel.SE_att * 0.25f)) * stats->getAttack();

    return stats->getAttack();
}

int PlayerCharacterStatsBattle::getDefence()
{
    if(statusEffectModel.guard)
        return stats->getDefence() * 2.f;

    if(statusEffectModel.SE_def != 0)
        return (1.f + (statusEffectModel.SE_def * 0.25f)) * stats->getDefence();

    return stats->getDefence();
}

int PlayerCharacterStatsBattle::getMagicAttack()
{
    if(statusEffectModel.overdrive)
        return stats->getMagicAttack() * 2.f;

    if(statusEffectModel.SE_magic != 0)
        return (1.f + (statusEffectModel.SE_magic * 0.25f)) * stats->getMagicAttack();

    return stats->getMagicAttack();
}

int PlayerCharacterStatsBattle::getMagicDefence()
{
    if(statusEffectModel.guard)
        return stats->getMagicDefence() * 2.f;

    if(statusEffectModel.SE_magicDef != 0)
        return (1.f + (statusEffectModel.SE_magicDef * 0.25f)) * stats->getMagicDefence();

    return stats->getMagicDefence();
}

int PlayerCharacterStatsBattle::getSpeed()
{
    if(statusEffectModel.overdrive)
        return stats->getSpeed() * 2.f;

    if(statusEffectModel.sleep)
        return 0;

    float multiplier = 1.f;

    if(statusEffectModel.SE_speed != 0)
        multiplier *= (1.f + (statusEffectModel.SE_speed * 0.25f));

    if(statusEffectModel.guard)
        multiplier *= 1.5f;

    return stats->getSpeed() * multiplier;
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

bool PlayerCharacterStatsBattle::changeXP(int amount)
{
    return stats->changeXP(amount);
}

void PlayerCharacterStatsBattle::setCurrentHealth(int hp)
{
    stats->setCurrentHealth(hp);
}

void PlayerCharacterStatsBattle::changeCurrentHealth(int amount)
{
    stats->changeCurrentHealth(amount);
}

void PlayerCharacterStatsBattle::changeCurrentMP(int amount)
{
    stats->changeCurrentMP(amount);
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

void PlayerCharacterStatsBattle::beginCasting(int attackIndex, int attackTarget, bool isForAllies)
{
    this->attackIndex = attackIndex;
    this->attackTarget = attackTarget;
    this->attackTargetAllies = isForAllies;
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

bool PlayerCharacterStatsBattle::getIsTargetAllies()
{
    return attackTargetAllies;
}

void PlayerCharacterStatsBattle::setTarget(int value)
{
    attackTarget = value;
}

float PlayerCharacterStatsBattle::getElementalMultiplier(int element)
{
    return 1;
}

bool PlayerCharacterStatsBattle::applyStatusEffect(std::string se)
{
    if(se == "None")
        return false;

    //Based on equipement, check if resist
    if(rand()%100 < stats->getResistantValueBasedOnEquipmentAndAbilites(se))
        return false;

    statusEffectModel.applyStatusEffect(se);
    return true;
}

void PlayerCharacterStatsBattle::cureAllStatusEffects()
{
    statusEffectModel.cureAllNegativeStatusEffects();
}

StatusEffectModel *PlayerCharacterStatsBattle::getStatusEffectModel()
{
    return &statusEffectModel;
}

void PlayerCharacterStatsBattle::setIsVisible(bool newIsVisible)
{
    isVisible = newIsVisible;
}

bool PlayerCharacterStatsBattle::getIsVisible()
{
    return isVisible;
}

float PlayerCharacterStatsBattle::getAttackingMultiplier(int attackType)
{
    return stats->getAttackElementalMultiplier(attackType);
}

float PlayerCharacterStatsBattle::getDefendingMultiplier(int attackType)
{
    return stats->getDefenceElementalMultiplier(attackType);
}

float PlayerCharacterStatsBattle::getAccuracyMultiplier()
{
    if(statusEffectModel.blind)
        return 0.5f;

    return 1.f;
}




