QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/display/openglwindow.cpp \
    src/factory/boardobjectfactory.cpp \
    src/factory/worldobjectfactoryabstract.cpp \
    src/filemanagment/fileReader.cpp \
    src/main.cpp \
    src/model/EnemyModel.cpp \
    src/model/boardmodel.cpp \
    src/model/boardobjectabstract.cpp \
    src/model/boardobjectobstacle.cpp \
    src/model/gamemodelabstract.cpp \
    src/test/FileReaderTester.cpp \
    src/test/tester.cpp \
    src/testmain.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/display/openglwindow.h \
    src/factory/boardobjectfactory.h \
    src/factory/worldobjectfactoryabstract.h \
    src/filemanagment/fileReader.h \
    src/model/EnemyModel.h \
    src/model/boardmodel.h \
    src/model/boardobjectabstract.h \
    src/model/boardobjectobstacle.h \
    src/model/gamemodelabstract.h \
    src/test/FileReaderTester.h \
    src/test/tester.h \
    src/testmain.h

FORMS +=
