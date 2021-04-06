#include "boardobjectfactory.h"

#include <sstream>

#include "../filemanagment/fileReader.h"
#include "../model/boardobjectobstacle.h"
#include "../model/doorway.h"

BoardObjectFactory::BoardObjectFactory()
{

}

void BoardObjectFactory::populate(std::vector<BoardObjectAbstract *> *boardObjects, std::vector<Doorway*> * doors, int *xPos, int *yPos, std::string boardFileName)
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
            else if(vect.at(0) == "playerpos")
            {
                (*xPos) = std::stoi(vect.at(1));
                (*yPos) = std::stoi(vect.at(2));
            }
            else if(vect.at(0) == "door")
                doors->push_back(createDoorway(vect));
        }
    }
}

BoardObjectAbstract *BoardObjectFactory::createObstacle(std::vector<std::string> info)
{
    return new BoardObjectObstacle(
                                   std::stoi(info.at(1)),
                                   std::stoi(info.at(2)),
                                   std::stoi(info.at(3)),
                                   std::stoi(info.at(4)),
                                   info.at(5),
                                   true
                );
}

BoardObjectAbstract *BoardObjectFactory::createMap(std::vector<std::string> info)
{
    return new BoardObjectObstacle(
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
    return new BoardObjectObstacle(
                                   std::stoi(info.at(1)),
                                   std::stoi(info.at(2)),
                                   std::stoi(info.at(3)),
                                   std::stoi(info.at(4)),
                                   info.at(5),
                                   true
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
