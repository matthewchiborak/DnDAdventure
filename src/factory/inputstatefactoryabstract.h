#ifndef INPUTSTATEFACTORYABSTRACT_H
#define INPUTSTATEFACTORYABSTRACT_H

#include <iostream>
#include <queue>
#include <QKeyEvent>


class KeyInputState;
class ModelAbstract;
class RenderingStrategy;

class InputStateFactoryAbstract
{
public:
    InputStateFactoryAbstract(ModelAbstract *model, std::queue<int> *keyboardEventQueue, std::vector<bool> * movementKeys);

    virtual KeyInputState * getState(std::string key);
    virtual RenderingStrategy * getRenderStrategy(std::string key);

protected:
    ModelAbstract *model;
    std::queue<int> *keyboardEventQueue;
    std::vector<bool> * movementKeys;
};

#endif // INPUTSTATEFACTORYABSTRACT_H
