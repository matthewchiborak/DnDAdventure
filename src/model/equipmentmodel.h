#ifndef EQUIPMENTMODEL_H
#define EQUIPMENTMODEL_H

#include <string>

class EquipmentModel
{
public:
    EquipmentModel(std::string creationInfo, int index);

    std::string getName();
    std::string getType();
    int getPartyMemberLimit();
    std::string getEffect();
    float getMultiplier();
    std::string getDescription();
    int getIndexInBag();

private:
    int indexInBag = 0;
    std::string name;
    int partyMemberLimit = 0; //0 - all, 1 - bullent
    //2 - chad, 3-allura, 4-duke, 5-BullentDuke(Light) 6-ChadAllura(Heavy)
    std::string type;
    std::string desc;
    std::string effect;
    float mulitplier;
};

#endif // EQUIPMENTMODEL_H
