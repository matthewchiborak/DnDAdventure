#include "keyinputstatetitle.h"

#include "../model/modelabstract.h"

KeyInputStateTitle::KeyInputStateTitle(ModelAbstract *model, std::queue<int> *keyboardEventQueue)
    : KeyInputState(model, keyboardEventQueue)
{
    movementLockTimeMil = 150;
}

KeyInputStateTitle::~KeyInputStateTitle()
{

}

bool KeyInputStateTitle::handle(std::string *nextState)
{
    if(!eventBeenSetUp)
    {
        if(keyboardEventQueue->empty())
            return false;

        keyToHandle = keyboardEventQueue->front();

        if(keyToHandle == Qt::Key_E || keyToHandle == Qt::Key_W || keyToHandle == Qt::Key_S)
        {
            auto nowTime = std::chrono::system_clock::now().time_since_epoch();
            auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime).count();
            theTimeNow = (millis);
            timeOfLastButtonEvent = theTimeNow;
            eventBeenSetUp = true;

            if(keyToHandle == Qt::Key_E)
            {
                model->enterMenu("Title");

                while(!keyboardEventQueue->empty())
                    keyboardEventQueue->pop();

                //If new game, do the opening cutscene. Else load the save file
                if(model->doIStartANewGame())
                    (*nextState) = "Cutscene";
                else
                    (*nextState) = "Board";
                return true;
            }
            if(keyToHandle == Qt::Key_W)
            {
                model->moveMenuCursor(0, 1, "Title");
                return false;
            }
            if(keyToHandle == Qt::Key_S)
            {
                model->moveMenuCursor(0, -1, "Title");
                return false;
            }
        }

        return false;
    }

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
