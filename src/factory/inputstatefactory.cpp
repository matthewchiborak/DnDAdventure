#include "inputstatefactory.h"

#include "../controller/keyinputstateboard.h"
#include "../controller/keyinputstatepausemenu.h"
#include "../display/renderingstrategyboard.h"
#include "../display/renderingstrategypausemenu.h"

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
    else if(key == "PauseMenu")
    {
        return new KeyInputStatePauseMenu(model, keyboardEventQueue);
    }

    return nullptr;
}

RenderingStrategy *InputStateFactory::getRenderStrategy(std::string key)
{
    if(key == "Board")
    {
        return new RenderingStrategyBoard(model);
    }
    else if(key == "PauseMenu")
    {
        return new RenderingStrategyPauseMenu(model);
    }

    return nullptr;
}
