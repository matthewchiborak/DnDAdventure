#include "fileReader.h"

#include <fstream>
#include <string>

FileReader::FileReader(std::string fileName)
{
    this->fileName = fileName;
}

std::string FileReader::readFileContents()
{
    std::ifstream file(fileName);

    std::string contents = "";
    std::string singleLine = "";

    while (std::getline(file, singleLine)) {
      // Output the text from the file
        contents += singleLine;
    }

    return contents;
}
