#ifndef SPRITEFLYWEIGHTFACTORY_H
#define SPRITEFLYWEIGHTFACTORY_H

#include "spriteflyweightfactoryabstract.h"

class SpriteFlyweightFactory : public SpriteFlyweightFactoryAbstract
{
public:
    SpriteFlyweightFactory(std::string spriteListFilepath);

    SpriteFlyweight* getFlyweight(std::string key);

protected:
    SpriteFlyweight* createFlyweight(std::string key);
};

#endif // SPRITEFLYWEIGHTFACTORY_H
