#include "keyinputstatecutscene.h"

#include "../model/modelabstract.h"

KeyInputStateCutscene::KeyInputStateCutscene(ModelAbstract *model, std::queue<int> *keyboardEventQueue)
    : KeyInputState(model, keyboardEventQueue)
{
    movementLockTimeMil = 150;
}

KeyInputStateCutscene::~KeyInputStateCutscene()
{

}

bool KeyInputStateCutscene::handle(std::string *nextState)
{
    if(!eventBeenSetUp)
    {
        if(keyboardEventQueue->empty())
            return false;

        keyToHandle = keyboardEventQueue->front();

        if(keyToHandle == Qt::Key_E)
        {
            auto nowTime = std::chrono::system_clock::now().time_since_epoch();
            auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime).count();
            theTimeNow = (millis);
            timeOfLastButtonEvent = theTimeNow;
            eventBeenSetUp = true;

            if(keyToHandle == Qt::Key_E)
            {
                model->enterMenu("Cutscene");

                if(model->cutsceneIsDone())
                {
                    if(model->loadBoardBasedOnLoadedCutscene())
                        (*nextState) = "RandomEncounter";
                    else
                        (*nextState) = "Board";
                    return true;
                }
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

