#include "spriteflyweightfactoryabstract.h"

#include "../filemanagment/fileReader.h"

SpriteFlyweightFactoryAbstract::SpriteFlyweightFactoryAbstract(std::string spriteListFilepath)
{
    this->spriteListFilepath = spriteListFilepath;

    FileReader fr(spriteListFilepath);

    while(fr.hasNext())
    {
        std::vector<std::string> split = fr.splitString(fr.next(), ',');

        keyToImageLocationMap.insert(std::pair<std::string,std::string>(split.at(0), split.at(1)));
    }
}

SpriteFlyweight *SpriteFlyweightFactoryAbstract::getFlyweight(std::string key)
{
    return nullptr;
}

SpriteFlyweight *SpriteFlyweightFactoryAbstract::createFlyweight(std::string key)
{
    return nullptr;
}
