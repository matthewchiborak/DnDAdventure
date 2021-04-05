#ifndef FILE_READER_HEADER
#define FILE_READER_HEADER

#include <iostream>
#include <queue>

class FileReader
{
public:
    FileReader(std::string fileName);

    bool hasNext();
    std::string next();

    std::vector<std::string> splitString(std::string line, char delimeter);

private:
    std::string fileName;
    std::queue<std::string> fileLines;

    void read();
};

#endif
