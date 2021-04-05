// #include <QOpenGLWidget>
#include <QtOpenGL>
#include <QInputEvent>
#include <QColor>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <math.h>

void fghCircleTable(double **sint,double **cost, const int n);
void glutSolidCylinder(GLdouble radius, GLdouble height, GLint slices, GLint stacks);
void glutSolidSphere(GLdouble radius, GLint slices, GLint stacks);
void glutSolidCube(GLdouble size);
void glutSolidBox(GLdouble length, GLdouble width, GLdouble height);
void glutSolidTorus(GLdouble dInnerRadius, GLdouble dOuterRadius, GLint nSides, GLint nRings);
void glutSolidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
void glutWireCylinder(GLdouble radius, GLdouble height, GLint slices, GLint stacks);
void glutWireSphere(GLdouble radius, GLint slices, GLint stacks);
void glutWireCube(GLdouble size);
void glutWireTorus(GLdouble dInnerRadius, GLdouble dOuterRadius, GLint nSides, GLint nRings);
void glutWireCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
void glutLine3D(GLdouble x1, GLdouble y1, GLdouble z1, GLdouble x2, GLdouble y2, GLdouble z2);
void glutQuad3D(GLdouble x1, GLdouble y1, GLdouble z1, GLdouble x2, GLdouble y2, GLdouble z2,
                 GLdouble x3, GLdouble y3, GLdouble z3, GLdouble x4, GLdouble y4, GLdouble z4);
void glutTri3D(GLdouble x1, GLdouble y1, GLdouble z1, GLdouble x2, GLdouble y2, GLdouble z2,
                 GLdouble x3, GLdouble y3, GLdouble z3);
void glutPinX(GLdouble size);
void glutPinY(GLdouble size);
void glutPin(GLdouble size);
void glutRoller(GLdouble size);
void glutRollerX(GLdouble size);
void glutRollerY(GLdouble size);
void glutFixed(GLdouble size);
void glutBase(GLdouble size);
double max(double a, double b, double c);
double angle2d(double x1, double y1, double x2, double y2);
