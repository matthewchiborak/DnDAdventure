#include "renderingstrategybattle.h"

RenderingStrategyBattle::RenderingStrategyBattle(ModelAbstract *model)
    : RenderingStrategy(model)
{

}

void RenderingStrategyBattle::draw(std::vector<DrawInformation> *items, float *xOffset, float *yOffset)
{
    (*xOffset) = -800;
    (*yOffset) = 0;
    model->drawBattleModel(items);
}
