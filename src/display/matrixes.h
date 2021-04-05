#ifndef MATRIXES_H
#define MATRIXES_H

#include <QString>

class Matrix3x1
{
public:
    Matrix3x1()
    {
        m_a = 0;
        m_b = 0;
        m_c = 0;
    }
    Matrix3x1(float a, float b, float c)
    {
        m_a = a;
        m_b = b;
        m_c = c;
    }

    float m_a;
    float m_b;
    float m_c;
};

class Matrix3x3
{
public:
    Matrix3x3()
    {
        m_r1c1 = 0;
        m_r1c2 = 0;
        m_r1c3 = 0;
        m_r2c1 = 0;
        m_r2c2 = 0;
        m_r2c3 = 0;
        m_r3c1 = 0;
        m_r3c2 = 0;
        m_r3c3 = 0;
    }
    Matrix3x3(float r1c1, float r1c2, float r1c3, float r2c1, float r2c2, float r2c3, float r3c1, float r3c2, float r3c3)
    {
        m_r1c1 = r1c1;
        m_r1c2 = r1c2;
        m_r1c3 = r1c3;
        m_r2c1 = r2c1;
        m_r2c2 = r2c2;
        m_r2c3 = r2c3;
        m_r3c1 = r3c1;
        m_r3c2 = r3c2;
        m_r3c3 = r3c3;
    }

    float m_r1c1;
    float m_r1c2;
    float m_r1c3;
    float m_r2c1;
    float m_r2c2;
    float m_r2c3;
    float m_r3c1;
    float m_r3c2;
    float m_r3c3;

    Matrix3x1 apply3by1Matix(Matrix3x1 point)
    {
        Matrix3x1 resultMat(0,0,0);
        resultMat.m_a = m_r1c1 * point.m_a +
                m_r1c2 * point.m_b +
                m_r1c3 * point.m_c;
        resultMat.m_b = m_r2c1 * point.m_a +
                m_r2c2 * point.m_b +
                m_r2c3 * point.m_c;
        resultMat.m_c = m_r3c1 * point.m_a +
                m_r3c2 * point.m_b +
                m_r3c3 * point.m_c;

        return resultMat;
    }
};



#endif // MATRIXES_H

