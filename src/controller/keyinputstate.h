#ifndef KEYINPUTSTATE_H
#define KEYINPUTSTATE_H

#include <iostream>
#include <queue>
#include <QKeyEvent>
#include <chrono>

class ModelAbstract;

class KeyInputState
{
public:
    KeyInputState(ModelAbstract * model, std::queue<int> * keyboardEventQueue);
    //~KeyInputState();

    //bool it returns is true if state change.
    //Next state is the key for the factory to
    //make the next state
    virtual bool handle(std::string * nextState);

protected:
    ModelAbstract * model;
    std::queue<int> * keyboardEventQueue;

    int keyToHandle;

};

#endif // KEYINPUTSTATE_H
