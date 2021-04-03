#include <iostream>
#include "test/FileReaderTester.h"
#include "testmain.h"
#include "test/tester.h"

TestMain::TestMain()
{
    addTest(new FileReaderTester());
}

TestMain::~TestMain()
{
    for (std::vector<Tester*>::iterator it = testsToDo.begin() ; it != testsToDo.end(); ++it)
    {
        delete (*it);
    }
}

void TestMain::addTest(Tester * newTest)
{
    testsToDo.push_back(newTest);
}

bool TestMain::executeAllTests()
{
    bool allTestsPassed = true;

    int index = 0;
    for (std::vector<Tester*>::iterator it = testsToDo.begin() ; it != testsToDo.end(); ++it)
    {
        if(!(*it)->execute())
        {
            //A Test failed
            failedId = index;
            return false;
        }
        index++;
    }

    return allTestsPassed;
}

int TestMain::getFailedTestId()
{
    return failedId;
}
