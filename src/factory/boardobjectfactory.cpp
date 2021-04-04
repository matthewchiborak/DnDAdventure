#include "boardobjectfactory.h"

#include <sstream>

#include "../filemanagment/fileReader.h"
#include "../model/boardobjectobstacle.h"

BoardObjectFactory::BoardObjectFactory()
{

}

void BoardObjectFactory::populate(std::vector<BoardObjectAbstract *> *boardObjects, std::string boardFileName)
{
    FileReader reader(boardFileName);

    while(reader.hasNext())
    {
        std::vector<std::string> vect = reader.splitString(reader.next(), ',');

        if(vect.size() > 0)
        {
            if(vect.at(0) == "obs")
                boardObjects->push_back(createObstacle(vect));
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
                                   info.at(5)
                                   );
}
