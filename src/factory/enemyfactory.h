#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

class EnemyModel;

#include <string>

class EnemyFactory
{
public:
    EnemyFactory();

    EnemyModel * createEnemy(std::string key);
};

#endif // ENEMYFACTORY_H
