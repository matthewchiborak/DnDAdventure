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

private:
    std::string name;
    int castTime; //
    int mpcost;
    int power;
    std::string description;
    int attackType; //0 = phys, 1 = magic ,2 = none
    int element; //0 = none, 1= fire, i can decide these later
    //or even make an enum

    //Additional effects? Lets get basic attack done first
};

#endif // ATTACKMODEL_H
