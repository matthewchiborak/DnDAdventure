#include "fglut.h"

#ifndef M_PI
#    define  M_PI  3.14159265358979323846
#endif

void fghCircleTable(double **sint,double **cost, const int n)
{
    int i;

    /* Table size, the sign of n flips the circle direction */

    const int size = abs(n);

    /* Determine the angle between samples */

    const double angle = 2*M_PI/(double)( ( n == 0 ) ? 1 : n );

    /* Allocate memory for n samples, plus duplicate of first entry at the end */

    *sint = (double *) calloc(sizeof(double), size+1);
    *cost = (double *) calloc(sizeof(double), size+1);

    /* Bail out if memory allocation fails, fgError never returns */

    if (!(*sint) || !(*cost))
    {
        free(*sint);
        free(*cost);
        //fgError("Failed to allocate memory in fghCircleTable");
    }

    /* Compute cos and sin around the circle */

    (*sint)[0] = 0.0;
    (*cost)[0] = 1.0;

    for (i=1; i<size; i++)
    {
        (*sint)[i] = sin(angle*i);
        (*cost)[i] = cos(angle*i);
    }

    /* Last sample is duplicate of the first */

    (*sint)[size] = (*sint)[0];
    (*cost)[size] = (*cost)[0];
}

void glutSolidSphere(GLdouble radius, GLint slices, GLint stacks)
{
    int i,j;

    /* Adjust z and radius as stacks are drawn. */

    double z0,z1;
    double r0,r1;

    /* Pre-computed circle */

    double *sint1,*cost1;
    double *sint2,*cost2;

   // FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidSphere" );

    fghCircleTable(&sint1,&cost1,-slices);
    fghCircleTable(&sint2,&cost2,stacks*2);

    /* The top stack is covered with a triangle fan */

    z0 = 1.0;
    z1 = cost2[(stacks>0)?1:0];
    r0 = 0.0;
    r1 = sint2[(stacks>0)?1:0];

    glBegin(GL_TRIANGLE_FAN);

        glNormal3d(0,0,1);
        glVertex3d(0,0,radius);

        for (j=slices; j>=0; j--)
        {
            glNormal3d(cost1[j]*r1,        sint1[j]*r1,        z1       );
            glVertex3d(cost1[j]*r1*radius, sint1[j]*r1*radius, z1*radius);
        }

    glEnd();

    /* Cover each stack with a quad strip, except the top and bottom stacks */

    for( i=1; i<stacks-1; i++ )
    {
        z0 = z1; z1 = cost2[i+1];
        r0 = r1; r1 = sint2[i+1];

        glBegin(GL_QUAD_STRIP);

            for(j=0; j<=slices; j++)
            {
                glNormal3d(cost1[j]*r1,        sint1[j]*r1,        z1       );
                glVertex3d(cost1[j]*r1*radius, sint1[j]*r1*radius, z1*radius);
                glNormal3d(cost1[j]*r0,        sint1[j]*r0,        z0       );
                glVertex3d(cost1[j]*r0*radius, sint1[j]*r0*radius, z0*radius);
            }

        glEnd();
    }

    /* The bottom stack is covered with a triangle fan */

    z0 = z1;
    r0 = r1;

    glBegin(GL_TRIANGLE_FAN);

        glNormal3d(0,0,-1);
        glVertex3d(0,0,-radius);

        for (j=0; j<=slices; j++)
        {
            glNormal3d(cost1[j]*r0,        sint1[j]*r0,        z0       );
            glVertex3d(cost1[j]*r0*radius, sint1[j]*r0*radius, z0*radius);
        }

    glEnd();

    /* Release sin and cos tables */

    free(sint1);
    free(cost1);
    free(sint2);
    free(cost2);
}

