#include "keyinputstatebattle.h"

#include <QDebug>

KeyInputStateBattle::KeyInputStateBattle(ModelAbstract *model, std::queue<int> *keyboardEventQueue)
    : KeyInputState(model, keyboardEventQueue)
{
    movementLockTimeMil = 150;
}

KeyInputStateBattle::~KeyInputStateBattle()
{

}

bool KeyInputStateBattle::handle(std::string *nextState)
{
    if(handleUserInput(nextState))
        return true;

    return false;
}

bool KeyInputStateBattle::handleUserInput(std::string *nextState)
{
    //qDebug() << "Key Pressed in the battle state";
    return false;
}
