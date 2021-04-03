#include "FileReaderTester.h"

#include "../filemanagment/fileReader.h"

FileReaderTester::FileReaderTester()
{

}

FileReaderTester::~FileReaderTester()
{

}

bool FileReaderTester::execute()
{
    return readFileContentsTest();
}

bool FileReaderTester::readFileContentsTest()
{
    FileReader testReader("D:\\Qt Projects\\DnDAdventure\\src\\test\\TestTextFile.txt");

    std::string expected("ThisIsATestMessage");
    std::string gotString = testReader.readFileContents();

    return (gotString == expected);
}
