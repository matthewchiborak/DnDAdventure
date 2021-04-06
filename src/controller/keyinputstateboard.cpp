#include "keyinputstateboard.h"

#include <queue>
#include <QDebug>

#include "../model/modelabstract.h"

KeyInputStateBoard::KeyInputStateBoard(ModelAbstract *model, std::queue<int> *keyboardEventQueue)
    : KeyInputState(model, keyboardEventQueue)
{
    movementLockTimeMil = 300;
    keepIncrLoop = false;
    eventBeenSetUp = false;
}

bool KeyInputStateBoard::handle(std::string *nextState)
{
    if(!eventBeenSetUp)
    {
        if(keyboardEventQueue->empty())
            return false;

        keyToHandle = keyboardEventQueue->front();

        if(keyToHandle == Qt::Key_W
                || keyToHandle == Qt::Key_S
                || keyToHandle == Qt::Key_A
                || keyToHandle == Qt::Key_D
                )
        {
            auto nowTime = std::chrono::system_clock::now().time_since_epoch();
            auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime).count();
            theTimeNow = (millis);
            timeOfLastButtonEvent = theTimeNow;
            eventBeenSetUp = true;
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

    if((elapsed_millies / movementLockTimeMil) >= 1)
    {
        //keyboardEventQueue->pop();
        eventBeenSetUp = false;
    }

    return false;

}
