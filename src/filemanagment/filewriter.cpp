#include "filewriter.h"

#include <QDebug>
#include <fstream>

FileWriter::FileWriter()
{

}

void FileWriter::writeLines(std::string filepath, std::vector<std::string> lines)
{
    std::ofstream myFile_Handler;
    // File Open
    myFile_Handler.open(filepath);

    for(int i = 0; i < lines.size(); i++)
    {
        myFile_Handler << lines.at(i) << "\n";
    }

    myFile_Handler.close();
}


