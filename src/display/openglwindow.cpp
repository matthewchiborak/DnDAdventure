#include "openglwindow.h"

#include "drawinformation.h"


OpenGLWindow::OpenGLWindow(ModelAbstract *model, SpriteFlyweightFactoryAbstract *factory)
    : AbstractView(model, factory)
{
    m_view.lookAt(QVector3D(0,0,0),
                  QVector3D(0,0,0),
                  QVector3D(0,1,0));

    QLinearGradient gradient(QPointF(-1,-1), QPointF(1,1));
    gradient.setColorAt(0, Qt::red);
    gradient.setColorAt(1, Qt::green);

    m_brush = QBrush(Qt::red);

    xOffset = 12.0f;
    yOffset = 7.0f;

    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
}

void OpenGLWindow::paintGL()
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    QPainter p(this);
    p.setWorldTransform(m_window_normalised_matrix.toTransform());

    QMatrix4x4 mvp = m_projection * m_view;
    p.setTransform(mvp.toTransform(), false);

    std::vector<DrawInformation> itemsToDraw;

    //based on the current stregy, draw the objects
    renderStrat->draw(&itemsToDraw);

    for(int i = 0; i < itemsToDraw.size(); i++)
    {
        SpriteFlyweight * focusFlyweight = spriteFactory->getFlyweight(itemsToDraw.at(i).key);

        focusFlyweight->generate();
        glEnable(GL_TEXTURE_2D);
        focusFlyweight->bind(0);
        glBegin(GL_QUADS);

        glTexCoord2f(0, 1);
        glVertex3f(itemsToDraw.at(i).x - xOffset,
                   itemsToDraw.at(i).y - yOffset, 0.0f);

        glTexCoord2f(1, 1);
        glVertex3f(itemsToDraw.at(i).x - xOffset + itemsToDraw.at(i).w,
                   itemsToDraw.at(i).y - yOffset, 0.0f);

        glTexCoord2f(1, 0);
        glVertex3f(itemsToDraw.at(i).x - xOffset + itemsToDraw.at(i).w,
                   itemsToDraw.at(i).y + itemsToDraw.at(i).h - yOffset, 0.0f);

        glTexCoord2f(0, 0);
        glVertex3f(itemsToDraw.at(i).x - xOffset,
                   itemsToDraw.at(i).y + itemsToDraw.at(i).h - yOffset, 0.0f);

        glEnd();

        glDisable(GL_TEXTURE_2D);
    }

}

void OpenGLWindow::resizeGL(int w, int h)
{
    m_window_normalised_matrix.setToIdentity();
    m_window_normalised_matrix.translate(w / 2.0, h / 2.0);
    m_window_normalised_matrix.scale(w / 2.0, -h / 2.0);

    m_window_painter_matrix.setToIdentity();
    m_window_painter_matrix.translate(w / 2.0, h / 2.0);

    m_projection.setToIdentity();
    m_projection.ortho(0.0f, 240.0f, 5.0f, 135.0f, 0.1f, 100.0f);
    //m_projection.ortho(0.0f, 320.0f, 0.0f, 180.0f, 0.1f, 100.0f);
    //m_projection.ortho(0.0f, 160.0f, 0.0f, 90.0f, 0.1f, 100.0f);
    //m_projection.ortho(0.0f, 150.0f, 0.0f, 200.0f, 0.1f, 100.0f);
    //m_projection.ortho(0.0f, 100.0f, 0.0f, 200.0f, 0.1f, 100.0f);
    //m_projection.perspective(45.f, qreal(w) / qreal(h), 0.1f, 100.f);

    //glOrtho(0.0f, 240.0f, 5.0f, 135.0f, 0.1f, 100.0f);
    //1600 900
    glOrtho( -12.f, 12.f, -6.75f, 6.75f, -1, 1);

    //glOrtho( -w/2.f, w/2.f, -h/2.f, h/2.f, -1, 1);

}

void OpenGLWindow::keyPressEvent(QKeyEvent *e)
{

}
