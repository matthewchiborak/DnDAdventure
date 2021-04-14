#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <string>
#include <vector>

class FileWriter
{
public:
    FileWriter();

    void writeLines(std::string filepath, std::vector<std::string> lines);
};

#endif // FILEWRITER_H
