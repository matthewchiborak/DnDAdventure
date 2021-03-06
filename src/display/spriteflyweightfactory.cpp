#include "spriteflyweightfactory.h"

#include "spriteflyweight.h"

#include <QDebug>
#include <QDir>

SpriteFlyweightFactory::SpriteFlyweightFactory(std::string spriteListFilepath)
    : SpriteFlyweightFactoryAbstract(spriteListFilepath)
{

}

SpriteFlyweight *SpriteFlyweightFactory::getFlyweight(std::string key)
{
    if (spriteFlyweights.find(key) == spriteFlyweights.end())
    {
        //Time to create the sprite
        return createFlyweight(key);
    }

    //If got to here it exists in the map
    return spriteFlyweights[key];
}

SpriteFlyweight *SpriteFlyweightFactory::createFlyweight(std::string key)
{
    QDir dir(QDir::current());
    dir.cdUp();
    //Get the image location from the other map, create and store the flyweight
    std::string spriteFilePath = dir.path().toStdString()+ "/DnDAdventure/src/test/sprites/" + keyToImageLocationMap[key];

    //Create it. Return it.
    SpriteFlyweight * newSpr = new SpriteFlyweight(spriteFilePath);
    spriteFlyweights.insert(std::pair<std::string,SpriteFlyweight*>(key, newSpr));

    return newSpr;
}
