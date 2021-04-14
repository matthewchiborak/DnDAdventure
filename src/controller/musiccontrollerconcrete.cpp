#include "musiccontrollerconcrete.h"

#include <QDir>

MusicControllerConcrete::MusicControllerConcrete(std::string musicFilepath)
    : MusicControllerAbstract(musicFilepath)
{
    //Auto load se that will be used alot like hit, miss, advancetext
    /*
    QMediaPlayer backgroundMusic;
    QMediaPlayer hitSE;
    QMediaPlayer missSE;
    QMediaPlayer advanceTextSE;
    QMediaPlayer miscSE;*/
}

void MusicControllerConcrete::playMusic(std::string key)
{
    if(key == lastBGMusicKey)
        return;

    lastBGMusicKey = key;

    QDir dir(QDir::current());
    dir.cdUp();
    std::string theFilePath = "file:///" + dir.path().toStdString()+ "/DnDAdventure/src/test/Music/" + keyToFilepaths.at(key);

    //backgroundMusic.setMedia(QUrl("file:///D:/Qt Projects/DnDAdventure/src/test/Music/FF6BattleTheme.wav"));
    backgroundMusic.setMedia(QUrl(QString::fromStdString(theFilePath)));
    if(backgroundMusic.state() == QMediaPlayer::PlayingState)
    {
        backgroundMusic.setPosition(0);
    }
    else if(backgroundMusic.state() == QMediaPlayer::StoppedState)
        backgroundMusic.play();
}

void MusicControllerConcrete::playSoundEffect(std::string key)
{
    if(key == "Hit")
        hitSE.play();
    else if(key == "Miss")
        missSE.play();
   // else if(key == "AdvanceText")
     //   advanceTextSE.play();
    else
    {
        QDir dir(QDir::current());
        dir.cdUp();
        std::string theFilePath = "file:///" + dir.path().toStdString()+ "/DnDAdventure/src/test/Music/" + keyToFilepaths.at(key);

        miscSE.setMedia(QUrl(QString::fromStdString(theFilePath)));
        if(miscSE.state() == QMediaPlayer::PlayingState)
        {
            miscSE.setPosition(0);
        }
        else if(miscSE.state() == QMediaPlayer::StoppedState)
            miscSE.play();
    }
}

void MusicControllerConcrete::manualLoad(std::string typeKey, std::string soundKey)
{
    QDir dir(QDir::current());
    dir.cdUp();
    std::string theFilePath = "file:///" + dir.path().toStdString()+ "/DnDAdventure/src/test/Music/" + keyToFilepaths.at(soundKey);

    if(typeKey == "Hit")
        hitSE.setMedia(QUrl(QString::fromStdString(theFilePath)));
    else if(typeKey == "Miss")
        missSE.setMedia(QUrl(QString::fromStdString(theFilePath)));
    //else if(typeKey == "AdvanceText")
    //  advanceTextSE.setMedia(QUrl(QString::fromStdString(theFilePath)));
}

void MusicControllerConcrete::loopMusic(int resetPos, int loopPoint)
{
    if(backgroundMusic.state() == QMediaPlayer::PlayingState)
    {
        if(backgroundMusic.position() >= loopPoint)
            backgroundMusic.setPosition(resetPos);
    }
    if(backgroundMusic.state() == QMediaPlayer::StoppedState)
    {
        backgroundMusic.setPosition(resetPos);
        backgroundMusic.play();
    }
}
