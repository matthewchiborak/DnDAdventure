#ifndef SHOPMODEL_H
#define SHOPMODEL_H

#include <string>
#include <vector>

class DrawInformation;
class EquipmentModel;

class ShopModel
{
public:
    ShopModel();

    void load(std::string info,
              int * gold,
              int * numberOfPotions,
              int * numberOfRemedies,
              int * numberOfEthers,
              int * numberOfPickleJars,
              std::vector<EquipmentModel*> * equipment
              );

    void confirm();

    void moveMenuCursor(int x, int y);

    void draw(std::vector<DrawInformation> * items);

private:
    int cursorPos = 0;
    int numberofItems = 0;

    std::vector<int> prices;
    std::vector<std::string> names;
    std::vector<std::string> desc;
    std::vector<std::string> inventory;

    int * gold;
    int * numberOfPotions;
    int * numberOfRemedies;
    int * numberOfEthers;
    int * numberOfPickleJars;
    std::vector<EquipmentModel*> * equipment;

    void clear();
};

#endif // SHOPMODEL_H
