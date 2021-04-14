#ifndef MODELABSTRACT_H
#define MODELABSTRACT_H

#include "boardmodel.h"
#include "../display/spriteflyweightfactoryabstract.h"
#include "../model/playercharacterstats.h"

#include <queue>

class MonsterManualEntry;
class DrawInformation;
class EquipmentModel;
class MusicControllerAbstract;

class ModelAbstract
{
public:
    ModelAbstract(MusicControllerAbstract * musicController);
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
    virtual void specialMessage(std::string message, std::string key);

    std::vector<PlayerCharacterStats*> playerCharacters;

    void addEquipment(std::string info);
    std::vector<EquipmentModel> * getEquipment();

    bool getPauseIsDone();
    void setPauseIsDone(bool value);

    int getNumberOfPotions();
    void setNumberOfPotions(int value);
    void changePotionAmount(int amount);
    int getNumberOfRemedies();
    void setNumberOfRemedies(int value);
    void changeRemedyAmount(int amount);
    int getGold();
    void changeGold(int amount);
    void setGold(int value);

    int getNumberOfEthers();
    int getNumberOfJars();
    void setNumberOfEthers(int value);
    void setNumberofJars(int value);
    void changeEtherAmount(int amount);
    void changeJarAmount(int amount);

    void loadMonsterManual(std::string filepath);
    std::vector<MonsterManualEntry> * getMonsterManual();

    virtual std::string interact();
    virtual std::string standOnInteract();

    void updateInventoryBasedOnString(std::string message);

    bool hasBoardDialogRemaining();
    std::string getNextBoardDialog();

    //Cutscenes
    virtual void loadCutscene(std::string filepath);
    virtual void drawCutscene(std::vector<DrawInformation> * items);
    virtual bool cutsceneIsDone();
    virtual bool loadBoardBasedOnLoadedCutscene();

    virtual void loadSaveGame();

    virtual bool doIStartANewGame();
    virtual void drawTitleScreen(std::vector<DrawInformation> * items);

protected:
    bool pauseIsDone = false;
    //Bag
    int gold = 0;
    int numberOfPotions = 0;
    int numberOfRemedies = 0;
    int numberOfEthers = 0;
    int numberOfPickleJars = 0;
    std::vector<EquipmentModel> equipment;

    std::vector<MonsterManualEntry> monsterManual;

    std::vector<int> boardObjectsInteratctedWith;
    std::queue<std::string> boardModelDialog;

    virtual void saveGame();



};

#endif // MODELABSTRACT_H
