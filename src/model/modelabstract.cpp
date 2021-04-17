#include "modelabstract.h"

#include "../filemanagment/fileReader.h"


#include "../model/monstermanualentry.h"

#include <vector>

ModelAbstract::ModelAbstract(MusicControllerAbstract *musicController)
{

}

ModelAbstract::~ModelAbstract()
{
    for(int i = 0; i < playerCharacters.size(); i++)
    {
        delete playerCharacters.at(i);
    }
    for(int i = 0; i < equipment.size(); i++)
    {
        delete equipment.at(i);
    }
}

void ModelAbstract::addPlayerCharacter(PlayerCharacterStats *character)
{
    playerCharacters.push_back(character);
}


void ModelAbstract::drawBoardModel(std::vector<DrawInformation> * items, float *xOffset, float *yOffset)
{

}
void ModelAbstract::loadBoardModel(std::string loadInfo)
{

}

std::string ModelAbstract::handleBoardCollisionTriggers()
{
    return "None";
}

void ModelAbstract::movePlayer(int x, int y, float t)
{

}

void ModelAbstract::drawPauseMenu(std::vector<DrawInformation> *items)
{

}

void ModelAbstract::moveMenuCursor(int x, int y, std::string key)
{

}

void ModelAbstract::enterMenu(std::string key)
{

}

void ModelAbstract::closeMenu(std::string key)
{

}

bool ModelAbstract::tryToStartABattle()
{
    return false;
}

void ModelAbstract::drawBattleModel(std::vector<DrawInformation> *items)
{

}

void ModelAbstract::passTime(float value)
{

}

bool ModelAbstract::isBattleDone()
{
    return true;
}

bool ModelAbstract::isGameOver()
{
    return false;
}

void ModelAbstract::qrPressed(bool wasQ)
{

}

void ModelAbstract::specialMessage(std::string message, std::string key)
{

}

void ModelAbstract::addEquipment(std::string info)
{
    EquipmentModel * temp = new EquipmentModel(info, equipment.size());
    equipment.push_back(temp);
}

std::vector<EquipmentModel*> *ModelAbstract::getEquipment()
{
    return &equipment;
}

bool ModelAbstract::getPauseIsDone()
{
    return pauseIsDone;
}

void ModelAbstract::setPauseIsDone(bool value)
{
    pauseIsDone = value;
}

int ModelAbstract::getNumberOfPotions()
{
    return numberOfPotions;
}

void ModelAbstract::setNumberOfPotions(int value)
{
    numberOfPotions = value;
}

void ModelAbstract::changePotionAmount(int amount)
{
    numberOfPotions += amount;

    if(numberOfPotions < 0)
        numberOfPotions = 0;
}

int ModelAbstract::getNumberOfRemedies()
{
    return numberOfRemedies;
}

void ModelAbstract::setNumberOfRemedies(int value)
{
    numberOfRemedies = value;
}

void ModelAbstract::changeRemedyAmount(int amount)
{
    numberOfRemedies += amount;

    if(numberOfRemedies < 0)
        numberOfRemedies = 0;
}

int ModelAbstract::getGold()
{
    return gold;
}

void ModelAbstract::changeGold(int amount)
{
    gold += amount;

    if(gold < 0)
        gold = 0;
}

void ModelAbstract::setGold(int value)
{
    gold = value;
}

int ModelAbstract::getNumberOfEthers()
{
    return numberOfEthers;
}

int ModelAbstract::getNumberOfJars()
{
    return numberOfPickleJars;
}

void ModelAbstract::setNumberOfEthers(int value)
{
    numberOfEthers = value;
}

void ModelAbstract::setNumberofJars(int value)
{
    numberOfPickleJars = value;
}

void ModelAbstract::changeEtherAmount(int amount)
{
    numberOfEthers += amount;

    if(numberOfEthers < 0)
        numberOfEthers = 0;
}

void ModelAbstract::changeJarAmount(int amount)
{
    numberOfPickleJars += amount;

    if(numberOfPickleJars < 0)
        numberOfPickleJars = 0;
}

void ModelAbstract::loadMonsterManual(std::string filepath)
{
    FileReader fr(filepath);

    while(fr.hasNext())
    {
        std::vector<std::string> spt = fr.splitString(fr.next(), ',');
        MonsterManualEntry en(spt.at(0), spt.at(1));
        monsterManual.push_back(en);
    }
}

