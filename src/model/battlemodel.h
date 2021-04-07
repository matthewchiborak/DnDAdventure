#ifndef BATTLEMODEL_H
#define BATTLEMODEL_H

#include <vector>
#include <string>

class PlayerCharacterStats;
class DrawInformation;
class EnemyModel;
class EncounterFactory;

class BattleModel
{
public:
    BattleModel();

    void clear();
    void load(std::string key, std::vector<PlayerCharacterStats*> * characters);
    void draw(std::vector<DrawInformation> * drawInfo);
    void passTime(float value);

private:
    //factory for building the enounter
    EncounterFactory * encounterFact;

    float timelineP1Pos;
    float timelineP2Pos;

    //vector of enemies
    std::vector<EnemyModel*> enemies;

    std::string backgroundImageKey;

    //buffs defuffs?

    std::vector<PlayerCharacterStats*> * characters;
};

#endif // BATTLEMODEL_H