void glutSolidCube( GLdouble dSize )
{
    double size = dSize * 0.5;

   // FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidCube" );

#   define V(a,b,c) glVertex3d( a size, b size, c size );
#   define N(a,b,c) glNormal3d( a, b, c );

    /* PWO: Again, I dared to convert the code to use macros... */
    glBegin( GL_QUADS );
        N( 1.0, 0.0, 0.0); V(+,-,+); V(+,-,-); V(+,+,-); V(+,+,+);
        N( 0.0, 1.0, 0.0); V(+,+,+); V(+,+,-); V(-,+,-); V(-,+,+);
        N( 0.0, 0.0, 1.0); V(+,+,+); V(-,+,+); V(-,-,+); V(+,-,+);
        N(-1.0, 0.0, 0.0); V(-,-,+); V(-,+,+); V(-,+,-); V(-,-,-);
        N( 0.0,-1.0, 0.0); V(-,-,+); V(-,-,-); V(+,-,-); V(+,-,+);
        N( 0.0, 0.0,-1.0); V(-,-,-); V(-,+,-); V(+,+,-); V(+,-,-);
    glEnd();

#   undef V
#   undef N
}

void glutSolidBox( GLdouble length, GLdouble width, GLdouble height)
{
    double xs = length * 0.5;
    double ys = width * 0.5;
    double zs = height * 0.5;

#   define V(a,b,c) glVertex3d( a xs, b ys, c zs);
#   define N(a,b,c) glNormal3d( a, b, c );

    glBegin( GL_QUADS );
    N( 1.0, 0.0, 0.0); V(+,-,+); V(+,-,-); V(+,+,-); V(+,+,+);
    N( 0.0, 1.0, 0.0); V(+,+,+); V(+,+,-); V(-,+,-); V(-,+,+);
    N( 0.0, 0.0, 1.0); V(+,+,+); V(-,+,+); V(-,-,+); V(+,-,+);
    N(-1.0, 0.0, 0.0); V(-,-,+); V(-,+,+); V(-,+,-); V(-,-,-);
    N( 0.0,-1.0, 0.0); V(-,-,+); V(-,-,-); V(+,-,-); V(+,-,+);
    N( 0.0, 0.0,-1.0); V(-,-,-); V(-,+,-); V(+,+,-); V(+,-,-);
    glEnd();

#   undef V
#   undef N

}
void glutSolidCylinder(GLdouble radius, GLdouble height, GLint slices, GLint stacks)
{
    int i,j;

    /* Step in z and radius as stacks are drawn. */

    double z0,z1;
    const double zStep = height / ( ( stacks > 0 ) ? stacks : 1 );

    /* Pre-computed circle */

    double *sint,*cost;

    // FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidCylinder" );

    fghCircleTable(&sint,&cost,-slices);

    /* Cover the base and top */

    glBegin(GL_TRIANGLE_FAN);
        glNormal3d(0.0, 0.0, -1.0 );
        glVertex3d(0.0, 0.0,  0.0 );
        for (j=0; j<=slices; j++)
          glVertex3d(cost[j]*radius, sint[j]*radius, 0.0);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        glNormal3d(0.0, 0.0, 1.0   );
        glVertex3d(0.0, 0.0, height);
        for (j=slices; j>=0; j--)
          glVertex3d(cost[j]*radius, sint[j]*radius, height);
    glEnd();

    /* Do the stacks */

    z0 = 0.0;
    z1 = zStep;

    for (i=1; i<=stacks; i++)
    {
        if (i==stacks)
            z1 = height;

        glBegin(GL_QUAD_STRIP);
            for (j=0; j<=slices; j++ )
            {
                glNormal3d(cost[j],        sint[j],        0.0 );
                glVertex3d(cost[j]*radius, sint[j]*radius, z0  );
                glVertex3d(cost[j]*radius, sint[j]*radius, z1  );
            }
        glEnd();

        z0 = z1; z1 += zStep;
    }

    /* Release sin and cos tables */

    free(sint);
    free(cost);
}

