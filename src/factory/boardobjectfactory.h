#ifndef BOARDOBJECTFACTORY_H
#define BOARDOBJECTFACTORY_H

#include <iostream>

#include "worldobjectfactoryabstract.h"

class BoardObjectAbstract;

class BoardObjectFactory : public WorldObjectFactoryAbstract
{
public:
    BoardObjectFactory();

    void populate(std::vector<BoardObjectAbstract*> * boardObjects, int * xPos, int * yPos, std::string boardFileName);

private:
    BoardObjectAbstract * createObstacle(std::vector<std::string> info);
    BoardObjectAbstract * createMap(std::vector<std::string> info);
    BoardObjectAbstract * createNPC(std::vector<std::string> info);
    //Create other
};

#endif // BOARDOBJECTFACTORY_H
