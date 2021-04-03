#ifndef ENEMY_MODEL_HEADER
#define ENEMY_MODEL_HEADER

//Class for storing all the information relating to enemies in the game.
class EnemyModel
{
public:
    EnemyModel(int maxHP, int att, int def, int mAtt, int mDef, int speed);

    int getCurrentHealth();
    int getMaxHealth();
    int getAttack();
    int getDefence();
    int getMagicAttack();
    int getMagicDefence();
    int getSpeed();

private:
    int maxHealth;
    int currentHealth;
    int attack;
    int defence;
    int magicAttack;
    int magicDefence;
    int speed;
};

#endif
