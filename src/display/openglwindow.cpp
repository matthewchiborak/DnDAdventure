#include "openglwindow.h"

#include "drawinformation.h"




OpenGLWindow::OpenGLWindow(ModelAbstract *model, std::queue<int> * keyboardEventQueue, SpriteFlyweightFactoryAbstract *factory)
    : AbstractView(model, keyboardEventQueue, factory)
{
    m_view.lookAt(QVector3D(0,0,0),
                  QVector3D(0,0,0),
                  QVector3D(0,1,0));

    QLinearGradient gradient(QPointF(-1,-1), QPointF(1,1));
    gradient.setColorAt(0, Qt::red);
    gradient.setColorAt(1, Qt::green);

    m_brush = QBrush(Qt::red);
    font.setPixelSize(48);

    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));

    windowWidth = 1600;
    windowHeight = 900;

//    if (FT_Init_FreeType(&ft))
//    {
//        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
//    }


//    if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
//    {
//        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
//    }

    //FT_Set_Pixel_Sizes(face, 0, 48);
}

void OpenGLWindow::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    QPainter p(this);
    p.setFont(font);
    p.setBrush(m_brush);
    //p.setWorldTransform(m_window_normalised_matrix.toTransform());

    QMatrix4x4 mvp = m_projection * m_view;
    //p.setTransform(mvp.toTransform(), false);

    std::vector<DrawInformation> itemsToDraw;
    float xOffset;// = 12.0f;
    float yOffset;// = 7.0f;

    //based on the current stregy, draw the objects
    renderStrat->draw(&itemsToDraw, &xOffset, &yOffset);

    for(int i = 0; i < itemsToDraw.size(); i++)
    {
        //Text items
        if(itemsToDraw.at(i).text != "")
        {
            if(!itemsToDraw.at(i).isLeftAlign)
            {
                font.setPixelSize(itemsToDraw.at(i).fontSize);
                p.setFont(font);
                p.drawText((itemsToDraw.at(i).x),
                           (itemsToDraw.at(i).y),
                           (itemsToDraw.at(i).w),
                           (itemsToDraw.at(i).h),
                           Qt::AlignCenter, QString::fromStdString(itemsToDraw.at(i).text));
            }
            else
            {
                font.setPixelSize(itemsToDraw.at(i).fontSize);
                p.setFont(font);
                p.drawText((itemsToDraw.at(i).x),
                           (itemsToDraw.at(i).y),
                           (itemsToDraw.at(i).w),
                           (itemsToDraw.at(i).h),
                           Qt::AlignLeft, QString::fromStdString(itemsToDraw.at(i).text));
            }
            continue;
        }

        SpriteFlyweight * focusFlyweight = spriteFactory->getFlyweight(itemsToDraw.at(i).key);

        focusFlyweight->generate();
        glEnable(GL_TEXTURE_2D);
        focusFlyweight->bind(0);
        glBegin(GL_QUADS);

        if(itemsToDraw.at(i).isRelativeToWorld)
        {
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
        }
        else
        {
            glTexCoord2f(0, 1);
            glVertex3f(itemsToDraw.at(i).x/100.f,
                       ((itemsToDraw.at(i).y)/100.f), 0.0f);

            glTexCoord2f(1, 1);
            glVertex3f((itemsToDraw.at(i).x + itemsToDraw.at(i).w)/100.f,
                       ((itemsToDraw.at(i).y)/100.f), 0.0f);

            glTexCoord2f(1, 0);
            glVertex3f((itemsToDraw.at(i).x + itemsToDraw.at(i).w)/100.f,
                       ((itemsToDraw.at(i).y + itemsToDraw.at(i).h)/100.f), 0.0f);

            glTexCoord2f(0, 0);
            glVertex3f((itemsToDraw.at(i).x)/100.f,
                       ((itemsToDraw.at(i).y + itemsToDraw.at(i).h)/100.f), 0.0f);
        }

        glEnd();

        glDisable(GL_TEXTURE_2D);
    }
}

void OpenGLWindow::resizeGL(int w, int h)
{
    windowWidth = w;
    windowHeight = h;

    m_window_normalised_matrix.setToIdentity();
    m_window_normalised_matrix.translate(w / 2.0, h / 2.0);
    m_window_normalised_matrix.scale(w / 2.0, -h / 2.0);

    m_window_painter_matrix.setToIdentity();
    m_window_painter_matrix.translate(w / 2.0, h / 2.0);

    m_projection.setToIdentity();
    m_projection.ortho(-7.5f, 8.5f, -4.f, 5.f, -1.f, 1.f);
    //m_projection.ortho(0.0f, 240.0f, 5.0f, 135.0f, 0.1f, 100.0f);
    //m_projection.ortho(0.0f, 320.0f, 0.0f, 180.0f, 0.1f, 100.0f);
    //m_projection.ortho(0.0f, 160.0f, 0.0f, 90.0f, 0.1f, 100.0f);
    //m_projection.ortho(0.0f, 150.0f, 0.0f, 200.0f, 0.1f, 100.0f);
    //m_projection.ortho(0.0f, 100.0f, 0.0f, 200.0f, 0.1f, 100.0f);
    //m_projection.perspective(45.f, qreal(w) / qreal(h), 0.1f, 100.f);

    //glOrtho(0.0f, 240.0f, 5.0f, 135.0f, 0.1f, 100.0f);
    //1600 900
    //glOrtho( -12.f, 12.f, -6.75f, 6.75f, -1, 1);
    //glOrtho( -8.25f, 8.25f, -4.640625f, 4.640625f, -1, 1);
    glOrtho(-7.5f, 8.5f, -4.f, 5.f, -1, 1);

    //glOrtho( -w/2.f, w/2.f, -h/2.f, h/2.f, -1, 1);

}

void OpenGLWindow::keyPressEvent(QKeyEvent *e)
{
    if(keyboardEventQueue->empty())
        keyboardEventQueue->push(e->key());
}

void OpenGLWindow::keyReleaseEvent(QKeyEvent *e)
{
    while(!keyboardEventQueue->empty())
        keyboardEventQueue->pop();
}

int OpenGLWindow::convertXLocationToPixels(int value)
{
    return value * 100;
}

int OpenGLWindow::convertYLocationToPixels(int value)
{
    return windowHeight - (value * 100);
}


