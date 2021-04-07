#include "encounterfactory.h"

#include "../filemanagment/fileReader.h"
#include "enemyfactory.h"

#include <QDebug>

EncounterFactory::EncounterFactory(std::string encounterFilePath)
{
    FileReader reader(encounterFilePath);

    while(reader.hasNext())
    {
        std::string readString = reader.next();
        std::vector<std::string> vect = reader.splitString(readString, ',');

        if(vect.size() > 1)
        {
            keyToEnemyFiles.insert(std::pair<std::string,std::string>(vect.at(0), readString.substr(readString.find(",")).substr(1)));
        }
    }
}

void EncounterFactory::populate(std::vector<EnemyModel *> *enemies, std::string key)
{
    EnemyFactory enemyfact;

    std::string enemiesInEncounter = keyToEnemyFiles[key];

    std::vector<std::string> enemyKeys = FileReader::splitString(enemiesInEncounter, ',');

    for(int i = 0; i < enemyKeys.size(); i++)
    {
        enemies->push_back(enemyfact.createEnemy(enemyKeys.at(i)));
    }
}
