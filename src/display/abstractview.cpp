#include "abstractview.h"

AbstractView::AbstractView(ModelAbstract * model)
    : QOpenGLWindow(QOpenGLWindow::NoPartialUpdate)
{
    this->model = model;
}

void AbstractView::setStrategy(RenderingStrategy *renderStrat)
{
    this->renderStrat = renderStrat;
}

void AbstractView::paintGL()
{

}

void AbstractView::resizeGL(int w, int h)
{

}

void AbstractView::keyPressEvent(QKeyEvent *e)
{

}


