#ifndef BOARDOBJECTFACTORY_H
#define BOARDOBJECTFACTORY_H

#include <iostream>

#include "worldobjectfactoryabstract.h"

class BoardObjectAbstract;

class BoardObjectFactory : public WorldObjectFactoryAbstract
{
public:
    BoardObjectFactory();

    void populate(std::vector<BoardObjectAbstract*> * boardObjects, std::string boardFileName);

private:
    BoardObjectAbstract * createObstacle(std::vector<std::string> info);
};

#endif // BOARDOBJECTFACTORY_H
