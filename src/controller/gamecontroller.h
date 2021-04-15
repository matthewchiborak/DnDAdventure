#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <vector>
#include <queue>
#include <QKeyEvent>
#include <QTimer>

#include "../factory/inputstatefactoryabstract.h"

class ModelAbstract;
class AbstractView;
class KeyInputState;


class GameController : public QObject
{
    Q_OBJECT
public:
    GameController(ModelAbstract * model,
                   AbstractView * view,
                   std::queue<int> * keyboardEventQueue,
                   std::vector<bool> * movementKeys,
                   InputStateFactoryAbstract * inputStateFactory);

    //Starts the timer for the timeout loop to handle events
    void start();

private slots:
    void eventLoopTimerTimeout();

private:
    ModelAbstract * model;
    AbstractView * view;
    std::queue<int> * keyboardEventQueue;
    std::vector<bool> * movementKeys;

    QTimer eventLoopTimer;

    //Input state
    KeyInputState * keyInputState;
    std::string nextStateKey;
    InputStateFactoryAbstract * inputStateFactory;

    void handleState();
    void checkDoors();
    void checkRandomEncounter();

};

#endif // GAMECONTROLLER_H
