//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CGL_Object.cpp
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
#include <cmath>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector/CVector3T.h>
#include <cgl/CGL_Object.h>

using namespace std;

//---------------------------------------------------------------------------
//
// Klasse:    CGL_Object
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_Object::Draw()
{
    glCallList(mDisplayListHandle);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Object
// Methode:   SetNormalVertex
//
//
//---------------------------------------------------------------------------

void CGL_Object::SetNormalVertex(CVector3<float>* Origin, CVector3<float>* cf)
{
    CVector3<float> norm; // (0,0,1);

    norm.SubtractVector(cf, Origin);
    norm.Normalize();
    glNormal3fv(norm.v());
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Object
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

CGL_Object::CGL_Object()
{
    mStatus = 0;
    mTexHandle = 0xFFFFFFFF;
    mDisplayListHandle = 0;
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Object
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

CGL_Object::~CGL_Object()
{
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Object
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------


void CGL_Object::MakeObject()
{
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Object
// Methode:		Init
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_Object::DeleteDisplayList()
{
    if (mDisplayListHandle != 0)
    {
        glDeleteLists(mDisplayListHandle, 1);
        mDisplayListHandle = 0;
    }
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Object
// Methode:		Init
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_Object::Init()
{
    mDisplayListHandle = glGenLists(1);
    glNewList(mDisplayListHandle, GL_COMPILE);
    MakeObject();
    glEndList();
}
