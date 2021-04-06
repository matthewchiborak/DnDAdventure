#include "spriteflyweight.h"

#include <QtDebug>

#include "stb_image.h"

SpriteFlyweight::SpriteFlyweight(std::string filepath)
{
    this->filepath = filepath;
    m_generated = false;
}

SpriteFlyweight::~SpriteFlyweight()
{
    glDeleteTextures(1, &texture);
}

void SpriteFlyweight::generate()
{
    if(m_generated)
        return;

    int width, height, numComponents;

    //Load texture data
    unsigned char* imageData = stbi_load(filepath.c_str(), &width, &height, &numComponents, 4);

    if (imageData == NULL)
    {
        qDebug() << "Load texture failed" << filepath.c_str();
    }

    //Generate space for the data in opengl
    //This is generate space for 1 texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    //Before specify texture data, can specify other things
    //These control texture wrapping. S is reading outside texture width, t is for height.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //If texture takes up more or less space than specified.
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //Fewer pixels than resolution
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //More

                                                                      //Send in data. Mitmapping using heigher resolution images the closer it is. But here its 0 so just use dfault
                                                                      //
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    //Free the texture data once no longer needed
    stbi_image_free(imageData);

    m_generated = true;
}

void SpriteFlyweight::bind(unsigned int unit)
{
    //Change what texture the program with working with
    //GL_TEXTURE unit is ordered sequentialy so can jsut add it
    //glActiveTexture(GL_TEXTURE0 + unit);

    //All future texture operations will use the texture that is stored there.
    glBindTexture(GL_TEXTURE_2D, texture);
}

