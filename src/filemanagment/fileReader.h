#ifndef FILE_READER_HEADER
#define FILE_READER_HEADER

#include <iostream>

class FileReader
{
public:
    FileReader(std::string fileName);

    std::string readFileContents();

private:
    std::string fileName;
};

#endif
