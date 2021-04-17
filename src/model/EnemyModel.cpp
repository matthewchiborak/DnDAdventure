#include "EnemyModel.h"

#include <cmath>

#include "attackmodel.h"

EnemyModel::EnemyModel(int maxHP, int att, int def, int mAtt, int mDef, int speed)
{
    this->maxHealth = maxHP;

    this->attack = att;
    this->defence = def;
    this->magicAttack = mAtt;
    this->magicDefence = mDef;
    this->speed = speed;
    this->timelinePos = 0;
    this->level = 1;

    this->currentHealth = getMaxHealth();
    this->cutsceneToTriggerOnDefeat = "None";
}

EnemyModel::EnemyModel()
{
    this->timelinePos = 0;
    this->cutsceneToTriggerOnDefeat = "None";
}

void EnemyModel::applyTime(float t)
{
    statusEffectModel.applyTime(t);
}

int EnemyModel::justGotToEndOfTimeLine()
{
    int totalDamnage = 0;

    if(statusEffectModel.poison)
         totalDamnage = (-1 * statusEffectModel.poisonDamagePercentagePerAction * getMaxHealth());

    changeHealth(totalDamnage);

    return totalDamnage;
}

void EnemyModel::addWeakness(int value)
{
    weaknesses.push_back(value);
}

void EnemyModel::addHalfed(int value)
{
    halved.push_back(value);
}

void EnemyModel::addResistance(int value)
{
    resistances.push_back(value);
}

void EnemyModel::addImmunity(int value)
{
    immunities.push_back(value);
}

void EnemyModel::addAbsorbed(int value)
{
    absorbed.push_back(value);
}

void EnemyModel::setLevel(int level)
{
    this->level = level;
}

void EnemyModel::setMaxHealth(int value)
{
    this->maxHealth = value;
    this->currentHealth = getMaxHealth();
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
    return floor(0.01f * (2.f * maxHealth + 0 + floor(0.25f * 0)) * (level + 15)) + level + 35;
    //return maxHealth;
}
int EnemyModel::getAttack()
{
    int temp = floor(0.01f * (2.f * attack + 0 + floor(0.25f * 0)) * (level + 15)) + 5;

    if(statusEffectModel.SE_att != 0)
        return (1.f + (statusEffectModel.SE_att * 0.25f)) * temp;

    return temp;
}
int EnemyModel::getDefence()
{
    int temp = floor(0.01f * (2.f * defence + 0 + floor(0.25f * 0)) * (level + 15)) + 5;

    if(statusEffectModel.SE_def != 0)
        return (1.f + (statusEffectModel.SE_def * 0.25f)) * temp;

    return temp;
}
int EnemyModel::getMagicAttack()
{
    int temp = floor(0.01f * (2.f * magicAttack + 0 + floor(0.25f * 0)) * (level + 15)) + 5;

    if(statusEffectModel.SE_magic != 0)
        return (1.f + (statusEffectModel.SE_magic * 0.25f)) * temp;

    return temp;
}
int EnemyModel::getMagicDefence()
{
    int temp = floor(0.01f * (2.f * magicDefence + 0 + floor(0.25f * 0)) * (level + 15)) + 5;

    if(statusEffectModel.SE_magicDef != 0)
        return (1.f + (statusEffectModel.SE_magicDef * 0.25f)) * temp;

    return temp;
}
int EnemyModel::getSpeed()
{
    if(statusEffectModel.sleep)
        return 0;

    int temp = floor(0.01f * (2.f * speed + 0 + floor(0.25f * 0)) * (level + 15)) + 5;

    if(statusEffectModel.SE_speed != 0)
        return (1.f + (statusEffectModel.SE_speed * 0.25f)) * temp;

    return temp;
}

int EnemyModel::getXP(int playerLevel)
{
    int fixedPlayerLevel = playerLevel + 15;
    int fixedLevel = level + 15;
    //What was loaded was the base. Use the formula
    float firstValue = (1 * xp * (fixedLevel)) / (5 * 1);
    float secondValue = (std::powf((2*fixedLevel) + 10, 2.5f)) / (std::powf(fixedLevel + fixedPlayerLevel + 10, 2.5f));
    return ((firstValue * secondValue) + 1) * 1 * 1 * 1;

    //return xp;
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
    if(currentHealth > getMaxHealth())
        currentHealth = getMaxHealth();
}

