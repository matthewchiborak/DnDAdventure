#include "keyinputstateboard.h"

#pragma comment(lib, "User32.lib")

#include <Windows.h>

#include <queue>
#include <QDebug>

#include "../model/modelabstract.h"
#include "../filemanagment/fileReader.h"

KeyInputStateBoard::KeyInputStateBoard(ModelAbstract *model, std::queue<int> *keyboardEventQueue, std::vector<bool> *movementKeys)
    : KeyInputState(model, keyboardEventQueue, movementKeys)
{
    movementLockTimeMil = 300;

    lockMovement[0] = false;
    lockMovement[1] = false;
    lockMovement[2] = false;
    lockMovement[3] = false;

    model->specialMessage("PlayMusic", "Board");
}

bool KeyInputStateBoard::handle(std::string *nextState)
{
    if(handleUserInput(nextState))
        return true;

    if(handleMovement(nextState))
        return true;

    //Else handle other possible events
    //Doorways
    if(handleCollisionTriggers(nextState))
        return true;

    //Random encounters
    return false;
}

bool KeyInputStateBoard::handleUserInput(std::string *nextState)
{
    if(movementEventSetUp)
        return false;

    if(!eventBeenSetUp)
    {
        if(keyboardEventQueue->empty())
            return false;

        keyToHandle = keyboardEventQueue->front();

        if(model->hasBoardDialogRemaining())
        {
            if(keyToHandle == Qt::Key_E)
            {
                auto nowTime = std::chrono::system_clock::now().time_since_epoch();
                auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime).count();
                theTimeNow = (millis);
                timeOfLastButtonEvent = theTimeNow;
                eventBeenSetUp = true;

                model->getNextBoardDialog();
            }

            return false;
        }

        if(keyToHandle == Qt::Key_E
                || keyToHandle == Qt::Key_Escape
                )
        {
            auto nowTime = std::chrono::system_clock::now().time_since_epoch();
            auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime).count();
            theTimeNow = (millis);
            timeOfLastButtonEvent = theTimeNow;
            eventBeenSetUp = true;

            if(keyToHandle == Qt::Key_E)
            {
                //Interact and update inventory based on resoponse
                std::string holdRes = this->model->interact();
                model->updateInventoryBasedOnString(holdRes);
                if(holdRes.length() > 3)
                {
                    if(holdRes.at(0) == 'S'
                            && holdRes.at(1) == 'h'
                            && holdRes.at(2) == 'o'
                            && holdRes.at(3) == 'p'
                            )
                    {
                        eventBeenSetUp = false;
                        while(!keyboardEventQueue->empty())
                            keyboardEventQueue->pop();
                        model->loadShop(holdRes);
                        (*nextState) = "Shop";
                        return true;
                    }
                }
            }
        }

        return false;
    }

    //Prcoess the event
    auto nowTime = std::chrono::system_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime).count();
    theTimeNow =(millis);
    elapsed_millies = theTimeNow - timeOfLastButtonEvent;

//    if(keyToHandle == Qt::Key_W)
//        this->model->movePlayer(0, 1, ((elapsed_millies/movementLockTimeMil)));
//    else if(keyToHandle == Qt::Key_S)
//        this->model->movePlayer(0, -1, ((elapsed_millies/movementLockTimeMil)));
//    else if(keyToHandle == Qt::Key_A)
//        this->model->movePlayer(-1, 0, ((elapsed_millies/movementLockTimeMil)));
//    else if(keyToHandle == Qt::Key_D)
//        this->model->movePlayer(1, 0, ((elapsed_millies/movementLockTimeMil)));
    //else
    if(keyToHandle == Qt::Key_Escape)
    {
        eventBeenSetUp = false;
        while(!keyboardEventQueue->empty())
            keyboardEventQueue->pop();
        (*nextState) = "PauseMenu";
        return true;
    }

    if((elapsed_millies / movementLockTimeMil) >= 1 && eventBeenSetUp)
    {
        eventBeenSetUp = false;
        while(!keyboardEventQueue->empty())
            keyboardEventQueue->pop();

//        if(keyToHandle == Qt::Key_W || keyToHandle == Qt::Key_S || keyToHandle == Qt::Key_A || keyToHandle == Qt::Key_D)
//        {
//            //Hey guess what. try to trigger a random enounter
//            if(model->tryToStartABattle())
//            {
//                (*nextState) = "RandomEncounter";
//                return true;
//            }
//        }
    }

    return false;
}

bool KeyInputStateBoard::handleMovement(std::string *nextState)
{
    if(eventBeenSetUp)
        return false;

    if(model->hasBoardDialogRemaining())
        return false;

    if(!movementEventSetUp)
    {
        if(GetAsyncKeyState('W') & 0x8000)
            lockMovement[0] = true;
        else if(GetAsyncKeyState('A') & 0x8000)
            lockMovement[1] = true;
        else if(GetAsyncKeyState('S') & 0x8000)
            lockMovement[2] = true;
        else if(GetAsyncKeyState('D') & 0x8000)
            lockMovement[3] = true;

        if(lockMovement[0] || lockMovement[1] || lockMovement[2] || lockMovement[3])
        {
            auto nowTime = std::chrono::system_clock::now().time_since_epoch();
            auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime).count();
            theTimeNow = (millis);
            timeOfLastButtonEvent = theTimeNow;
            movementEventSetUp = true;
        }

        return false;
    }

    //Prcoess the event
    auto nowTime = std::chrono::system_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime).count();
    theTimeNow =(millis);
    elapsed_millies = theTimeNow - timeOfLastButtonEvent;

    if(lockMovement[0])
        this->model->movePlayer(0, 1, ((elapsed_millies/movementLockTimeMil)));
    else if(lockMovement[2])
        this->model->movePlayer(0, -1, ((elapsed_millies/movementLockTimeMil)));
    else if(lockMovement[1])
        this->model->movePlayer(-1, 0, ((elapsed_millies/movementLockTimeMil)));
    else if(lockMovement[3])
        this->model->movePlayer(1, 0, ((elapsed_millies/movementLockTimeMil)));

    if((elapsed_millies / movementLockTimeMil) >= 1 && movementEventSetUp)
    {
        lockMovement[0] = false;
        lockMovement[1] = false;
        lockMovement[2] = false;
        lockMovement[3] = false;

        movementEventSetUp = false;

        //Hey guess what. try to trigger a random enounter
        if(model->tryToStartABattle())
        {
            (*nextState) = "RandomEncounter";
            return true;
        }
    }

    return false;
}

bool KeyInputStateBoard::handleCollisionTriggers(std::string *nextState)
{
    //For doors
    std::string res = model->handleBoardCollisionTriggers();

    //for cutscene triggers
    std::string cutsceneoption = model->standOnInteract();

    if(cutsceneoption == "None")
        return false;

    std::vector<std::string> cutsceneInfo = FileReader::splitString(cutsceneoption, '$');

    if(cutsceneInfo.at(0) == "Cutscene")
    {
        //Tell model to load cutscene
        (*nextState) = "Cutscene";

        //Load cutscene
        model->loadCutscene(cutsceneInfo.at(1));

        return true;
    }

    return false;
}
