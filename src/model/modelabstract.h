#ifndef MODELABSTRACT_H
#define MODELABSTRACT_H

#include "boardmodel.h"
#include "../display/spriteflyweightfactoryabstract.h"
#include "../model/playercharacterstats.h"

class DrawInformation;

class ModelAbstract
{
public:
    ModelAbstract();
    ~ModelAbstract();
    void addPlayerCharacter(PlayerCharacterStats* character);

    virtual void drawBoardModel(std::vector<DrawInformation> * items, float *xOffset, float *yOffset);
    virtual void loadBoardModel(std::string loadInfo);
    virtual std::string handleBoardCollisionTriggers();

    virtual void movePlayer(int x, int y, float t);

    virtual void drawPauseMenu(std::vector<DrawInformation> * items);
    virtual void moveMenuCursor(int x, int y, std::string key);
    virtual void enterMenu(std::string key);
    virtual void closeMenu(std::string key);

    //Will return true if a battle starts
    virtual bool tryToStartABattle();
    virtual void drawBattleModel(std::vector<DrawInformation> * items);
    virtual void passTime(float value);
    virtual bool isBattleDone();
    virtual bool isGameOver();
    virtual void qrPressed(bool wasQ);

    std::vector<PlayerCharacterStats*> playerCharacters;
};

#endif // MODELABSTRACT_H
