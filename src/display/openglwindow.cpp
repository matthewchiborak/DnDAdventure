#include "openglwindow.h"



OpenGLWindow::OpenGLWindow()
    : QOpenGLWindow(QOpenGLWindow::NoPartialUpdate)
{
    m_view.lookAt(QVector3D(0,0,0),
                  QVector3D(0,0,0),
                  QVector3D(0,1,0));

    QLinearGradient gradient(QPointF(-1,-1), QPointF(1,1));
    gradient.setColorAt(0, Qt::red);
    gradient.setColorAt(1, Qt::green);

    m_brush = QBrush(Qt::red);

    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
}

void OpenGLWindow::paintGL()
{
    QPainter p(this);
    p.setWorldTransform(m_window_normalised_matrix.toTransform());

    QMatrix4x4 mvp = m_projection * m_view;
    p.setTransform(mvp.toTransform(), true);

    //Clear the screen
    p.fillRect(0, 0, 150, 200, m_brush);
}

void OpenGLWindow::resizeGL(int w, int h)
{
    m_window_normalised_matrix.setToIdentity();
    m_window_normalised_matrix.translate(w / 2.0, h / 2.0);
    m_window_normalised_matrix.scale(w / 2.0, -h / 2.0);

    m_window_painter_matrix.setToIdentity();
    m_window_painter_matrix.translate(w / 2.0, h / 2.0);

    m_projection.setToIdentity();
    m_projection.ortho(0.0f, 150.0f, 0.0f, 200.0f, 0.1f, 100.0f);
    //m_projection.ortho(0.0f, 100.0f, 0.0f, 200.0f, 0.1f, 100.0f);
    //m_projection.perspective(45.f, qreal(w) / qreal(h), 0.1f, 100.f);

}

void OpenGLWindow::keyPressEvent(QKeyEvent *e)
{

}
