#ifndef PLAYERCHARACTERSTATSBATTLE_H
#define PLAYERCHARACTERSTATSBATTLE_H

#include "playercharacterstats.h"

//Acts as middle so can apply out of battle non persistant stats
//like buffs and debuffs.

class PlayerCharacterStatsBattle
{
public:
    PlayerCharacterStatsBattle(PlayerCharacterStats * characterInfo);

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
    void setIsActive(bool value);

    std::vector<AttackModel*> * getAttacks();

    void stopCasting();
    void beginCasting(int attackIndex, int attackTarget);
    bool getIsCasting();
    AttackModel * getCastingAttack();
    int getAttackTarget();

    float getElementalMultiplier(int element);


private:
    PlayerCharacterStats * stats;

    //For attacking
    bool isCasting = false;
    int attackIndex = 0;
    int attackTarget = 0;

    //Effects to apply to stat retrieval

};

#endif // PLAYERCHARACTERSTATSBATTLE_H
