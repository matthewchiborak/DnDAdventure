#ifndef BATTLEMODEL_H
#define BATTLEMODEL_H

#include <vector>
#include <string>
#include "../controller/battlemenustate.h"

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
    void draw(std::vector<DrawInformation> * items);
    void passTime(float value);

    void moveMenuCursor(int x, int y);
    void enterMenu();
    void closeMenu();

    std::vector<PlayerCharacterStats*> * getCharacters();
    std::vector<EnemyModel*> * getEnemies();
    float getP1TimeLinePos();
    float getP2TimeLinePos();
    void setP1TimeLinePos(float value);
    void setP2TimeLinePos(float value);

private:
    //factory for building the enounter
    EncounterFactory * encounterFact;

    float timelineP1Pos = 0; // scale of 0-1200. 1000 being the attack time?
    float timelineP2Pos = 0;
    const float timeLineOffset = -618;

    //vector of enemies
    std::vector<EnemyModel*> enemies;

    std::string backgroundImageKey;

    //buffs defuffs?

    std::vector<PlayerCharacterStats*> * characters;
    BattleMenuState * battleMenuState;
};

#endif // BATTLEMODEL_H
