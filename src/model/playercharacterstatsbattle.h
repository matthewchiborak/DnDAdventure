#ifndef PLAYERCHARACTERSTATSBATTLE_H
#define PLAYERCHARACTERSTATSBATTLE_H

#include "playercharacterstats.h"
#include "statuseffectmodel.h"

//Acts as middle so can apply out of battle non persistant stats
//like buffs and debuffs.

class PlayerCharacterStatsBattle
{
public:
    PlayerCharacterStatsBattle(PlayerCharacterStats * characterInfo);

    void applyTime(float t);
    int justGotToEndOfTimeLine();

    int getCurrentHealth();
    int getMaxHealth();
    int getAttack();
    int getDefence();
    int getMagicAttack();
    int getMagicDefence();
    int getSpeed();
    int getLevel();
    int getXP();
    bool getIsActive();
    int getCurrentMP();
    int getMaxMP();
    std::string getName();
    std::string getSpriteKey();
    std::string getMenuSpriteKey();
    std::string getTimelineSpriteKey();

    void setLevel(int lvl);
    void setXP(int xp);
    void changeXP(int amount);
    void setCurrentHealth(int hp);
    void changeCurrentHealth(int amount);
    void changeCurrentMP(int amount);
    void setIsActive(bool value);

    std::vector<AttackModel*> * getAttacks();

    void stopCasting();
    void beginCasting(int attackIndex, int attackTarget, bool isForAllies);
    bool getIsCasting();
    AttackModel * getCastingAttack();
    int getAttackTarget();
    bool getIsTargetAllies();

    void setTarget(int value);

    float getElementalMultiplier(int element);
    void applyStatusEffect(std::string se);

    StatusEffectModel * getStatusEffectModel();

private:
    PlayerCharacterStats * stats;

    //For attacking
    bool isCasting = false;
    int attackIndex = 0;
    int attackTarget = 0;
    bool attackTargetAllies = false;

    //Effects to apply to stat retrieval
    StatusEffectModel statusEffectModel;
};

#endif // PLAYERCHARACTERSTATSBATTLE_H
