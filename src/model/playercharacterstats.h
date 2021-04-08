#ifndef PLAYERCHARACTERSTATS_H
#define PLAYERCHARACTERSTATS_H

#include <iostream>
#include <vector>

class AttackModel;

class PlayerCharacterStats
{
public:
    PlayerCharacterStats(std::string filepath);
    ~PlayerCharacterStats();

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

private:
    std::string name;
    bool isActive;
    int level;
    int xp;
    int currentHealth;
    std::string spriteKey;
    std::string menuSpriteKey;
    std::string timelineSpriteKey;
    int currentMP;

    //base stats
    int baseHealth;
    int baseMP;
    int attack;
    int defence;
    int magicAttack;
    int magicDefence;
    int speed;

    int IVHP;
    int IVMP;
    int IVAtt;
    int IVDef;
    int IVMAtt;
    int IVMDef;
    int IVSpeed;

    std::vector<AttackModel*> attacks;
};

#endif // PLAYERCHARACTERSTATS_H
