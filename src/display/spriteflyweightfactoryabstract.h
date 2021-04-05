#ifndef SPRITEFLYWEIGHTFACTORYABSTRACT_H
#define SPRITEFLYWEIGHTFACTORYABSTRACT_H

#include <iostream>
#include <vector>
#include <map>

#include "spriteflyweight.h"


class SpriteFlyweightFactoryAbstract
{
public:
    SpriteFlyweightFactoryAbstract(std::string spriteListFilepath);

    //function to reimplement in derived class on choosing how to get
    //the sprites
    virtual SpriteFlyweight* getFlyweight(std::string key);

protected:
    std::string spriteListFilepath;

    //list of sprites
    std::map<std::string, SpriteFlyweight*> spriteFlyweights;
    std::map<std::string, std::string> keyToImageLocationMap;

    virtual SpriteFlyweight* createFlyweight(std::string key);
};

#endif // SPRITEFLYWEIGHTFACTORYABSTRACT_H
