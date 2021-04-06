#include "inputstatefactory.h"

#include "../controller/keyinputstateboard.h"

InputStateFactory::InputStateFactory(ModelAbstract *model, std::queue<int> *keyboardEventQueue)
    : InputStateFactoryAbstract(model, keyboardEventQueue)
{

}

KeyInputState *InputStateFactory::getState(std::string key)
{
    if(key == "Board")
    {
        return new KeyInputStateBoard(model, keyboardEventQueue);
    }

    return nullptr;
}
