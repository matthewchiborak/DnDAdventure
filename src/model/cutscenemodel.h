#ifndef CUTSCENEMODEL_H
#define CUTSCENEMODEL_H

#include <queue>
#include <string>

class DrawInformation;

class CutsceneModel
{
public:
    CutsceneModel();

    void load(std::string loadInfo);
    void draw(std::vector<DrawInformation> * items);

    void advance();
    bool isDone();

    std::string getNextBoardFilePath();
    int getXPosBoard();
    int getYPosBoard();

private:
    std::queue<std::string> instructions;

    std::string nextBoardFilePath;
    int xPosBoard;
    int yPosBoard;

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
