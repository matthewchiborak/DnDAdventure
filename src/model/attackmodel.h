#ifndef ATTACKMODEL_H
#define ATTACKMODEL_H

#include <string>

class AttackModel
{
public:
    AttackModel(std::string info);

    std::string getName();
    int getCastTime(); //
    int getMpcost();
    std::string getMPCostString();
    int getPower();
    std::string getDescription();
    int getAttackType();
    int getElement();
    std::string getAdditionalEffect();
    std::string getAdditionalEffectRoll();
    int getAccuracy();
    int getMultitarget();

    bool isUnlocked();
    void unlock();

private:
    std::string name;
    int castTime; //
    int mpcost;
    int power;
    std::string description;
    int attackType; //0 = phys, 1 = magic ,2 = none
    int element; //0 = none, 1= fire, 2 = ice, 3 = Lightning, 4 = Water, 5 = Wind, 6 = Earth, 7 = Bash, 8 = Slash, 9 = Pierce

    int accuracy;
    int multitarget; //0 = no, 1 = all enemeis, 2 = all allies, 3 = self

    std::string additionalEffect;
    int chanceOfAdditionalEffect;
    //Poison, Sleep, Silence, Slow, Haste, AttackUp, etc.

    bool unlocked = false;
};

#endif // ATTACKMODEL_H
