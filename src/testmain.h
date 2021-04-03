#ifndef TEST_MAIN_HEADER
#define TEST_MAIN_HEADER

#include <vector>

#include "test/tester.h"

class TestMain
{
public:
    TestMain();
    ~TestMain();

    void addTest(Tester * newTest);
    bool executeAllTests();
    int getFailedTestId();

private:
    std::vector<Tester*> testsToDo;
    int failedId;
};

#endif
