#include "monstermanualentry.h"

MonsterManualEntry::MonsterManualEntry(std::string key, std::string name)
{
    this->name = name;
    defeated = false;
    this->key = key;
}

std::string MonsterManualEntry::getName()
{
    return name;
}

std::string MonsterManualEntry::getKey()
{
    return key;
}

bool MonsterManualEntry::getDefeated()
{
    return defeated;
}

void MonsterManualEntry::defeat()
{
    defeated = true;
}

void MonsterManualEntry::setName(std::string name)
{
    this->name = name;
}
