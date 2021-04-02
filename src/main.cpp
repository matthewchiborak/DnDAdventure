#include <iostream>
#include "src/model/EnemyModel.h"

int main()
{
    std::cout << "Hello World";
    EnemyModel test(1,2,3,4,5,6);
    std::cout << test.getAttack();
}
