//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CGL_GLU_Object.cpp
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


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cgl/CGL_GLU_Object.h>

using namespace std;

static void CGL_GLU_ObjectError()
{
    cout << "CGL_GLU_Object Error ***" << endl;
}


void CGL_GLU_Object::SetParams(int Orient, int DrawStyle, int Normal, bool TextCoord)
{
    gluQuadricOrientation(mQuadObj, Orient);
    gluQuadricDrawStyle(mQuadObj, DrawStyle);
    gluQuadricNormals(mQuadObj, Normal);
    //gluQuadricCallback(mQuadObj, GLU_ERROR, CGL_GLU_ObjectError);
    gluQuadricTexture(mQuadObj, TextCoord);
}
