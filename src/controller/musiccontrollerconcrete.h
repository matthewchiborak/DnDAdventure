#ifndef MUSICCONTROLLERCONCRETE_H
#define MUSICCONTROLLERCONCRETE_H

#include "musiccontrollerabstract.h"
#include <QMediaPlayer>

class MusicControllerConcrete : public MusicControllerAbstract
{
public:
    MusicControllerConcrete(std::string musicFilepath);

    void playMusic(std::string key);
    void playSoundEffect(std::string key);

    void manualLoad(std::string typeKey, std::string soundKey);
    void loopMusic(int resetPos, int loopPoint);

private:
    std::string lastBGMusicKey = "None";
    QMediaPlayer backgroundMusic;
    QMediaPlayer hitSE;
    QMediaPlayer missSE;
    QMediaPlayer thudSE;
    //QMediaPlayer advanceTextSE;
    QMediaPlayer miscSE;
};

#endif // MUSICCONTROLLERCONCRETE_H
