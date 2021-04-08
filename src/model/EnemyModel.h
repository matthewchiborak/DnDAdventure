#ifndef ENEMY_MODEL_HEADER
#define ENEMY_MODEL_HEADER

#include <string>

//Class for storing all the information relating to enemies in the game.
class EnemyModel
{
public:
    EnemyModel(int maxHP, int att, int def, int mAtt, int mDef, int speed);
    EnemyModel();

    void addAttack();

    void setMaxHealth(int value);
    void setAttack(int value);
    void setDefence(int value);
    void setMagicAttack(int value);
    void setMagicDefence(int value);
    void setSpeed(int value);
    void setSpriteKey(std::string value);
    void setName(std::string value);

    int getCurrentHealth();
    int getMaxHealth();
    int getAttack();
    int getDefence();
    int getMagicAttack();
    int getMagicDefence();
    int getSpeed();
    std::string getSpriteKey();
    std::string getName();
    float getTimeLinePos();
    void setTimeLinePos(float value);

private:
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
};

#endif
