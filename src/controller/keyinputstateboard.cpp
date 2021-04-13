#include "keyinputstateboard.h"

#include <queue>
#include <QDebug>

#include "../model/modelabstract.h"

KeyInputStateBoard::KeyInputStateBoard(ModelAbstract *model, std::queue<int> *keyboardEventQueue)
    : KeyInputState(model, keyboardEventQueue)
{
    movementLockTimeMil = 300;
}

bool KeyInputStateBoard::handle(std::string *nextState)
{
    if(handleUserInput(nextState))
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

        if(keyToHandle == Qt::Key_W
                || keyToHandle == Qt::Key_S
                || keyToHandle == Qt::Key_A
                || keyToHandle == Qt::Key_D
                || keyToHandle == Qt::Key_E
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
                model->updateInventoryBasedOnString(this->model->interact());
            }
        }

        return false;
    }

    //Prcoess the event
    auto nowTime = std::chrono::system_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime).count();
    theTimeNow =(millis);
    elapsed_millies = theTimeNow - timeOfLastButtonEvent;

    if(keyToHandle == Qt::Key_W)
        this->model->movePlayer(0, 1, ((elapsed_millies/movementLockTimeMil)));
    else if(keyToHandle == Qt::Key_S)
        this->model->movePlayer(0, -1, ((elapsed_millies/movementLockTimeMil)));
    else if(keyToHandle == Qt::Key_A)
        this->model->movePlayer(-1, 0, ((elapsed_millies/movementLockTimeMil)));
    else if(keyToHandle == Qt::Key_D)
        this->model->movePlayer(1, 0, ((elapsed_millies/movementLockTimeMil)));
    else if(keyToHandle == Qt::Key_Escape)
    {
        eventBeenSetUp = false;
        while(!keyboardEventQueue->empty())
            keyboardEventQueue->pop();
        (*nextState) = "PauseMenu";
        return true;
    }

    if((elapsed_millies / movementLockTimeMil) >= 1)
    {
        eventBeenSetUp = false;
        while(!keyboardEventQueue->empty())
            keyboardEventQueue->pop();

        if(keyToHandle == Qt::Key_W || keyToHandle == Qt::Key_S || keyToHandle == Qt::Key_A || keyToHandle == Qt::Key_D)
        {
            //Hey guess what. try to trigger a random enounter
            if(model->tryToStartABattle())
            {
                (*nextState) = "RandomEncounter";
                return true;
            }
        }
    }

    return false;
}

bool KeyInputStateBoard::handleCollisionTriggers(std::string *nextState)
{
    std::string res = model->handleBoardCollisionTriggers();
    if(res == "HUH")
        return false;

    return false;
}
