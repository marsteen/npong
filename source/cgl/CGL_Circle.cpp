//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CGL_Circle.cpp
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <vector/CVector3T.h>
#include <cgl/CGL_Object.h>
#include <cgl/CGL_Circle.h>


using namespace std;

#if 1
void CGL_Circle::MakeObject()
{
    CVector3<float> CirclePoint;
    CVector3<float> Normal;
    float Alpha = 0;
    float AlphaPlus = DEG_TO_RAD(360.0 / mSegments);

    CirclePoint.x = mRadius + mOrigin.x;
    CirclePoint.y = 0;
    CirclePoint.z = mOrigin.z;

    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= mSegments; i++)
    {
        CirclePoint.x = (cos(Alpha) * mRadius) + mOrigin.x;
        CirclePoint.y = (sin(Alpha) * mRadius) + mOrigin.y;

        glVertex3fv(CirclePoint.v());
        Alpha += AlphaPlus;
    }
    glEnd();

    glPopMatrix();
}


#endif
