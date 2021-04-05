#include <iostream>
#include <QDebug>

#include "testmain.h"

#include "display/openglwindow.h"

#include "model/modelconcrete.h"

#include "display/renderingstrategyboard.h"

#include "display/spriteflyweightfactory.h"


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

    AbstractView * window = new OpenGLWindow(testModel, spriteFactory);
    window->setStrategy(renderStrat);

    window->resize(1600, 900);
    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);
    fmt.setStencilBufferSize(8);
    window->setFormat(fmt);
    window->show();

    std::cout << "Application Running...\n";

    return app.exec();
}
