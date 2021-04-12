#include "keyinputstatepausemenu.h"

#include "../model/modelabstract.h"

KeyInputStatePauseMenu::KeyInputStatePauseMenu(ModelAbstract *model, std::queue<int> *keyboardEventQueue)
    : KeyInputState(model, keyboardEventQueue)
{
    movementLockTimeMil = 150;
    model->setPauseIsDone(false);
}

KeyInputStatePauseMenu::~KeyInputStatePauseMenu()
{

}

bool KeyInputStatePauseMenu::handle(std::string *nextState)
{
    if(handleUserInput(nextState))
        return true;

    return false;
}

bool KeyInputStatePauseMenu::handleUserInput(std::string *nextState)
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
                || keyToHandle == Qt::Key_X
                || keyToHandle == Qt::Key_Q
                || keyToHandle == Qt::Key_R
                )
        {
            auto nowTime = std::chrono::system_clock::now().time_since_epoch();
            auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime).count();
            theTimeNow = (millis);
            timeOfLastButtonEvent = theTimeNow;
            eventBeenSetUp = true;

            if(keyToHandle == Qt::Key_W)
                this->model->moveMenuCursor(0, 1, "Pause");
            else if(keyToHandle == Qt::Key_S)
                this->model->moveMenuCursor(0, -1, "Pause");
            else if(keyToHandle == Qt::Key_A)
                this->model->moveMenuCursor(-1, 0, "Pause");
            else if(keyToHandle == Qt::Key_D)
                this->model->moveMenuCursor(1, 0, "Pause");
            else if(keyToHandle == Qt::Key_E)
                this->model->enterMenu("Pause");
            else if(keyToHandle == Qt::Key_R)
                this->model->specialMessage("PageForward", "Pause");
            else if(keyToHandle == Qt::Key_Q)
                this->model->specialMessage("PageBack", "Pause");
            else if(keyToHandle == Qt::Key_X)
                this->model->specialMessage("RemoveEquipment", "Pause");
            else if(keyToHandle == Qt::Key_Escape)
            {
                this->model->closeMenu("Pause");
                if(this->model->getPauseIsDone())
                {
                    eventBeenSetUp = false;
                    while(!keyboardEventQueue->empty())
                        keyboardEventQueue->pop();
                    (*nextState) = "Board";
                    return true;
                }
            }
        }

        return false;
    }

    //Process the event
    //Prcoess the event
    auto nowTime = std::chrono::system_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime).count();
    theTimeNow =(millis);
    elapsed_millies = theTimeNow - timeOfLastButtonEvent;

    //if(keyToHandle == Qt::Key_W)
        //this->model->movePlayer(0, 1, ((elapsed_millies/movementLockTimeMil)));
    //else if(keyToHandle == Qt::Key_S)
        //this->model->movePlayer(0, -1, ((elapsed_millies/movementLockTimeMil)));
    //else if(keyToHandle == Qt::Key_A)
        //this->model->movePlayer(-1, 0, ((elapsed_millies/movementLockTimeMil)));
    //else if(keyToHandle == Qt::Key_D)
        //this->model->movePlayer(1, 0, ((elapsed_millies/movementLockTimeMil)));
//    if(keyToHandle == Qt::Key_Escape)
//    {
//        eventBeenSetUp = false;
//        while(!keyboardEventQueue->empty())
//            keyboardEventQueue->pop();
//        (*nextState) = "Board";
//        return true;
//    }

    if((elapsed_millies / movementLockTimeMil) >= 1)
    {
        eventBeenSetUp = false;
    }

    return false;
}
