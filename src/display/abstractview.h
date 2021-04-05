#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include <QOpenGLWindow>
#include <QScreen>
#include <QPainter>
#include <QGuiApplication>
#include <QMatrix4x4>
#include <QStaticText>
#include <QKeyEvent>
#include <QPainterPath>
#include <QQueue>
#include <QDebug>

#include "../model/modelabstract.h"
#include "renderingstrategy.h"

class AbstractView : public QOpenGLWindow
{
public:
    AbstractView(ModelAbstract * model, SpriteFlyweightFactoryAbstract * factory); //Should take model

    void setStrategy(RenderingStrategy * renderStrat);

protected:
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *e) Q_DECL_OVERRIDE;

    ModelAbstract * model;
    RenderingStrategy * renderStrat;
    SpriteFlyweightFactoryAbstract * spriteFactory;
};

#endif // ABSTRACTVIEW_H
