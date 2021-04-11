#ifndef MONSTERMANUALENTRY_H
#define MONSTERMANUALENTRY_H

#include <string>

class MonsterManualEntry
{
public:
    MonsterManualEntry(std::string key, std::string name);

    std::string getName();
    std::string getKey();
    bool getDefeated();
    void defeat();

    void setName(std::string name);

private:
    std::string name;
    bool defeated;
    std::string key;
};

#endif // MONSTERMANUALENTRY_H
