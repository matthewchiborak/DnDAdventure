#include "gamecontroller.h"

#include <QDebug>

#include "keyinputstate.h"

GameController::GameController(ModelAbstract *model, AbstractView *view, std::queue<int> *keyboardEventQueue, InputStateFactoryAbstract *inputStateFactory)
{
    this->model = model;
    this->view = view;
    this->keyboardEventQueue = keyboardEventQueue;
    this->inputStateFactory = inputStateFactory;

    this->keyInputState = inputStateFactory->getState("Board");

    connect(&eventLoopTimer, SIGNAL(timeout()), this, SLOT(eventLoopTimerTimeout()));
}

void GameController::start()
{
    eventLoopTimer.start(40);
}

void GameController::eventLoopTimerTimeout()
{
    handleState();
}

void GameController::handleState()
{
    if(keyInputState->handle(&nextStateKey))
    {
        KeyInputState * temp = keyInputState;
        keyInputState = inputStateFactory->getState(nextStateKey);
        delete temp;
    }
}