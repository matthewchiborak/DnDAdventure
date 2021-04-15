#include "keyinputstatebattle.h"

#include "../model/modelabstract.h"
#include <QDebug>

KeyInputStateBattle::KeyInputStateBattle(ModelAbstract *model, std::queue<int> *keyboardEventQueue, std::vector<bool> *movementKeys)
    : KeyInputState(model, keyboardEventQueue, movementKeys)
{
    movementLockTimeMil = 150;
}

KeyInputStateBattle::~KeyInputStateBattle()
{

}

bool KeyInputStateBattle::handle(std::string *nextState)
{
    if(handleUserInput(nextState))
        return true;

    model->passTime(0);

    if(model->isBattleDone())
    {
        if(model->isGameOver())
        {
            qDebug() << "GAME OVER";
            return false;
        }

        (*nextState) = "Board";
        return true;
    }

    return false;
}

bool KeyInputStateBattle::handleUserInput(std::string *nextState)
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
                || keyToHandle == Qt::Key_E
                || keyToHandle == Qt::Key_Escape
                || keyToHandle == Qt::Key_R
                || keyToHandle == Qt::Key_Q
                )
        {
            auto nowTime = std::chrono::system_clock::now().time_since_epoch();
            auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime).count();
            theTimeNow = (millis);
            timeOfLastButtonEvent = theTimeNow;
            eventBeenSetUp = true;

            if(keyToHandle == Qt::Key_W)
                this->model->moveMenuCursor(0, 1, "Battle");
            else if(keyToHandle == Qt::Key_S)
                this->model->moveMenuCursor(0, -1, "Battle");
            else if(keyToHandle == Qt::Key_D)
                this->model->moveMenuCursor(1, 0, "Battle");
            else if(keyToHandle == Qt::Key_A)
                this->model->moveMenuCursor(-1, 0, "Battle");
            else if(keyToHandle == Qt::Key_E)
                this->model->enterMenu("Battle");
            else if(keyToHandle == Qt::Key_Escape)
                this->model->closeMenu("Battle");
            else if(keyToHandle == Qt::Key_Q)
                this->model->qrPressed(true);
            else if(keyToHandle == Qt::Key_R)
                this->model->qrPressed(false);
        }

        return false;
    }

    //Process the event
    auto nowTime = std::chrono::system_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime).count();
    theTimeNow =(millis);
    elapsed_millies = theTimeNow - timeOfLastButtonEvent;

    if((elapsed_millies / movementLockTimeMil) >= 1)
    {
        eventBeenSetUp = false;
    }

    return false;
}
