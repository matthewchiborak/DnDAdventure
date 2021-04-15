#include "keyinputstate.h"


KeyInputState::KeyInputState(ModelAbstract *model, std::queue<int> *keyboardEventQueue, std::vector<bool> *movementKeys)
{
    this->model = model;
    this->keyboardEventQueue = keyboardEventQueue;
    this->movementKeys = movementKeys;

    movementLockTimeMil = 300;
    eventBeenSetUp = false;
}

bool KeyInputState::handle(std::string *nextState)
{
    return false;
}
