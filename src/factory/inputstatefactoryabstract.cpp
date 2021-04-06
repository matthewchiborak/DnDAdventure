#include "inputstatefactoryabstract.h"

InputStateFactoryAbstract::InputStateFactoryAbstract(ModelAbstract *model, std::queue<int> *keyboardEventQueue)
{
    this->model = model;
    this->keyboardEventQueue = keyboardEventQueue;
}

KeyInputState *InputStateFactoryAbstract::getState(std::string key)
{
    return nullptr;
}
