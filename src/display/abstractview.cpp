#include "abstractview.h"

AbstractView::AbstractView(ModelAbstract * model, std::queue<int> * keyboardEventQueue, SpriteFlyweightFactoryAbstract *factory)
    : QOpenGLWindow(QOpenGLWindow::NoPartialUpdate)
{
    this->model = model;
    this->spriteFactory = factory;
    this->keyboardEventQueue = keyboardEventQueue;
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

void AbstractView::keyReleaseEvent(QKeyEvent *e)
{

}



