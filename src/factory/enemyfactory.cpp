#include "enemyfactory.h"

#include "../filemanagment/fileReader.h"
#include "../model/EnemyModel.h"
#include <QDir>

EnemyFactory::EnemyFactory()
{

}

EnemyModel *EnemyFactory::createEnemy(std::string key)
{
    EnemyModel * newEnemy = new EnemyModel();

    QDir dir(QDir::current());
    dir.cdUp();
    //Get the image location from the other map, create and store the flyweight
    std::string enemyFilePath = dir.path().toStdString()+ "/DnDAdventure/src/test/Enemies/" + key;

    FileReader fr(enemyFilePath);

    while(fr.hasNext())
    {
        std::vector<std::string> splits = fr.splitString(fr.next(), ',');

        if(splits.at(0) == "HP")
        {
            newEnemy->setMaxHealth(std::stoi(splits.at(1)));
        }
//        if(splits.at(0) == "BaseMP")
//        {
//            baseMP = std::stoi(splits.at(1));
//        }
        if(splits.at(0) == "Name")
            newEnemy->setName(splits.at(1));
        if(splits.at(0) == "Att")
            newEnemy->setAttack(std::stoi(splits.at(1)));
        if(splits.at(0) == "Def")
            newEnemy->setDefence(std::stoi(splits.at(1)));
        if(splits.at(0) == "MAtt")
            newEnemy->setMagicAttack(std::stoi(splits.at(1)));
        if(splits.at(0) == "MDef")
            newEnemy->setMagicDefence(std::stoi(splits.at(1)));
        if(splits.at(0) == "Speed")
            newEnemy->setSpeed(std::stoi(splits.at(1)));
        if(splits.at(0) == "Sprite")
            newEnemy->setSpriteKey(splits.at(1));
    }

    return newEnemy;
}