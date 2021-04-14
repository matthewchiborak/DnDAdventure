QT       += core gui opengl multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS+ = -lGL -lGLU

SOURCES += \
    src/controller/battlemenustate.cpp \
    src/controller/battlemenustateaccess.cpp \
    src/controller/battlemenustateattack.cpp \
    src/controller/battlemenustatebattleover.cpp \
    src/controller/battlemenustateflee.cpp \
    src/controller/battlemenustateitem.cpp \
    src/controller/battlemenustatemain.cpp \
    src/controller/battlemenustatespecial.cpp \
    src/controller/battlemenustateswitch.cpp \
    src/controller/battlemenustatetimeflow.cpp \
    src/controller/gamecontroller.cpp \
    src/controller/keyinputstate.cpp \
    src/controller/keyinputstatebattle.cpp \
    src/controller/keyinputstateboard.cpp \
    src/controller/keyinputstatecutscene.cpp \
    src/controller/keyinputstatepausemenu.cpp \
    src/controller/musiccontrollerabstract.cpp \
    src/controller/musiccontrollerconcrete.cpp \
    src/controller/pausemenustate.cpp \
    src/controller/pausemenustatebag.cpp \
    src/controller/pausemenustateequipment.cpp \
    src/controller/pausemenustatemain.cpp \
    src/controller/pausemenustatemonstermanual.cpp \
    src/controller/pausemenustateparty.cpp \
    src/controller/pausemenustateskills.cpp \
    src/display/aboveheadbattlemessage.cpp \
    src/display/abstractview.cpp \
    src/display/drawinformation.cpp \
    src/display/fglut.cpp \
    src/display/openglwindow.cpp \
    src/display/renderingstrategy.cpp \
    src/display/renderingstrategybattle.cpp \
    src/display/renderingstrategyboard.cpp \
    src/display/renderingstrategycutscene.cpp \
    src/display/renderingstrategypausemenu.cpp \
    src/display/spriteflyweight.cpp \
    src/display/spriteflyweightfactory.cpp \
    src/display/spriteflyweightfactoryabstract.cpp \
    src/display/stb_image.c \
    src/factory/boardobjectfactory.cpp \
    src/factory/encounterfactory.cpp \
    src/factory/enemyfactory.cpp \
    src/factory/inputstatefactory.cpp \
    src/factory/inputstatefactoryabstract.cpp \
    src/factory/worldobjectfactoryabstract.cpp \
    src/filemanagment/fileReader.cpp \
    src/main.cpp \
    src/model/EnemyModel.cpp \
    src/model/attackmodel.cpp \
    src/model/battlemodel.cpp \
    src/model/boardmodel.cpp \
    src/model/boardobjectabstract.cpp \
    src/model/boardobjectchest.cpp \
    src/model/boardobjectcutscenetrigger.cpp \
    src/model/boardobjectnpc.cpp \
    src/model/boardobjectobstacle.cpp \
    src/model/cutscenemodel.cpp \
    src/model/doorway.cpp \
    src/model/equipmentmodel.cpp \
    src/model/gamemodelabstract.cpp \
    src/model/modelabstract.cpp \
    src/model/modelconcrete.cpp \
    src/model/monstermanualentry.cpp \
    src/model/playercharacterstats.cpp \
    src/model/playercharacterstatsbattle.cpp \
    src/model/statuseffectmodel.cpp \
    src/test/FileReaderTester.cpp \
    src/test/tester.cpp \
    src/testmain.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/controller/battlemenustate.h \
    src/controller/battlemenustateaccess.h \
    src/controller/battlemenustateattack.h \
    src/controller/battlemenustatebattleover.h \
    src/controller/battlemenustateflee.h \
    src/controller/battlemenustateitem.h \
    src/controller/battlemenustatemain.h \
    src/controller/battlemenustatespecial.h \
    src/controller/battlemenustateswitch.h \
    src/controller/battlemenustatetimeflow.h \
    src/controller/gamecontroller.h \
    src/controller/keyinputstate.h \
    src/controller/keyinputstatebattle.h \
    src/controller/keyinputstateboard.h \
    src/controller/keyinputstatecutscene.h \
    src/controller/keyinputstatepausemenu.h \
    src/controller/musiccontrollerabstract.h \
    src/controller/musiccontrollerconcrete.h \
    src/controller/pausemenustate.h \
    src/controller/pausemenustatebag.h \
    src/controller/pausemenustateequipment.h \
    src/controller/pausemenustatemain.h \
    src/controller/pausemenustatemonstermanual.h \
    src/controller/pausemenustateparty.h \
    src/controller/pausemenustateskills.h \
    src/display/aboveheadbattlemessage.h \
    src/display/abstractview.h \
    src/display/drawinformation.h \
    src/display/fglut.h \
    src/display/matrixes.h \
    src/display/openglwindow.h \
    src/display/renderingstrategy.h \
    src/display/renderingstrategybattle.h \
    src/display/renderingstrategyboard.h \
    src/display/renderingstrategycutscene.h \
    src/display/renderingstrategypausemenu.h \
    src/display/spriteflyweight.h \
    src/display/spriteflyweightfactory.h \
    src/display/spriteflyweightfactoryabstract.h \
    src/display/stb_image.h \
    src/factory/boardobjectfactory.h \
    src/factory/encounterfactory.h \
    src/factory/enemyfactory.h \
    src/factory/inputstatefactory.h \
    src/factory/inputstatefactoryabstract.h \
    src/factory/worldobjectfactoryabstract.h \
    src/filemanagment/fileReader.h \
    src/model/EnemyModel.h \
    src/model/attackmodel.h \
    src/model/battlemodel.h \
    src/model/boardmodel.h \
    src/model/boardobjectabstract.h \
    src/model/boardobjectchest.h \
    src/model/boardobjectcutscenetrigger.h \
    src/model/boardobjectnpc.h \
    src/model/boardobjectobstacle.h \
    src/model/cutscenemodel.h \
    src/model/doorway.h \
    src/model/equipmentmodel.h \
    src/model/gamemodelabstract.h \
    src/model/modelabstract.h \
    src/model/modelconcrete.h \
    src/model/monstermanualentry.h \
    src/model/playercharacterstats.h \
    src/model/playercharacterstatsbattle.h \
    src/model/statuseffectmodel.h \
    src/test/FileReaderTester.h \
    src/test/tester.h \
    src/testmain.h

LIBS += -lOpenGL32

LIBS += -lGlU32


FORMS +=
