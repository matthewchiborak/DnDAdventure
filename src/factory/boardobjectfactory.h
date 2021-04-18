#ifndef BOARDOBJECTFACTORY_H
#define BOARDOBJECTFACTORY_H

#include <iostream>

#include "worldobjectfactoryabstract.h"

class BoardObjectAbstract;

class BoardObjectFactory : public WorldObjectFactoryAbstract
{
public:
    BoardObjectFactory();

    void populate(std::vector<BoardObjectAbstract*> * boardObjects,
                  std::vector<Doorway*> * doors,
                  std::vector<std::string> * encTable,
                  std::string * battleBackgroundKey, std::string * bgMusicKey,
                  int * xPos, int * yPos, std::string boardFileName);

private:
    BoardObjectAbstract * createObstacle(std::vector<std::string> info);
    BoardObjectAbstract * createChest(std::vector<std::string> info);
    BoardObjectAbstract * createShop(std::vector<std::string> info);
    BoardObjectAbstract * createMap(std::vector<std::string> info);
    BoardObjectAbstract * createNPC(std::vector<std::string> info);
    BoardObjectAbstract * createCutsceneTrigger(std::vector<std::string> info);
    BoardObjectAbstract * createSavePoint(std::vector<std::string> info);
    Doorway * createDoorway(std::vector<std::string> info);
};

#endif // BOARDOBJECTFACTORY_H
