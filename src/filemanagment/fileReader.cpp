#include "fileReader.h"

#include <fstream>
#include <string>
#include <sstream>

FileReader::FileReader(std::string fileName)
{
    this->fileName = fileName;

    read();
}

void FileReader::read()
{
    std::ifstream file(fileName);

    std::string singleLine = "";

    while (std::getline(file, singleLine)) {
      // Output the text from the file
        fileLines.push(singleLine);
    }
}

bool FileReader::hasNext()
{
    return (fileLines.size() > 0);
}

std::string FileReader::next()
{
    if(hasNext())
    {
        std::string temp = fileLines.front();
        fileLines.pop();
        return temp;
    }

    return "";
}

std::vector<std::string> FileReader::splitString(std::string line, char delimeter)
{
    std::vector<std::string> vect;

    std::stringstream ss(line);
    std::string currentLine = "";

    for (char i; ss >> i;) {
        currentLine.push_back(i);
        if (ss.peek() == delimeter)
        {
            ss.ignore();
            vect.push_back(currentLine);
            currentLine = "";
        }
    }

    //Forgot to add the end of the string
    vect.push_back(currentLine);

    return vect;
}

std::string FileReader::replaceCharacter(std::string line, char before, char after)
{
    std::string result = "";
    for(int i = 0; i < line.size(); i++)
    {
        if(line.at(i) == before)
        {
            result.push_back(after);
        }
        else
        {
            result.push_back(line.at(i));
        }
    }
    return result;
}
