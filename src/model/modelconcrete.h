#ifndef MODELCONCRETE_H
#define MODELCONCRETE_H

#include "modelabstract.h"
#include "battlemodel.h"

class PauseMenuDrawState;

class ModelConcrete : public ModelAbstract
{
public:
    ModelConcrete();
    void drawBoardModel(std::vector<DrawInformation> * items, float *xOffset, float *yOffset);
    void loadBoardModel(std::string loadInfo);
    std::string handleBoardCollisionTriggers();
    void movePlayer(int x, int y, float t);

    //
    void drawPauseMenu(std::vector<DrawInformation> * items);
    void moveMenuCursor(int x, int y, std::string key);
    void enterMenu(std::string key);
    void closeMenu(std::string key);

    bool tryToStartABattle();
    void drawBattleModel(std::vector<DrawInformation> * items);
    void passTime(float value);
    bool isBattleDone();
    bool isGameOver();

private:
    BoardModel boardModel;
    BattleModel battleModel;

    PauseMenuDrawState * currentMenuState;

    int partyGaugeValue = 0;

};

#endif // MODELCONCRETE_H
