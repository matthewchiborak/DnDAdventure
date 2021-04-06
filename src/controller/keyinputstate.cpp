#include "keyinputstate.h"


KeyInputState::KeyInputState(ModelAbstract *model, std::queue<int> *keyboardEventQueue)
{
    this->model = model;
    this->keyboardEventQueue = keyboardEventQueue;

    movementLockTimeMil = 300;
    eventBeenSetUp = false;
}

bool KeyInputState::handle(std::string *nextState)
{
    return false;
}
