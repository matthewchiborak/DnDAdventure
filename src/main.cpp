#include <iostream>
#include <QDebug>
#include <queue>

#include "testmain.h"

#include "display/openglwindow.h"

#include "model/modelconcrete.h"

#include "display/renderingstrategyboard.h"

#include "display/spriteflyweightfactory.h"

#include "controller/gamecontroller.h"

#include "factory/inputstatefactory.h"



int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    TestMain testmain;
    if(!testmain.executeAllTests())
    {
        qDebug() << "Test Failed: " << testmain.getFailedTestId() << " Aborting\n";
        return -1;
    }
    qDebug() << "All Tests Passed\n";

    SpriteFlyweightFactoryAbstract * spriteFactory =
            new SpriteFlyweightFactory("D:\\Qt Projects\\DnDAdventure\\src\\test\\SpritePaths.txt");

    ModelAbstract * testModel = new ModelConcrete();
    testModel->loadBoardModel("D:\\Qt Projects\\DnDAdventure\\src\\test\\testobstaclefilesprites.txt");

    RenderingStrategy * renderStrat = new RenderingStrategyBoard(testModel);

    std::queue<int> keyboardEventQueue;

    AbstractView * window = new OpenGLWindow(testModel, &keyboardEventQueue, spriteFactory);
    window->setStrategy(renderStrat);

    InputStateFactoryAbstract * inputStateFact = new InputStateFactory(testModel, &keyboardEventQueue);

    GameController gameController(testModel, window, &keyboardEventQueue, inputStateFact);
    gameController.start();

    window->resize(1600, 900);
    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);
    fmt.setStencilBufferSize(8);
    window->setFormat(fmt);
    window->show();

    std::cout << "Application Running...\n";

    return app.exec();
}
