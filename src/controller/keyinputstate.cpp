#include "keyinputstate.h"


KeyInputState::KeyInputState(ModelAbstract *model, std::queue<int> *keyboardEventQueue)
{
    this->model = model;
    this->keyboardEventQueue = keyboardEventQueue;
}

bool KeyInputState::handle(std::string *nextState)
{
    return false;
}
