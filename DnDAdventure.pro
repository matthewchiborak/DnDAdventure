QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS+ = -lGL -lGLU

SOURCES += \
    src/controller/gamecontroller.cpp \
    src/controller/keyinputstate.cpp \
    src/controller/keyinputstateboard.cpp \
    src/display/abstractview.cpp \
    src/display/drawinformation.cpp \
    src/display/fglut.cpp \
    src/display/openglwindow.cpp \
    src/display/renderingstrategy.cpp \
    src/display/renderingstrategyboard.cpp \
    src/display/spriteflyweight.cpp \
    src/display/spriteflyweightfactory.cpp \
    src/display/spriteflyweightfactoryabstract.cpp \
    src/display/stb_image.c \
    src/factory/boardobjectfactory.cpp \
    src/factory/inputstatefactory.cpp \
    src/factory/inputstatefactoryabstract.cpp \
    src/factory/worldobjectfactoryabstract.cpp \
    src/filemanagment/fileReader.cpp \
    src/main.cpp \
    src/model/EnemyModel.cpp \
    src/model/boardmodel.cpp \
    src/model/boardobjectabstract.cpp \
    src/model/boardobjectnpc.cpp \
    src/model/boardobjectobstacle.cpp \
    src/model/gamemodelabstract.cpp \
    src/model/modelabstract.cpp \
    src/model/modelconcrete.cpp \
    src/model/playercharacterstats.cpp \
    src/test/FileReaderTester.cpp \
    src/test/tester.cpp \
    src/testmain.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/controller/gamecontroller.h \
    src/controller/keyinputstate.h \
    src/controller/keyinputstateboard.h \
    src/display/abstractview.h \
    src/display/drawinformation.h \
    src/display/fglut.h \
    src/display/matrixes.h \
    src/display/openglwindow.h \
    src/display/renderingstrategy.h \
    src/display/renderingstrategyboard.h \
    src/display/spriteflyweight.h \
    src/display/spriteflyweightfactory.h \
    src/display/spriteflyweightfactoryabstract.h \
    src/display/stb_image.h \
    src/factory/boardobjectfactory.h \
    src/factory/inputstatefactory.h \
    src/factory/inputstatefactoryabstract.h \
    src/factory/worldobjectfactoryabstract.h \
    src/filemanagment/fileReader.h \
    src/model/EnemyModel.h \
    src/model/boardmodel.h \
    src/model/boardobjectabstract.h \
    src/model/boardobjectnpc.h \
    src/model/boardobjectobstacle.h \
    src/model/gamemodelabstract.h \
    src/model/modelabstract.h \
    src/model/modelconcrete.h \
    src/model/playercharacterstats.h \
    src/test/FileReaderTester.h \
    src/test/tester.h \
    src/testmain.h

LIBS += -lOpenGL32

LIBS += -lGlU32


FORMS +=