void glutSolidTorus( GLdouble dInnerRadius, GLdouble dOuterRadius, GLint nSides, GLint nRings )
{
  double  iradius = dInnerRadius, oradius = dOuterRadius, phi, psi, dpsi, dphi;
  double *vertex, *normal;
  int    i, j;
  double spsi, cpsi, sphi, cphi ;

//  FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidTorus" );

  if ( nSides < 1 ) nSides = 1;
  if ( nRings < 1 ) nRings = 1;

  /* Increment the number of sides and rings to allow for one more point than surface */
  nSides ++ ;
  nRings ++ ;

  /* Allocate the vertices array */
  vertex = (double *)calloc( sizeof(double), 3 * nSides * nRings );
  normal = (double *)calloc( sizeof(double), 3 * nSides * nRings );

  glPushMatrix();

  dpsi =  2.0 * M_PI / (double)(nRings - 1) ;
  dphi = -2.0 * M_PI / (double)(nSides - 1) ;
  psi  = 0.0;

  for( j=0; j<nRings; j++ )
  {
    cpsi = cos ( psi ) ;
    spsi = sin ( psi ) ;
    phi = 0.0;

    for( i=0; i<nSides; i++ )
    {
      int offset = 3 * ( j * nSides + i ) ;
      cphi = cos ( phi ) ;
      sphi = sin ( phi ) ;
      *(vertex + offset + 0) = cpsi * ( oradius + cphi * iradius ) ;
      *(vertex + offset + 1) = spsi * ( oradius + cphi * iradius ) ;
      *(vertex + offset + 2) =                    sphi * iradius  ;
      *(normal + offset + 0) = cpsi * cphi ;
      *(normal + offset + 1) = spsi * cphi ;
      *(normal + offset + 2) =        sphi ;
      phi += dphi;
    }

    psi += dpsi;
  }

    glBegin( GL_QUADS );
  for( i=0; i<nSides-1; i++ )
  {
    for( j=0; j<nRings-1; j++ )
    {
      int offset = 3 * ( j * nSides + i ) ;
      glNormal3dv( normal + offset );
      glVertex3dv( vertex + offset );
      glNormal3dv( normal + offset + 3 );
      glVertex3dv( vertex + offset + 3 );
      glNormal3dv( normal + offset + 3 * nSides + 3 );
      glVertex3dv( vertex + offset + 3 * nSides + 3 );
      glNormal3dv( normal + offset + 3 * nSides );
      glVertex3dv( vertex + offset + 3 * nSides );
    }
  }

  glEnd();

  free ( vertex ) ;
  free ( normal ) ;
  glPopMatrix();
}

void glutSolidCone( GLdouble base, GLdouble height, GLint slices, GLint stacks )
{
    int i,j;

    /* Step in z and radius as stacks are drawn. */

    double z0,z1;
    double r0,r1;

    const double zStep = height / ( ( stacks > 0 ) ? stacks : 1 );
    const double rStep = base / ( ( stacks > 0 ) ? stacks : 1 );

    /* Scaling factors for vertex normals */

    const double cosn = ( height / sqrt ( height * height + base * base ));
    const double sinn = ( base   / sqrt ( height * height + base * base ));

    /* Pre-computed circle */

    double *sint,*cost;

//    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidCone" );

    fghCircleTable(&sint,&cost,-slices);

    /* Cover the circular base with a triangle fan... */

    z0 = 0.0;
    z1 = zStep;

    r0 = base;
    r1 = r0 - rStep;

    glBegin(GL_TRIANGLE_FAN);

        glNormal3d(0.0,0.0,-1.0);
        glVertex3d(0.0,0.0, z0 );

        for (j=0; j<=slices; j++)
            glVertex3d(cost[j]*r0, sint[j]*r0, z0);

    glEnd();

    /* Cover each stack with a quad strip, except the top stack */

    for( i=0; i<stacks-1; i++ )
    {
        glBegin(GL_QUAD_STRIP);

            for(j=0; j<=slices; j++)
            {
                glNormal3d(cost[j]*cosn, sint[j]*cosn, sinn);
                glVertex3d(cost[j]*r0,   sint[j]*r0,   z0  );
                glVertex3d(cost[j]*r1,   sint[j]*r1,   z1  );
            }

            z0 = z1; z1 += zStep;
            r0 = r1; r1 -= rStep;

        glEnd();
    }

    /* The top stack is covered with individual triangles */

    glBegin(GL_TRIANGLES);

        glNormal3d(cost[0]*cosn, sint[0]*cosn, sinn);

        for (j=0; j<slices; j++)
        {
            glVertex3d(cost[j+0]*r0,   sint[j+0]*r0,   z0    );
            glVertex3d(0,              0,              height);
            glNormal3d(cost[j+1]*cosn, sint[j+1]*cosn, sinn  );
            glVertex3d(cost[j+1]*r0,   sint[j+1]*r0,   z0    );
        }

    glEnd();

    /* Release sin and cos tables */

    free(sint);
    free(cost);
}

