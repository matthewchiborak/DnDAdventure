#ifndef WORLDOBJECTFACTORYABSTRACT_H
#define WORLDOBJECTFACTORYABSTRACT_H

#include <vector>
#include <iostream>

class BoardObjectAbstract;

class WorldObjectFactoryAbstract
{
public:
    WorldObjectFactoryAbstract();

    void populate(std::vector<BoardObjectAbstract*> * boardObjects, std::string boardFileName);
};

#endif // WORLDOBJECTFACTORYABSTRACT_H
