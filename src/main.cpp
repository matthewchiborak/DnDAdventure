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

#include "controller/musiccontrollerconcrete.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

//    TestMain testmain;
//    if(!testmain.executeAllTests())
//    {
//        qDebug() << "Test Failed: " << testmain.getFailedTestId() << " Aborting\n";
//        return -1;
//    }
//    qDebug() << "All Tests Passed\n";

    SpriteFlyweightFactoryAbstract * spriteFactory =
            new SpriteFlyweightFactory("D:\\Qt Projects\\DnDAdventure\\src\\test\\SpritePaths.txt");

    MusicControllerAbstract * musicController = new MusicControllerConcrete("D:\\Qt Projects\\DnDAdventure\\src\\test\\MusicPaths.txt");
    musicController->manualLoad("Hit", "Hit");
    musicController->manualLoad("Miss", "Miss");
    musicController->manualLoad("Thud", "Thud");

    ModelAbstract * testModel = new ModelConcrete(musicController);
    testModel->loadMonsterManual("D:\\Qt Projects\\DnDAdventure\\src\\test\\monstermanual.txt");
    testModel->addPlayerCharacter(new PlayerCharacterStats("D:\\Qt Projects\\DnDAdventure\\src\\test\\TestPartyMembers\\Bullent.txt"));
    testModel->addPlayerCharacter(new PlayerCharacterStats("D:\\Qt Projects\\DnDAdventure\\src\\test\\TestPartyMembers\\Chad.txt"));
    testModel->addPlayerCharacter(new PlayerCharacterStats("D:\\Qt Projects\\DnDAdventure\\src\\test\\TestPartyMembers\\Allura.txt"));
    testModel->addPlayerCharacter(new PlayerCharacterStats("D:\\Qt Projects\\DnDAdventure\\src\\test\\TestPartyMembers\\Duke.txt"));
    testModel->loadBoardModel("testobstaclefilesprites.txt");

    RenderingStrategy * renderStrat = new RenderingStrategyBoard(testModel);

    std::queue<int> keyboardEventQueue;

    AbstractView * window = new OpenGLWindow(testModel, &keyboardEventQueue, spriteFactory);
    window->setStrategy(renderStrat);

    InputStateFactoryAbstract * inputStateFact = new InputStateFactory(testModel, &keyboardEventQueue);

    GameController gameController(testModel, window, &keyboardEventQueue, inputStateFact);
    testModel->loadSaveGame();
    gameController.start();

    window->resize(1600, 900);
    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);
    fmt.setStencilBufferSize(8);
    window->setFormat(fmt);
    window->show();

    qDebug() << "Application Running...\n";

    return app.exec();
}
