#include "renderingstrategyboard.h"

#include <QPainter>

RenderingStrategyBoard::RenderingStrategyBoard(ModelAbstract *model)
    : RenderingStrategy(model)
{
    clearColorBrush = QBrush(Qt::red);
}

void RenderingStrategyBoard::draw(QPainter *p)
{
    //Clear the screen
    p->fillRect(0, 0, 150, 200, clearColorBrush);

    model->drawBoardModel(p);
}
