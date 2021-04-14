#include "cutscenemodel.h"

#include "../filemanagment/fileReader.h"
#include "../display/drawinformation.h"

CutsceneModel::CutsceneModel()
{

}

void CutsceneModel::load(std::string loadInfo)
{
    FileReader fr("D:\\Qt Projects\\DnDAdventure\\src\\test\\Cutscenes\\" + loadInfo);

    while(fr.hasNext())
    {
        instructions.push(fr.next());
    }

    //Call advance once to inital set up
    advance();
}

void CutsceneModel::draw(std::vector<DrawInformation> *items)
{
    //Background
    DrawInformation bg(-800, -400, 1700, 900, currentBackground, false);
    items->push_back(bg);

    //Left port
    DrawInformation lp(-600, -150, 500, 500, currentLeft, false);
    items->push_back(lp);

    //Right port
    DrawInformation rp(200, -150, 500, 500, currentRight, false);
    items->push_back(rp);

    if(!currentlyHasText)
        return;

    //Text Box
    DrawInformation textBox(-700, -375, 1500, 200, "BattleMenuBG", false);
    items->push_back(textBox);

    //Name
    if(currentlyLeftTalking)
    {
        DrawInformation name(50, 670, 200, 100, "", false, currentLeftName, true);
        items->push_back(name);
    }
    else
    {
        DrawInformation name(1400, 670, 200, 100, "", false, currentRightName, true);
        items->push_back(name);
    }

    //Text
    DrawInformation dialog(50, 730, 1500, 140, "", false, currentText, true);
    items->push_back(dialog);
}

void CutsceneModel::advance()
{
    bool foundAStop = false;

    do{
        std::vector<std::string> focus = FileReader::splitString(instructions.front(), ',');

        if(focus.at(0) == "NextBoardPath")
            nextBoardFilePath = focus.at(1);
        if(focus.at(0) == "NextBoardX")
            xPosBoard = std::stoi(focus.at(1));
        if(focus.at(0) == "NextBoardY")
            yPosBoard = std::stoi(focus.at(1));
        if(focus.at(0) == "Stop")
            foundAStop = true;
        if(focus.at(0) == "BG")
            currentBackground = focus.at(1);
        if(focus.at(0) == "LeftPortrait")
            currentLeft = focus.at(1);
        if(focus.at(0) == "RightPortrait")
            currentRight = focus.at(1);
        if(focus.at(0) == "LeftName")
            currentLeftName = focus.at(1);
        if(focus.at(0) == "RightName")
            currentRightName = focus.at(1);
        if(focus.at(0) == "LeftTalk")
            currentlyLeftTalking = std::stoi(focus.at(1));
        if(focus.at(0) == "HasText")
            currentlyHasText = std::stoi(focus.at(1));
        if(focus.at(0) == "Text")
            currentText = FileReader::replaceCharacter(focus.at(1), '_', ' ');
        if(focus.at(0) == "BGMusic")
            musicController->playMusic(focus.at(1));


        instructions.pop();
    }while(!foundAStop);
}

bool CutsceneModel::isDone()
{
    return instructions.empty();
}

std::string CutsceneModel::getNextBoardFilePath()
{
    return nextBoardFilePath;
}

int CutsceneModel::getXPosBoard()
{
    return xPosBoard;
}

int CutsceneModel::getYPosBoard()
{
    return yPosBoard;
}

void CutsceneModel::setMusicController(MusicControllerAbstract *musicController)
{
    this->musicController = musicController;
}