#include "keyinputstateshop.h"

#include "../model/modelabstract.h"

KeyInputStateShop::KeyInputStateShop(ModelAbstract *model, std::queue<int> *keyboardEventQueue, std::vector<bool> *movementKeys)
    : KeyInputState(model, keyboardEventQueue, movementKeys)
{
    movementLockTimeMil = 150;
}

bool KeyInputStateShop::handle(std::string *nextState)
{
    if(handleUserInput(nextState))
        return true;

    return false;
}

bool KeyInputStateShop::handleUserInput(std::string *nextState)
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
                )
        {
            auto nowTime = std::chrono::system_clock::now().time_since_epoch();
            auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime).count();
            theTimeNow = (millis);
            timeOfLastButtonEvent = theTimeNow;
            eventBeenSetUp = true;

            if(keyToHandle == Qt::Key_W)
                this->model->moveMenuCursor(0, 1, "Shop");
            else if(keyToHandle == Qt::Key_S)
                this->model->moveMenuCursor(0, -1, "Shop");
            else if(keyToHandle == Qt::Key_A)
                this->model->moveMenuCursor(-1, 0, "Shop");
            else if(keyToHandle == Qt::Key_D)
                this->model->moveMenuCursor(1, 0, "Shop");
            else if(keyToHandle == Qt::Key_E)
                this->model->enterMenu("Shop");
            else if(keyToHandle == Qt::Key_Escape)
            {
                eventBeenSetUp = false;
                while(!keyboardEventQueue->empty())
                    keyboardEventQueue->pop();
                (*nextState) = "Board";
                return true;
            }
        }

        return false;
    }

    //Prcoess the event
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
