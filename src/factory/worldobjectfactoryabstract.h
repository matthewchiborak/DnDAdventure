#ifndef WORLDOBJECTFACTORYABSTRACT_H
#define WORLDOBJECTFACTORYABSTRACT_H

#include <vector>
#include <iostream>

class BoardObjectAbstract;
class Doorway;

class WorldObjectFactoryAbstract
{
public:
    WorldObjectFactoryAbstract();

    virtual void populate(std::vector<BoardObjectAbstract*> * boardObjects, std::string boardFileName);
};

#endif // WORLDOBJECTFACTORYABSTRACT_H
