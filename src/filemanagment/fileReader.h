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

    static std::vector<std::string> splitString(std::string line, char delimeter);
    static std::string replaceCharacter(std::string line, char before, char after);

private:
    std::string fileName;
    std::queue<std::string> fileLines;

    void read();
};

#endif
