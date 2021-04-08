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
    int getDamage();
    std::string getDescription();

private:
    std::string name;
    int castTime; //
    int mpcost;
    int damage;
    std::string description;

    //Additional effects? Lets get basic attack done first
};

#endif // ATTACKMODEL_H
