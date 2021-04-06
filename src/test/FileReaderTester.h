#ifndef FILE_READER_TESTER_HEADER
#define FILE_READER_TESTER_HEADER

#include "tester.h"

class FileReaderTester: public Tester
{
public:
    FileReaderTester();
    ~FileReaderTester();

    bool execute();
private :
    bool readFileContentsTest();
    bool boardObjectFactoryPopulateVectorBasedOnTextFileTest();
    bool readFileThatHasSpaces();
    bool splitStringsTest();
    bool factoryForMakingStatesTest();
};

#endif
