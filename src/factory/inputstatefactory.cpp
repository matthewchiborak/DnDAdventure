#include "inputstatefactory.h"

#include "../controller/keyinputstateboard.h"
#include "../controller/keyinputstatepausemenu.h"
#include "../controller/keyinputstatebattle.h"
#include "../controller/keyinputstatecutscene.h"
#include "../display/renderingstrategyboard.h"
#include "../display/renderingstrategypausemenu.h"
#include "../display/renderingstrategybattle.h"
#include "../display/renderingstrategycutscene.h"
#include "../display/renderingstrategytitle.h"
#include "../controller/keyinputstatetitle.h"

InputStateFactory::InputStateFactory(ModelAbstract *model, std::queue<int> *keyboardEventQueue, std::vector<bool> *movementKeys)
    : InputStateFactoryAbstract(model, keyboardEventQueue, movementKeys)
{

}

KeyInputState *InputStateFactory::getState(std::string key)
{
    if(key == "Board")
    {
        return new KeyInputStateBoard(model, keyboardEventQueue, movementKeys);
    }
    else if(key == "PauseMenu")
    {
        return new KeyInputStatePauseMenu(model, keyboardEventQueue, movementKeys);
    }
    else if(key == "RandomEncounter")
    {
        return new KeyInputStateBattle(model, keyboardEventQueue, movementKeys);
    }
    else if(key == "Cutscene")
    {
        return new KeyInputStateCutscene(model, keyboardEventQueue, movementKeys);
    }
    else if(key == "Title")
    {
        return new KeyInputStateTitle(model, keyboardEventQueue, movementKeys);
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
    else if(key == "RandomEncounter")
    {
        return new RenderingStrategyBattle(model);
    }
    else if(key == "Cutscene")
    {
        return new RenderingStrategyCutscene(model);
    }
    else if(key == "Title")
    {
        return new RenderingStrategyTitle(model);
    }

    return nullptr;
}
