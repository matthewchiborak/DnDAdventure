#ifndef MODELCONCRETE_H
#define MODELCONCRETE_H

#include "modelabstract.h"
#include "battlemodel.h"
#include "cutscenemodel.h"

class PauseMenuDrawState;

class ModelConcrete : public ModelAbstract
{
public:
    ModelConcrete(MusicControllerAbstract * musicController);
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
    void qrPressed(bool wasQ);
    void specialMessage(std::string message, std::string key);

    std::string interact();
    std::string standOnInteract();

    void loadCutscene(std::string filepath);
    void drawCutscene(std::vector<DrawInformation> * items);
    bool cutsceneIsDone();
    bool loadBoardBasedOnLoadedCutscene();


    void loadSaveGame();

    bool doIStartANewGame();

    void drawTitleScreen(std::vector<DrawInformation> * items);

private:
    BoardModel boardModel;
    BattleModel battleModel;
    CutsceneModel cutsceneModel;

    PauseMenuDrawState * currentMenuState;

    int partyGaugeValue = 0;

    int titleMenuPos = 0;

    void saveGame();

};

#endif // MODELCONCRETE_H
