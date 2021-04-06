#include "renderingstrategyboard.h"

#include <QPainter>
#include <QDebug>

RenderingStrategyBoard::RenderingStrategyBoard(ModelAbstract *model)
    : RenderingStrategy(model)
{

}

void RenderingStrategyBoard::draw(std::vector<DrawInformation> * items, float *xOffset, float *yOffset)
{
    model->drawBoardModel(items, xOffset, yOffset);
}
