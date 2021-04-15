#include "inputstatefactoryabstract.h"

InputStateFactoryAbstract::InputStateFactoryAbstract(ModelAbstract *model, std::queue<int> *keyboardEventQueue, std::vector<bool> *movementKeys)
{
    this->model = model;
    this->keyboardEventQueue = keyboardEventQueue;
    this->movementKeys = movementKeys;
}

KeyInputState *InputStateFactoryAbstract::getState(std::string key)
{
    return nullptr;
}

RenderingStrategy *InputStateFactoryAbstract::getRenderStrategy(std::string key)
{
    return nullptr;
}
