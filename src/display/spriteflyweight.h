#ifndef SPRITEFLYWEIGHT_H
#define SPRITEFLYWEIGHT_H

#include <QOpenGLTexture>
#include <iostream>
#include <QPixmap>
#include <QBrush>

class SpriteFlyweight
{
public:
    SpriteFlyweight(std::string filepath);
    ~SpriteFlyweight();

    void generate();
    void bind(unsigned int unit);

protected:
    GLuint texture;
    std::string filepath;
    bool m_generated;
};

#endif // SPRITEFLYWEIGHT_H
