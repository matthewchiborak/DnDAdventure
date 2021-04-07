#include "FileReaderTester.h"

#include <QDebug>

#include "../filemanagment/fileReader.h"

#include "../factory/boardobjectfactory.h"
#include "../model/boardobjectobstacle.h"
#include "../factory/inputstatefactory.h"
#include "../model/modelconcrete.h"
#include "../model/playercharacterstats.h"
#include "../model/doorway.h"

FileReaderTester::FileReaderTester()
{

}

FileReaderTester::~FileReaderTester()
{

}

bool FileReaderTester::execute()
{
    if(!readFileContentsTest())
    {
        qDebug() << "FileReaderTest 1 Failed";
        return false;
    }
    if(!boardObjectFactoryPopulateVectorBasedOnTextFileTest())
    {
        qDebug() << "FileReaderTest 2 Failed";
        return false;
    }
    if(!readFileThatHasSpaces())
    {
        qDebug() << "FileReaderTest 3 Failed";
        return false;
    }
    if(!splitStringsTest())
    {
        qDebug() << "FileReaderTest 4 Failed";
        return false;
    }
    if(!factoryForMakingStatesTest())
    {
        qDebug() << "FileReaderTest 5 Failed";
        return false;
    }
    if(!testFillingPlayerBaseStats())
    {
        qDebug() << "FileReaderTest 6 Failed";
        return false;
    }

    return true;
}

bool FileReaderTester::readFileContentsTest()
{
    std::string expected("ThisIsATestMessage");

    FileReader testReader("D:\\Qt Projects\\DnDAdventure\\src\\test\\TestTextFile.txt");

    if(!testReader.hasNext())
        return false;

    if(testReader.next() != expected)
        return false;

    if(testReader.hasNext())
        return false;

    return true;
}

bool FileReaderTester::boardObjectFactoryPopulateVectorBasedOnTextFileTest()
{
    BoardObjectFactory factory;
    std::vector<BoardObjectAbstract*> madeObjects;
    std::vector<Doorway*> doors;
    std::vector<std::string> encounterTable;
    int xPos;
    int yPos;

    factory.populate(&madeObjects, &doors, &encounterTable, &xPos, &yPos, "D:\\Qt Projects\\DnDAdventure\\src\\test\\testobstaclefile.txt");

    if(madeObjects.size() != 2)
        return false;

    if(madeObjects.at(0)->getXpos() != 0)
        return false;
    if(madeObjects.at(0)->getYpos() != 1)
        return false;
    if(madeObjects.at(0)->getWidth() != 2)
        return false;
    if(madeObjects.at(0)->getHeight() != 3)
        return false;
    if(madeObjects.at(0)->getSpriteName() != "Delphox")
        return false;
    if(xPos != 6)
        return false;
    if(yPos != 7)
        return false;
    if(doors.size() != 1)
        return false;
    if(doors.at(0)->getBoardKey() != "D:/Qt Projects/DnDAdventure/src/test/Boards/testobstaclefilesprites2.txt")
        return false;

    return true;
}

bool FileReaderTester::readFileThatHasSpaces()
{
    std::string expected("This has spaces in it.");

    FileReader testReader("D:\\Qt Projects\\DnDAdventure\\src\\test\\TestTextFileSpaces.txt");

    if(!testReader.hasNext())
        return false;

    if(testReader.next() != expected)
        return false;

    if(testReader.hasNext())
        return false;

    return true;
}

bool FileReaderTester::splitStringsTest()
{
    std::string expected("D:\\Qt Projects\\DnDAdventure\\src\\test\\TestTextFileSpaces.txt");

    FileReader testReader("D:\\Qt Projects\\DnDAdventure\\src\\test\\TestTextFileSpaces.txt");

    std::string stringToSplit("D:\\Qt Projects\\DnDAdventure\\src\\test\\TestTextFileSpaces.txt,ThiscanBeAnyThing");

    std::vector<std::string> res = testReader.splitString(stringToSplit, ',');

    if(res.at(0) == expected)
        return false;

    return true;
}

bool FileReaderTester::factoryForMakingStatesTest()
{
    ModelConcrete model;
    std::queue<int> que;
    InputStateFactory fact(&model, &que);
    KeyInputState * testPointer = fact.getState("Board");

    if(testPointer == nullptr)
        return false;

    return true;
}

bool FileReaderTester::testFillingPlayerBaseStats()
{
    PlayerCharacterStats stats("D:\\Qt Projects\\DnDAdventure\\src\\test\\TestPartyMembers\\Bullent.txt");

    if(stats.getName() != "Bullent")
        return false;

//    if(stats.getCurrentHealth() != 1)
//        return false;

    if(stats.getSpriteKey() != "Bullent")
        return false;


    return true;
}
