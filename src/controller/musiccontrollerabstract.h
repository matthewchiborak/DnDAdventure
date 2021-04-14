#ifndef MUSICCONTROLLERABSTRACT_H
#define MUSICCONTROLLERABSTRACT_H

#include <string>
#include <map>

class MusicControllerAbstract
{
public:
    MusicControllerAbstract(std::string musicFilepath);

    virtual void playMusic(std::string key);
    virtual void playSoundEffect(std::string key);
    virtual void manualLoad(std::string typeKey, std::string soundKey);
    virtual void loopMusic(int resetPos, int loopPoint);

protected:
    std::string musicFilepath;
    std::map<std::string, std::string> keyToFilepaths;
};

#endif // MUSICCONTROLLERABSTRACT_H