void glutWireCube( GLdouble dSize )
{
    double size = dSize * 0.5;

  //  FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutWireCube" );

#   define V(a,b,c) glVertex3d( a size, b size, c size );
#   define N(a,b,c) glNormal3d( a, b, c );

    /* PWO: I dared to convert the code to use macros... */
    glBegin( GL_LINE_LOOP ); N( 1.0, 0.0, 0.0); V(+,-,+); V(+,-,-); V(+,+,-); V(+,+,+); glEnd();
    glBegin( GL_LINE_LOOP ); N( 0.0, 1.0, 0.0); V(+,+,+); V(+,+,-); V(-,+,-); V(-,+,+); glEnd();
    glBegin( GL_LINE_LOOP ); N( 0.0, 0.0, 1.0); V(+,+,+); V(-,+,+); V(-,-,+); V(+,-,+); glEnd();
    glBegin( GL_LINE_LOOP ); N(-1.0, 0.0, 0.0); V(-,-,+); V(-,+,+); V(-,+,-); V(-,-,-); glEnd();
    glBegin( GL_LINE_LOOP ); N( 0.0,-1.0, 0.0); V(-,-,+); V(-,-,-); V(+,-,-); V(+,-,+); glEnd();
    glBegin( GL_LINE_LOOP ); N( 0.0, 0.0,-1.0); V(-,-,-); V(-,+,-); V(+,+,-); V(+,-,-); glEnd();

#   undef V
#   undef N
}

void glutWireCone( GLdouble base, GLdouble height, GLint slices, GLint stacks)
{
    int i,j;

    /* Step in z and radius as stacks are drawn. */

    double z = 0.0;
    double r = base;

    const double zStep = height / ( ( stacks > 0 ) ? stacks : 1 );
    const double rStep = base / ( ( stacks > 0 ) ? stacks : 1 );

    /* Scaling factors for vertex normals */

    const double cosn = ( height / sqrt ( height * height + base * base ));
    const double sinn = ( base   / sqrt ( height * height + base * base ));

    /* Pre-computed circle */

    double *sint,*cost;

//    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutWireCone" );

    fghCircleTable(&sint,&cost,-slices);

    /* Draw the stacks... */

    for (i=0; i<stacks; i++)
    {
        glBegin(GL_LINE_LOOP);

            for( j=0; j<slices; j++ )
            {
                glNormal3d(cost[j]*sinn, sint[j]*sinn, cosn);
                glVertex3d(cost[j]*r,    sint[j]*r,    z   );
            }

        glEnd();

        z += zStep;
        r -= rStep;
    }

    /* Draw the slices */

    r = base;

    glBegin(GL_LINES);

        for (j=0; j<slices; j++)
        {
            glNormal3d(cost[j]*cosn, sint[j]*cosn, sinn  );
            glVertex3d(cost[j]*r,    sint[j]*r,    0.0   );
            glVertex3d(0.0,          0.0,          height);
        }

    glEnd();

    /* Release sin and cos tables */

    free(sint);
    free(cost);
}
void glutWireCylinder(GLdouble radius, GLdouble height, GLint slices, GLint stacks)
{
    int i,j;

    /* Step in z and radius as stacks are drawn. */

          double z = 0.0;
    const double zStep = height / ( ( stacks > 0 ) ? stacks : 1 );

    /* Pre-computed circle */

    double *sint,*cost;

//    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutWireCylinder" );

    fghCircleTable(&sint,&cost,-slices);

    /* Draw the stacks... */

    for (i=0; i<=stacks; i++)
    {
        if (i==stacks)
            z = height;

        glBegin(GL_LINE_LOOP);

            for( j=0; j<slices; j++ )
            {
                glNormal3d(cost[j],        sint[j],        0.0);
                glVertex3d(cost[j]*radius, sint[j]*radius, z  );
            }

        glEnd();

        z += zStep;
    }

    /* Draw the slices */

    glBegin(GL_LINES);

        for (j=0; j<slices; j++)
        {
            glNormal3d(cost[j],        sint[j],        0.0   );
            glVertex3d(cost[j]*radius, sint[j]*radius, 0.0   );
            glVertex3d(cost[j]*radius, sint[j]*radius, height);
        }

    glEnd();

    /* Release sin and cos tables */

    free(sint);
    free(cost);
}


