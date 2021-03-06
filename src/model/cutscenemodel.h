#ifndef CUTSCENEMODEL_H
#define CUTSCENEMODEL_H

#include <queue>
#include <string>

#include "../controller/musiccontrollerabstract.h"

class DrawInformation;

class CutsceneModel
{
public:
    CutsceneModel();

    void clear();
    void load(std::string loadInfo);
    void draw(std::vector<DrawInformation> * items);

    void advance();
    bool isDone();

    std::string getNextBoardFilePath();
    int getXPosBoard();
    int getYPosBoard();
    std::string getNextEncounter();

    void setMusicController(MusicControllerAbstract * musicController);

private:
    std::queue<std::string> instructions;

    MusicControllerAbstract * musicController;

    std::string nextBoardFilePath = "None";
    int xPosBoard;
    int yPosBoard;

    std::string nextEnouncter = "None";

    std::string currentBackground = "";
    std::string currentLeft = "";
    std::string currentRight = "";
    std::string currentLeftName = "";
    std::string currentRightName = "";
    bool currentlyLeftTalking = true;
    bool currentlyHasText = true;
    std::string currentText = "";
};

#endif // CUTSCENEMODEL_H
