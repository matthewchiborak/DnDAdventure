#include "FileReaderTester.h"

#include <QDebug>

#include "../filemanagment/fileReader.h"

#include "../factory/boardobjectfactory.h"
#include "../model/boardobjectobstacle.h"

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

    factory.populate(&madeObjects, "D:\\Qt Projects\\DnDAdventure\\src\\test\\testobstaclefile.txt");

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

    return true;
}