std::vector<MonsterManualEntry> *ModelAbstract::getMonsterManual()
{
    return &monsterManual;
}

std::string ModelAbstract::interact()
{
    return "None";
}

std::string ModelAbstract::standOnInteract()
{
    return "None";
}

void ModelAbstract::updateInventoryBasedOnString(std::string message)
{
    if(message == "None")
        return;

    std::vector<std::string> cutMessage = FileReader::splitString(message, '$');

    if(cutMessage.at(0) == "Chest")
    {
        if(cutMessage.at(1) == "gold")
        {
            boardModelDialog.push("Found " + cutMessage.at(2) + " gold!");
            this->gold += std::stoi(cutMessage.at(2));
            return;
        }

        if(cutMessage.at(1) == "potion")
        {
            if(std::stoi(cutMessage.at(2)) > 1)
                boardModelDialog.push("Found " + cutMessage.at(2) + " potions!");
            else
                boardModelDialog.push("Found " + cutMessage.at(2) + " potion!");
            this->numberOfPotions += std::stoi(cutMessage.at(2));
            return;
        }
        if(cutMessage.at(1) == "ether")
        {
            if(std::stoi(cutMessage.at(2)) > 1)
                boardModelDialog.push("Found " + cutMessage.at(2) + " ethers!");
            else
                boardModelDialog.push("Found " + cutMessage.at(2) + " ether!");
            this->numberOfEthers += std::stoi(cutMessage.at(2));
            return;
        }
        if(cutMessage.at(1) == "remedy")
        {
            if(std::stoi(cutMessage.at(2)) > 1)
                boardModelDialog.push("Found " + cutMessage.at(2) + " remedies!");
            else
                boardModelDialog.push("Found " + cutMessage.at(2) + " remedy!");
            this->numberOfRemedies += std::stoi(cutMessage.at(2));
            return;
        }
        if(cutMessage.at(1) == "jar")
        {
            if(std::stoi(cutMessage.at(2)) > 1)
                boardModelDialog.push("Found " + cutMessage.at(2) + " jars of pickles!");
            else
                boardModelDialog.push("Found " + cutMessage.at(2) + " jar of pickles!");
            this->numberOfPickleJars += std::stoi(cutMessage.at(2));
            return;
        }

        if(cutMessage.at(1) == "equipment")
        {
            boardModelDialog.push("Found " + FileReader::replaceCharacter(cutMessage.at(4), '_', ' ') + "!");
            addEquipment(
                        cutMessage.at(2) + "," +
                        cutMessage.at(3) + "," +
                        cutMessage.at(4) + "," +
                        cutMessage.at(5) + "," +
                        cutMessage.at(6) + "," +
                        cutMessage.at(7)
                        );
            return;
        }
    }

    if(cutMessage.at(0) == "NPC")
    {
        for(int i = 1; i < cutMessage.size(); i++)
        {
            boardModelDialog.push(FileReader::replaceCharacter(cutMessage.at(i), '_', ' '));
        }

        return;
    }

    if(cutMessage.at(0) == "Save" || message == "Save")
    {
        saveGame();
        return;
    }
}

bool ModelAbstract::hasBoardDialogRemaining()
{
    return !boardModelDialog.empty();
}

std::string ModelAbstract::getNextBoardDialog()
{
    std::string toRet = boardModelDialog.front();
    boardModelDialog.pop();
    return toRet;
}

void ModelAbstract::loadCutscene(std::string filepath)
{

}

void ModelAbstract::drawCutscene(std::vector<DrawInformation> *items)
{

}

bool ModelAbstract::cutsceneIsDone()
{
    return true;
}

bool ModelAbstract::loadBoardBasedOnLoadedCutscene()
{
    return false;
}

void ModelAbstract::loadSaveGame()
{

}

bool ModelAbstract::doIStartANewGame()
{
    return true;
}

void ModelAbstract::drawTitleScreen(std::vector<DrawInformation> *items)
{

}

std::string ModelAbstract::getCutsceneToPlayAfterBattle()
{
    return "None";
}

void ModelAbstract::saveGame()
{

}