void glutWireTorus( GLdouble dInnerRadius, GLdouble dOuterRadius, GLint nSides, GLint nRings )
{
  double  iradius = dInnerRadius, oradius = dOuterRadius, phi, psi, dpsi, dphi;
  double *vertex, *normal;
  int    i, j;
  double spsi, cpsi, sphi, cphi ;

//  FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutWireTorus" );

  if ( nSides < 1 ) nSides = 1;
  if ( nRings < 1 ) nRings = 1;

  /* Allocate the vertices array */
  vertex = (double *)calloc( sizeof(double), 3 * nSides * nRings );
  normal = (double *)calloc( sizeof(double), 3 * nSides * nRings );

  glPushMatrix();

  dpsi =  2.0 * M_PI / (double)nRings ;
  dphi = -2.0 * M_PI / (double)nSides ;
  psi  = 0.0;

  for( j=0; j<nRings; j++ )
  {
    cpsi = cos ( psi ) ;
    spsi = sin ( psi ) ;
    phi = 0.0;

    for( i=0; i<nSides; i++ )
    {
      int offset = 3 * ( j * nSides + i ) ;
      cphi = cos ( phi ) ;
      sphi = sin ( phi ) ;
      *(vertex + offset + 0) = cpsi * ( oradius + cphi * iradius ) ;
      *(vertex + offset + 1) = spsi * ( oradius + cphi * iradius ) ;
      *(vertex + offset + 2) =                    sphi * iradius  ;
      *(normal + offset + 0) = cpsi * cphi ;
      *(normal + offset + 1) = spsi * cphi ;
      *(normal + offset + 2) =        sphi ;
      phi += dphi;
    }

    psi += dpsi;
  }

  for( i=0; i<nSides; i++ )
  {
    glBegin( GL_LINE_LOOP );

    for( j=0; j<nRings; j++ )
    {
      int offset = 3 * ( j * nSides + i ) ;
      glNormal3dv( normal + offset );
      glVertex3dv( vertex + offset );
    }

    glEnd();
  }

  for( j=0; j<nRings; j++ )
  {
    glBegin(GL_LINE_LOOP);

    for( i=0; i<nSides; i++ )
    {
      int offset = 3 * ( j * nSides + i ) ;
      glNormal3dv( normal + offset );
      glVertex3dv( vertex + offset );
    }

    glEnd();
  }

  free ( vertex ) ;
  free ( normal ) ;
  glPopMatrix();
}

