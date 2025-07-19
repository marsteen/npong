//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CPolylineObject.cpp
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <iostream>
#include <vector>

#include <cgl/CGL_include.h>
#include <pong/CPolylineObject.h>

using namespace std;

//---------------------------------------------------------------------------
//
// Klasse:		CPolylineObject
// Methode:		Draw
//
//
//---------------------------------------------------------------------------

void CPolylineObject::Draw() const
{
    //glColor4fv(mColor);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < mVerts.size(); i++)
    {
        glVertex2f(mVerts[i].x, mVerts[i].y);
    }
    glEnd();
}


//---------------------------------------------------------------------------
//
// Klasse:		CPolylineObject
// Methode:		Draw
//
//
//---------------------------------------------------------------------------

void CPolylineObject::DrawPoints() const
{
    glBegin(GL_POINTS);
    for (int i = 0; i < mVerts.size(); i++)
    {
        glVertex2f(mVerts[i].x, mVerts[i].y);
    }
    glEnd();
}


//---------------------------------------------------------------------------
//
// Klasse:		CPolylineObject
// Methode:		AddVertex
//
//
//---------------------------------------------------------------------------

void CPolylineObject::AddVertex(float x, float y)
{
    CVector2<float> v2;

    v2.x = x;
    v2.y = y;

    mVerts.push_back(v2);
}


//---------------------------------------------------------------------------
//
// Klasse:		CPolylineObject
// Methode:		GetMinMax
//
//
//---------------------------------------------------------------------------

void CPolylineObject::GetMinMax(CVector2<float>* Min, CVector2<float>* Max) const
{
    Min->x = 100000.0;
    Min->y = 100000.0;
    Max->x = -100000.0;
    Max->y = -100000.0;

    for (int i = 0; i < mVerts.size(); i++)
    {
        if (mVerts[i].x < Min->x)
        {
            Min->x = mVerts[i].x;
        }
        if (mVerts[i].y < Min->y)
        {
            Min->y = mVerts[i].y;
        }
        if (mVerts[i].x > Max->x)
        {
            Max->x = mVerts[i].x;
        }
        if (mVerts[i].y > Max->y)
        {
            Max->y = mVerts[i].y;
        }
    }
}


//---------------------------------------------------------------------------
//
// Klasse:		CPolylineObject
// Methode:		Translate
//
//
//---------------------------------------------------------------------------

void CPolylineObject::Translate(float xa, float ya)
{
    for (int i = 0; i < mVerts.size(); i++)
    {
        mVerts[i].x += xa;
        mVerts[i].y += ya;
    }
}


//---------------------------------------------------------------------------
//
// Klasse:		CPolylineObject
// Methode:		Scale
//
//
//---------------------------------------------------------------------------

void CPolylineObject::Scale(float f)
{
    for (int i = 0; i < mVerts.size(); i++)
    {
        mVerts[i].x *= f;
        mVerts[i].y *= f;
    }
}
