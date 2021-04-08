#ifndef ENCOUNTERFACTORYABSTRACT_H
#define ENCOUNTERFACTORYABSTRACT_H

#include <string>
#include <vector>
#include <map>
#include "../model/EnemyModel.h"


class EncounterFactory
{
public:
    EncounterFactory(std::string encounterFilePath);

    int populate(std::vector<EnemyModel*> * enemies, std::string key);

private:
    std::map<std::string, std::string> keyToEnemyFiles;
};

#endif // ENCOUNTERFACTORYABSTRACT_H