void glutWireSphere(GLdouble radius, GLint slices, GLint stacks)
{
    int i,j;

    /* Adjust z and radius as stacks and slices are drawn. */

    double r;
    double x,y,z;

    /* Pre-computed circle */

    double *sint1,*cost1;
    double *sint2,*cost2;

//    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutWireSphere" );

    fghCircleTable(&sint1,&cost1,-slices  );
    fghCircleTable(&sint2,&cost2, stacks*2);

    /* Draw a line loop for each stack */

    for (i=1; i<stacks; i++)
    {
        z = cost2[i];
        r = sint2[i];

        glBegin(GL_LINE_LOOP);

            for(j=0; j<=slices; j++)
            {
                x = cost1[j];
                y = sint1[j];

                glNormal3d(x,y,z);
                glVertex3d(x*r*radius,y*r*radius,z*radius);
            }

        glEnd();
    }

    /* Draw a line loop for each slice */

    for (i=0; i<slices; i++)
    {
        glBegin(GL_LINE_STRIP);

            for(j=0; j<=stacks; j++)
            {
                x = cost1[i]*sint2[j];
                y = sint1[i]*sint2[j];
                z = cost2[j];

                glNormal3d(x,y,z);
                glVertex3d(x*radius,y*radius,z*radius);
            }

        glEnd();
    }

    /* Release sin and cos tables */

    free(sint1);
    free(cost1);
    free(sint2);
    free(cost2);
}
void glutLine3D( GLdouble x1, GLdouble y1, GLdouble z1, GLdouble x2, GLdouble y2, GLdouble z2)
{
    glBegin(GL_LINES);
        glNormal3d(0.0, 0.0, 1.0);
        glVertex3d(x1, y1, z1);
        glVertex3d(x2, y2, z2);
    glEnd();
}
void glutQuad3D( GLdouble x1, GLdouble y1, GLdouble z1, GLdouble x2, GLdouble y2, GLdouble z2,
                 GLdouble x3, GLdouble y3, GLdouble z3, GLdouble x4, GLdouble y4, GLdouble z4)
{
    double n1, n2, n3, nn, dx1, dx2, dy1, dy2, dz1, dz2;
    dx1 = x2 - x1;
    dx2 = x3 - x1;
    dy1 = y2 - y1;
    dy2 = y3 - y1;
    dz1 = z2 - z1;
    dz2 = z3 - z1;
    n1 = (dy1 * dz2) - (dy2 * dz1);
    n2 = (dx2 * dz1) - (dx1 * dz2);
    n3 = (dx1 * dy2) - (dx2 * dy1);
    nn = pow(((n1 * n1) + (n2 * n2) + (n3 * n3)), 0.5);
    n1 /= nn;
    n2 /= nn;
    n3 /= nn;

    glBegin(GL_QUADS);
        glNormal3d(n1, n2, n3);
        glVertex3d(x1, y1, z1);
        glVertex3d(x2, y2, z2);
        glVertex3d(x3, y3, z3);
        glVertex3d(x4, y4, z4);
    glEnd();
}
void glutTri3D( GLdouble x1, GLdouble y1, GLdouble z1, GLdouble x2, GLdouble y2, GLdouble z2,
                 GLdouble x3, GLdouble y3, GLdouble z3)
{
    double n1, n2, n3, nn, dx1, dx2, dy1, dy2, dz1, dz2;
    dx1 = x2 - x1;
    dx2 = x3 - x1;
    dy1 = y2 - y1;
    dy2 = y3 - y1;
    dz1 = z2 - z1;
    dz2 = z3 - z1;
    n1 = (dy1 * dz2) - (dy2 * dz1);
    n2 = (dx2 * dz1) - (dx1 * dz2);
    n3 = (dx1 * dy2) - (dx2 * dy1);
    nn = pow(((n1 * n1) + (n2 * n2) + (n3 * n3)), 0.5);
    n1 /= nn;
    n2 /= nn;
    n3 /= nn;

    glBegin(GL_TRIANGLES);
        glNormal3d(n1, n2, n3);
        glVertex3d(x1, y1, z1);
        glVertex3d(x2, y2, z2);
        glVertex3d(x3, y3, z3);
    glEnd();
}
void glutPin(GLdouble size)
{
    glutSolidCone(size, 2.0f*size, 32, 32);
}
void glutPinX(GLdouble size)
{
    glutTri3D(-0.5f * size, 0, 0, 0.5f*size, 0, 0, 0, 0, 1.414f * size);
}
void glutPinY(GLdouble size)
{
    glutTri3D(0, -0.5f * size,  0, 0, 0.5f*size, 0, 0, 0, 1.414f * size);
}
void glutRoller(GLdouble size)
{
    glutSolidSphere(size, 32, 32);
}
void glutRollerX(GLdouble size)
{
    glRotatef(90, 1, 0, 0);
    glutSolidCylinder(size, 0, 32, 1);
    glRotatef(-90, 1, 0, 0);
}
void glutRollerY(GLdouble size)
{
    glRotatef(90, 0, 1, 0);
    glutSolidCylinder(size, 0, 32, 1);
    glRotatef(-90, 0, 1, 0);
}
void glutBase(GLdouble size)
{
    glutSolidCylinder(size, 0, 32, 1);
}
void glutFixed(GLdouble size)
{
    glutSolidBox(size, 0, size);
    glutSolidBox(0, size, size);
}
double max(double a, double b, double c)
{
    double maxa = a;
    if (maxa < b)
    {
        maxa = b;
    }
    if (maxa < c)
    {
        maxa = c;
    }
    return maxa;
}
double angle2d(double x1, double y1, double x2, double y2)
{
    double t1, t2, angle;

    t1 = atan2(y1, x1);
    t2 = atan2(y2, x2);
    angle = t2 - t1;

    while (angle>M_PI)
    {
        angle -= (2.0*M_PI);
    }
    while (angle < -M_PI)
    {
        angle += (2.0*M_PI);
    }
    return angle;
}
