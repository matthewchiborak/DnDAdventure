#include <iostream>

#include "testmain.h"

#include "display/openglwindow.h"



int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    TestMain testmain;
    if(!testmain.executeAllTests())
    {
        std::cout << "Test Failed: " << testmain.getFailedTestId() << " Aborting\n";
        return -1;
    }
    std::cout << "All Tests Passed\n";

    OpenGLWindow window;
    window.resize(450, 600);
    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);
    fmt.setStencilBufferSize(8);
    window.setFormat(fmt);
    window.show();

    std::cout << "Application Running...\n";

    return app.exec();
}
