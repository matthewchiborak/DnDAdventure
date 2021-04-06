#ifndef INPUTSTATEFACTORY_H
#define INPUTSTATEFACTORY_H

#include "inputstatefactoryabstract.h"

class InputStateFactory : public InputStateFactoryAbstract
{
public:
    InputStateFactory(ModelAbstract *model, std::queue<int> *keyboardEventQueue);

    KeyInputState * getState(std::string key);
};

#endif // INPUTSTATEFACTORY_H
