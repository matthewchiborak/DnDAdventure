#include "musiccontrollerabstract.h"

#include "../filemanagment/fileReader.h"

MusicControllerAbstract::MusicControllerAbstract(std::string musicFilepath)
{
    this->musicFilepath = musicFilepath;

    FileReader fr(musicFilepath);

    std::string spaceString = " ";

    while(fr.hasNext())
    {
        std::vector<std::string> split = fr.splitString(fr.next(), ',');

        //So apparently maps cant have spaces which is why ive been getting errors.
        keyToFilepaths.insert(std::pair<std::string,std::string>(split.at(0), split.at(1)));
    }
}

void MusicControllerAbstract::playMusic(std::string key)
{

}

void MusicControllerAbstract::playSoundEffect(std::string key)
{

}

void MusicControllerAbstract::manualLoad(std::string typeKey, std::string soundKey)
{

}

void MusicControllerAbstract::loopMusic(int resetPos, int loopPoint)
{

}
