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
    this->level = 1;
}

EnemyModel::EnemyModel()
{
    this->timelinePos = 0;
}

void EnemyModel::applyTime(float t)
{
    statusEffectModel.applyTime(t);
}

void EnemyModel::justGotToEndOfTimeLine()
{
    if(statusEffectModel.poison)
        changeHealth(-1 * statusEffectModel.poisonDamagePercentagePerAction * getMaxHealth());
}

void EnemyModel::setLevel(int level)
{
    this->level = level;
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

void EnemyModel::setXP(int value)
{
    this->xp = value;
}

int EnemyModel::getLevel()
{
    return level;
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
    if(statusEffectModel.SE_att != 0)
        return (1.f + (statusEffectModel.SE_att * 0.25f)) * attack;

    return attack;
}
int EnemyModel::getDefence()
{
    if(statusEffectModel.SE_def != 0)
        return (1.f + (statusEffectModel.SE_def * 0.25f)) * defence;

    return defence;
}
int EnemyModel::getMagicAttack()
{
    if(statusEffectModel.SE_magic != 0)
        return (1.f + (statusEffectModel.SE_magic * 0.25f)) * magicAttack;

    return magicAttack;
}
int EnemyModel::getMagicDefence()
{
    if(statusEffectModel.SE_magicDef != 0)
        return (1.f + (statusEffectModel.SE_magicDef * 0.25f)) * magicDefence;

    return magicDefence;
}
int EnemyModel::getSpeed()
{
    if(statusEffectModel.sleep)
        return 0;

    if(statusEffectModel.SE_speed != 0)
        return (1.f + (statusEffectModel.SE_speed * 0.25f)) * speed;

    return speed;
}

int EnemyModel::getXP()
{
    return xp;
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

void EnemyModel::changeHealth(int amount)
{
    currentHealth += amount;

    if(currentHealth < 0)
        currentHealth = 0; //Die
    if(currentHealth > maxHealth)
        currentHealth = maxHealth;
}

float EnemyModel::getElementalMultiplier(int element)
{
    return 1.f;
}

void EnemyModel::addAttack(AttackModel *newAtt)
{
    attacks.push_back(newAtt);
}

std::vector<AttackModel *> *EnemyModel::getAttacks()
{
    return &attacks;
}

void EnemyModel::stopCasting()
{
    isCasting = false;
}

void EnemyModel::castARandomAttack(bool p1Alive, bool p2Alive)
{
    this->attackIndex = rand()%attacks.size();

    if(!p1Alive)
        attackTarget = 1;
    else if(!p2Alive)
        attackTarget = 0;
    else
        attackTarget = rand()%2;

    isCasting = true;
}

bool EnemyModel::getIsCasting()
{
    return isCasting;
}

AttackModel *EnemyModel::getCastingAttack()
{
    return attacks.at(attackIndex);
}

int EnemyModel::getAttackTarget()
{
    return attackTarget;
}

bool EnemyModel::getAttackTargetAlly()
{
    return attackTargetAlly;
}

void EnemyModel::applyStatusEffect(std::string se)
{
    statusEffectModel.applyStatusEffect(se);
}

StatusEffectModel *EnemyModel::getStatusEffectModel()
{
    return &statusEffectModel;
}

bool EnemyModel::tryInterrupt(float amount)
{
    if(!isCasting)
    {
        return false;
    }

    isCasting = false;
    timelinePos -= amount;

    return true;
}
