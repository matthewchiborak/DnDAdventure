#ifndef ENEMY_MODEL_HEADER
#define ENEMY_MODEL_HEADER

#include <string>
#include <vector>

#include "statuseffectmodel.h"

class AttackModel;

//Class for storing all the information relating to enemies in the game.
class EnemyModel
{
public:
    EnemyModel(int maxHP, int att, int def, int mAtt, int mDef, int speed);
    EnemyModel();

    void applyTime(float t);
    void justGotToEndOfTimeLine();

    void addAttack();

    void addWeakness(int value);
    void addHalfed(int value);
    void addResistance(int value);
    void addImmunity(int value);
    void addAbsorbed(int value);

    void setLevel(int level);
    void setMaxHealth(int value);
    void setAttack(int value);
    void setDefence(int value);
    void setMagicAttack(int value);
    void setMagicDefence(int value);
    void setSpeed(int value);
    void setSpriteKey(std::string value);
    void setName(std::string value);
    void setXP(int value);

    int getLevel();
    int getCurrentHealth();
    int getMaxHealth();
    int getAttack();
    int getDefence();
    int getMagicAttack();
    int getMagicDefence();
    int getSpeed();
    int getXP();
    std::string getSpriteKey();
    std::string getName();
    float getTimeLinePos();
    void setTimeLinePos(float value);

    void changeHealth(int amount);

    float getElementalMultiplier(int element);

    void addAttack(AttackModel * newAtt);
    std::vector<AttackModel*> * getAttacks();

    void stopCasting();
    void castARandomAttack(bool p1Alive, bool p2Alive);
    bool getIsCasting();
    AttackModel * getCastingAttack();
    int getAttackTarget();
    bool getAttackTargetAlly();

    void applyStatusEffect(std::string se);

    StatusEffectModel * getStatusEffectModel();

    bool tryInterrupt(float amount);

private:
    int level;
    int maxHealth;
    int currentHealth;
    int attack;
    int defence;
    int magicAttack;
    int magicDefence;
    int speed;
    std::string spriteKey;
    std::string name;
    float timelinePos;
    int xp;

    std::vector<AttackModel*> attacks;

    bool isCasting = false;
    int attackIndex = 0;
    int attackTarget = 0;
    bool attackTargetAlly = false;

    StatusEffectModel statusEffectModel;

    std::vector<int> weaknesses;
    std::vector<int> resistances;
    std::vector<int> immunities;
    std::vector<int> halved;
    std::vector<int> absorbed;
};

#endif
