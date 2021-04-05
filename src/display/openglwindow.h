#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include "abstractview.h"

class OpenGLWindow : public AbstractView
{
    Q_OBJECT

public:
    OpenGLWindow(ModelAbstract * model, SpriteFlyweightFactoryAbstract * factory);

protected:
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *e) Q_DECL_OVERRIDE;

private:
    QMatrix4x4 m_window_normalised_matrix;
    QMatrix4x4 m_window_painter_matrix;
    QMatrix4x4 m_projection;
    QMatrix4x4 m_view;
    QMatrix4x4 m_model_triangle;
    QMatrix4x4 m_model_text;
    QBrush m_brush;

    float xOffset;
    float yOffset;
};

#endif // OPENGLWINDOW_H
