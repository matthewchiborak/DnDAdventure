#include "enemyfactory.h"

#include "../filemanagment/fileReader.h"
#include "../model/EnemyModel.h"
#include <QDir>
#include "../model/attackmodel.h"

EnemyFactory::EnemyFactory()
{

}

EnemyModel *EnemyFactory::createEnemy(std::string key)
{
    EnemyModel * newEnemy = new EnemyModel();
    newEnemy->setCutsceneToPlayOnDefeat("None");

    QDir dir(QDir::current());
    dir.cdUp();
    //Get the image location from the other map, create and store the flyweight
    std::string enemyFilePath = dir.path().toStdString()+ "/DnDAdventure/src/test/Enemies/" + key + ".txt";

    FileReader fr(enemyFilePath);

    while(fr.hasNext())
    {
        std::string nextLine = fr.next();
        std::vector<std::string> splits = fr.splitString(nextLine, ',');

        newEnemy->setEnemyKey(key);

        if(splits.at(0) == "HP")
        {
            newEnemy->setMaxHealth(std::stoi(splits.at(1)));
        }
//        if(splits.at(0) == "BaseMP")
//        {
//            baseMP = std::stoi(splits.at(1));
//        }
        if(splits.at(0) == "Name")
        {
            newEnemy->setName(FileReader::replaceCharacter(splits.at(1), '_', ' '));
        }
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
        if(splits.at(0) == "XP")
            newEnemy->setXP(std::stoi(splits.at(1)));
        if(splits.at(0) == "Sprite")
            newEnemy->setSpriteKey(splits.at(1));
        if(splits.at(0) == "Level")
            newEnemy->setLevel(std::stoi(splits.at(1)));
        if(splits.at(0) == "Attack")
            newEnemy->addAttack(new AttackModel(nextLine));
        if(splits.at(0) == "Weak")
            newEnemy->addWeakness(std::stoi(splits.at(1)));
        if(splits.at(0) == "Res")
            newEnemy->addResistance(std::stoi(splits.at(1)));
        if(splits.at(0) == "Half")
            newEnemy->addHalfed(std::stoi(splits.at(1)));
        if(splits.at(0) == "Immune")
            newEnemy->addImmunity(std::stoi(splits.at(1)));
        if(splits.at(0) == "Absorb")
            newEnemy->addAbsorbed(std::stoi(splits.at(1)));
        if(splits.at(0) == "StatusImmune")
            newEnemy->addStatusImmunity(splits.at(1));
        if(splits.at(0) == "Cutscene")
            newEnemy->setCutsceneToPlayOnDefeat(splits.at(1));
    }

    return newEnemy;
}
