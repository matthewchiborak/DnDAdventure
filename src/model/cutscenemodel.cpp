#include "cutscenemodel.h"

#include "../filemanagment/fileReader.h"
#include "../display/drawinformation.h"

CutsceneModel::CutsceneModel()
{

}

void CutsceneModel::clear()
{
    nextBoardFilePath = "None";
    nextEnouncter = "None";
    currentBackground = "";
    currentLeft = "";
    currentRight = "";
    currentLeftName = "";
    currentRightName = "";
    currentlyLeftTalking = true;
    currentlyHasText = true;
    currentText = "";

    while(!instructions.empty())
        instructions.pop();
}

void CutsceneModel::load(std::string loadInfo)
{
    clear();

    FileReader fr("D:\\Qt Projects\\DnDAdventure\\src\\test\\Cutscenes\\" + loadInfo);

    nextBoardFilePath = "None";
    nextEnouncter = "None";

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
    DrawInformation lp(-600, -175, 500, 500, currentLeft, false);
    items->push_back(lp);

    //Right port
    DrawInformation rp(200, -175, 500, 500, currentRight, false);
    rp.flip = true;
    items->push_back(rp);

    if(!currentlyHasText)
        return;

    //Text Box
    DrawInformation textBox(-700, -375, 1500, 200, "BattleMenuBG", false);
    items->push_back(textBox);

    //Name
    if(currentlyLeftTalking)
    {
        DrawInformation name(50, 670, 300, 100, "", false, currentLeftName, true, 36.f);
        items->push_back(name);
    }
    else
    {
        DrawInformation name(1400, 670, 300, 100, "", false, currentRightName, true, 36.f);
        items->push_back(name);
    }

    //Text
    DrawInformation dialog(50, 730, 1500, 140, "", false, currentText, true, 24.f);
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
        if(focus.at(0) == "NextEncounter")
            nextEnouncter = focus.at(1);
        if(focus.at(0) == "Stop")
            foundAStop = true;
        if(focus.at(0) == "BG")
            currentBackground = focus.at(1);
        if(focus.at(0) == "LeftPortrait")
            currentLeft = focus.at(1);
        if(focus.at(0) == "RightPortrait")
            currentRight = focus.at(1);
        if(focus.at(0) == "LeftName")
            currentLeftName = FileReader::replaceCharacter(focus.at(1), '_', ' ');
        if(focus.at(0) == "RightName")
            currentRightName = FileReader::replaceCharacter(focus.at(1), '_', ' ');
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

std::string CutsceneModel::getNextEncounter()
{
    return nextEnouncter;
}

void CutsceneModel::setMusicController(MusicControllerAbstract *musicController)
{
    this->musicController = musicController;
}
