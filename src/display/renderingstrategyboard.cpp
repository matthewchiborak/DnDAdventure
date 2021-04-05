#include "renderingstrategyboard.h"

#include <QPainter>
#include <QDebug>

RenderingStrategyBoard::RenderingStrategyBoard(ModelAbstract *model)
    : RenderingStrategy(model)
{
    clearColorBrush = QBrush(Qt::black);
}

void RenderingStrategyBoard::draw(std::vector<DrawInformation> * items)
{
    model->drawBoardModel(items);
}
