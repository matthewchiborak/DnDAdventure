#ifndef PLAYERCHARACTERSTATS_H
#define PLAYERCHARACTERSTATS_H

#include <iostream>

class PlayerCharacterStats
{
public:
    PlayerCharacterStats(std::string filepath);

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
    std::string getName();
    std::string getSpriteKey();

    void setLevel(int lvl);
    void setXP(int xp);
    void changeXP(int amount);
    void setCurrentHealth(int hp);
    void changeCurrentHealth(int amount);
    void setIsActive(bool value);

private:
    std::string name;
    bool isActive;
    int level;
    int xp;
    int currentHealth;
    std::string spriteKey;

    //base stats
    int maxHealth;
    int attack;
    int defence;
    int magicAttack;
    int magicDefence;
    int speed;

};

#endif // PLAYERCHARACTERSTATS_H
