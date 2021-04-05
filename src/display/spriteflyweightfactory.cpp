#include "spriteflyweightfactory.h"

#include <QDebug>

SpriteFlyweightFactory::SpriteFlyweightFactory(std::string spriteListFilepath)
    : SpriteFlyweightFactoryAbstract(spriteListFilepath)
{

}

SpriteFlyweight *SpriteFlyweightFactory::getFlyweight(std::string key)
{
    qDebug() << QString::fromStdString(key) << " was requested";

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
    //Get the image location from the other map, create and store the flyweight
    std::string spriteFilePath = keyToImageLocationMap[key];

    //Create it. Return it.
    return nullptr;
}