float EnemyModel::getElementalMultiplier(int element)
{
    for(int i = 0; i < weaknesses.size(); i++)
    {
        if(weaknesses.at(i) == element)
            return 2.f;
    }
    for(int i = 0; i < resistances.size(); i++)
    {
        if(resistances.at(i) == element)
            return 0.25f;
    }
    for(int i = 0; i < halved.size(); i++)
    {
        if(halved.at(i) == element)
            return 0.5f;
    }
    for(int i = 0; i < immunities.size(); i++)
    {
        if(immunities.at(i) == element)
            return 0.0f;
    }
    for(int i = 0; i < absorbed.size(); i++)
    {
        if(absorbed.at(i) == element)
            return -1.f;
    }

    return 1.f;
}

std::string EnemyModel::getElementalString(int element)
{
    for(int i = 0; i < weaknesses.size(); i++)
    {
        if(weaknesses.at(i) == element)
            return "Weakness";
    }
    for(int i = 0; i < resistances.size(); i++)
    {
        if(resistances.at(i) == element)
            return "Resist";
    }
    for(int i = 0; i < halved.size(); i++)
    {
        if(halved.at(i) == element)
            return "Halved";
    }
    for(int i = 0; i < immunities.size(); i++)
    {
        if(immunities.at(i) == element)
            return "Immune";
    }
    for(int i = 0; i < absorbed.size(); i++)
    {
        if(absorbed.at(i) == element)
            return "Absorbed";
    }

    return "Normal";
}

void EnemyModel::getRGB(std::string word, int *r, int *g, int *b)
{
    if(word == "Weakness")
    {
        (*r) = 0;
        (*g) = 255;
        (*b) = 0;
    }
    else if(word == "Resist")
    {
        (*r) = 255;
        (*g) = 165;
        (*b) = 0;
    }
    else if(word == "Halved")
    {
        (*r) = 255;
        (*g) = 255;
        (*b) = 0;
    }
    else if(word == "Immune")
    {
        (*r) = 255;
        (*g) = 0;
        (*b) = 0;
    }
    else if(word == "Absorbed")
    {
        (*r) = 0;
        (*g) = 0;
        (*b) = 255;
    }
    else
    {
        (*r) = 0;
        (*g) = 0;
        (*b) = 0;
    }
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

void EnemyModel::castARandomAttack(bool p1Alive, bool p2Alive, int myIndex, std::vector<int> aliveAllies)
{
    this->attackIndex = rand()%attacks.size();

    if(this->statusEffectModel.silenced)
    {
        for(int i = 0; i < attacks.size(); i++)
        {
            if(this->attacks.at(attackIndex)->getAdditionalEffect() == "None")
            {
                while(this->attacks.at(attackIndex)->getAdditionalEffect() != "None")
                {
                    this->attackIndex = rand()%attacks.size();
                }
                break;
            }
        }
    }

    if(attacks.at(attackIndex)->getMultitarget() == 3)
    {
        this->attackTargetAlly=true;
        attackTarget = myIndex;
    }
    else if(attacks.at(attackIndex)->getMultitarget() == 4)
    {
        int numAlies = 0;
        for(int i = 0; i < aliveAllies.size(); i++)
            numAlies++;

        this->attackTargetAlly = true;
        attackTarget = aliveAllies.at(rand()%numAlies);
    }
    else
    {
        this->attackTargetAlly=false;
        if(!p1Alive)
            attackTarget = 1;
        else if(!p2Alive)
            attackTarget = 0;
        else
            attackTarget = rand()%2;
    }

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

bool EnemyModel::applyStatusEffect(std::string se)
{
    //Check if immune
    if(isImmuneToThis(se))
        return false;

    statusEffectModel.applyStatusEffect(se);

    return true;
}

bool EnemyModel::isImmuneToThis(std::string se)
{
    for(int i = 0; i < statusImmunities.size(); i++)
    {
        if(statusImmunities.at(i) == se)
            return true;
    }

    return false;
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

void EnemyModel::setTarget(int value)
{
    attackTarget = value;
}

void EnemyModel::addStatusImmunity(std::string value)
{
    statusImmunities.push_back(value);
}

float EnemyModel::getAccuracyMultiplier()
{
    if(statusEffectModel.blind)
        return 0.5f;

    return 1.f;
}

void EnemyModel::setEnemyKey(std::string eKey)
{
    enemyKey = eKey;
}

std::string EnemyModel::getEnemyKey()
{
    return enemyKey;
}

void EnemyModel::setCutsceneToPlayOnDefeat(std::string path)
{
    cutsceneToTriggerOnDefeat = path;
}

std::string EnemyModel::getCutsceneToPlayOnDefeat()
{
    return cutsceneToTriggerOnDefeat;
}
