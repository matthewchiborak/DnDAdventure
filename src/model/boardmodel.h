#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <vector>

#include "gamemodelabstract.h"
#include "../factory/boardobjectfactory.h"
#include "../controller/musiccontrollerabstract.h"

class BoardObjectAbstract;

class BoardModel //: public GameModelAbstract
{
public:
    BoardModel();

    //void draw(QPainter *p);
    void load(std::string loadInfo, std::vector<int> * boardObjectInteractedWith);
    void clear();

    std::string interact(int * objId);
    std::string standOnInteract();

    std::vector<BoardObjectAbstract*> * getObjects();
    std::vector<Doorway*> * getDoors();

    void movePlayer(int x, int y, float t);
    void setPlayerPos(int x, int y);

    float getXOffset();
    float getYOffset();
    int getXPos();
    int getYPos();

    void checkAndActivateDoor();

    bool tryToGetAnEnounter(std::string * keyToReturn);

    std::string getBattleBackgroundKey();

    void setMusicController(MusicControllerAbstract * musicController);
    void playBGMusic();

    std::string getLastLoadedFilePath();

private:
    std::string lastLoadedFilePath;
    std::vector<BoardObjectAbstract*> boardObjects;
    std::vector<Doorway*> doors;
    BoardObjectFactory factory;

    std::vector<std::string> encounterTable;
    std::string battleBackgroundKey;
    std::string backgroundMusicKey;

    int xPos;
    int yPos;
    float xOffset;
    float yOffset;

    int lastDirectionMovedX;
    int lastDirectionMovedY;

    std::vector<int> * boardObjectInteractedWith;

    MusicControllerAbstract * musicController;

    bool lastMoveCallWasSuccess = true;
    int stepsSinceLastEnouncter = 0;

    bool playerCanMoveThisWay(int x, int y);
};

#endif // BOARDMODEL_H
