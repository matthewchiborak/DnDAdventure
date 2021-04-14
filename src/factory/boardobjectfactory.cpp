#include "boardobjectfactory.h"

#include <sstream>

#include "../filemanagment/fileReader.h"
#include "../model/boardobjectobstacle.h"
#include "../model/boardobjectnpc.h"
#include "../model/boardobjectchest.h"
#include "../model/boardobjectcutscenetrigger.h"
#include "../model/doorway.h"

BoardObjectFactory::BoardObjectFactory()
{

}

void BoardObjectFactory::populate(std::vector<BoardObjectAbstract *> *boardObjects, std::vector<Doorway*> * doors, std::vector<std::string> *encTable, std::string *battleBackgroundKey, std::string *bgMusicKey, int *xPos, int *yPos, std::string boardFileName)
{
    FileReader reader(boardFileName);

    while(reader.hasNext())
    {
        std::vector<std::string> vect = reader.splitString(reader.next(), ',');

        if(vect.size() > 0)
        {
            if(vect.at(0) == "obs")
                boardObjects->push_back(createObstacle(vect));
            else if(vect.at(0) == "npc")
                    boardObjects->push_back(createNPC(vect));
            else if(vect.at(0) == "map")
                    boardObjects->push_back(createMap(vect));
            else if(vect.at(0) == "ranenc")
                    encTable->push_back(vect.at(1));
            else if(vect.at(0) == "battleBG")
                    (*battleBackgroundKey) = (vect.at(1));
            else if(vect.at(0) == "playerpos")
            {
                (*xPos) = std::stoi(vect.at(1));
                (*yPos) = std::stoi(vect.at(2));
            }
            else if(vect.at(0) == "door")
                doors->push_back(createDoorway(vect));
            else if(vect.at(0) == "chest")
                boardObjects->push_back(createChest(vect));
            else if(vect.at(0) == "cutscene")
                boardObjects->push_back(createCutsceneTrigger(vect));
            else if(vect.at(0) == "musicBG")
                (*bgMusicKey) = (vect.at(1));
        }
    }
}

BoardObjectAbstract *BoardObjectFactory::createObstacle(std::vector<std::string> info)
{
    return new BoardObjectObstacle(
                                   -1,//std::stoi(info.at(6)),
                                   std::stoi(info.at(1)),
                                   std::stoi(info.at(2)),
                                   std::stoi(info.at(3)),
                                   std::stoi(info.at(4)),
                                   info.at(5),
                                   true
                );
}

BoardObjectAbstract *BoardObjectFactory::createChest(std::vector<std::string> info)
{
    return new BoardObjectChest(
                std::stoi(info.at(8)),
                std::stoi(info.at(1)),
                std::stoi(info.at(2)),
                std::stoi(info.at(3)),
                std::stoi(info.at(4)),
                info.at(5),
                true,
                info.at(6),
                info.at(7)
                );
}

BoardObjectAbstract *BoardObjectFactory::createMap(std::vector<std::string> info)
{
    return new BoardObjectObstacle(
                                   -1,//std::stoi(info.at(6)),
                                   std::stoi(info.at(1)),
                                   std::stoi(info.at(2)),
                                   std::stoi(info.at(3)),
                                   std::stoi(info.at(4)),
                                   info.at(5),
                                   false
                );
}

BoardObjectAbstract *BoardObjectFactory::createNPC(std::vector<std::string> info)
{
    return new BoardObjectNPC(
                                   -1,//std::stoi(info.at(6)),
                                   std::stoi(info.at(1)),
                                   std::stoi(info.at(2)),
                                   std::stoi(info.at(3)),
                                   std::stoi(info.at(4)),
                                   info.at(5),
                                   true,
                                   info.at(6)
                );
}

BoardObjectAbstract *BoardObjectFactory::createCutsceneTrigger(std::vector<std::string> info)
{
    return new BoardObjectCutsceneTrigger(
                -1,//std::stoi(info.at(7)),
                std::stoi(info.at(1)),
                std::stoi(info.at(2)),
                std::stoi(info.at(3)),
                std::stoi(info.at(4)),
                info.at(5),
                false,
                info.at(6)
                );
}

Doorway *BoardObjectFactory::createDoorway(std::vector<std::string> info)
{
    return new Doorway(
                std::stoi(info.at(1)),
                std::stoi(info.at(2)),
                std::stoi(info.at(3)),
                std::stoi(info.at(4)),
                info.at(5),
                std::stoi(info.at(6)),
                std::stoi(info.at(7))
                );
}
