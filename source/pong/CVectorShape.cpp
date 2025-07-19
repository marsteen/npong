//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CVectorShape.cpp
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <iostream>
#include <fstream>
#include <vector>


#include <cgl/CGL_include.h>
#include <file/CFileIO.h>
#include <tools/CStringTool.h>
#include <pong/CVectorShape.h>

using namespace std;

extern float gGlobalLineWidth;
extern float gGlobalScale;

//---------------------------------------------------------------------------
//
// Klasse:    CVectorShape
// Methode:   CVectorShape
//
//
//---------------------------------------------------------------------------

CVectorShape::CVectorShape()
{
    mColor[0] = 1.0;
    mColor[1] = 1.0;
    mColor[2] = 1.0;
    mColor[3] = 1.0;

    mOrigin.Set(0, 0);
    mDisplayListValid = false;
    mRotation = 0;
    mPointStrength = 1.0;
    mColorPtr = mColor;
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorShape
// Methode:   PrintBounds
//
//
//---------------------------------------------------------------------------

std::string CVectorShape::PrintBounds() const
{
    return mBound.Print();
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorShape
// Methode:   Draw
//
//
//---------------------------------------------------------------------------

void CVectorShape::Draw(const SShapeParams& shape)
{
    float Scale = shape.mScale * gGlobalScale;

    glPushMatrix();
    glTranslatef(shape.mPosition.x, shape.mPosition.y, 0.0);
    glScalef(Scale, Scale, 1.0);
    glRotatef(shape.mRotation + mRotation, 0.0, 0.0, 1.0);

    glLineWidth(1.6 * gGlobalLineWidth);
    glColor4fv(mColorPtr);
    glPointSize(2.0 * gGlobalLineWidth);

    if (!mDisplayListValid)
    {
        mDisplayListHandle = glGenLists(2);
        glNewList(mDisplayListHandle, GL_COMPILE);
        for (vector<CPolylineObject>::iterator iv = mPolylist.begin();
            iv != mPolylist.end();
            ++iv)
        {
            iv->Draw();
        }
        glEndList();

        glNewList(mDisplayListHandle+1, GL_COMPILE);
        for (vector<CPolylineObject>::iterator iv = mPolylist.begin();
            iv != mPolylist.end();
            ++iv)
        {
            iv->DrawPoints();
        }
        glEndList();
        mDisplayListValid = true;
    }
    else
    {
        glCallList(mDisplayListHandle);
        glColor4f(mColorPtr[0], mColorPtr[1], mColorPtr[2], mPointStrength);
        glCallList(mDisplayListHandle+1);
    }
    glPopMatrix();

    //glPushMatrix();
    //glColor4f(0.8, 0.4, 0.0, 1.0);
    mBound.CreateBounds(shape);
    //mBound.Draw(shape);
    //glColor4f(1.0, 1.0, 1.0, 1.0);
    //glPopMatrix();
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorShape
// Methode:   DrawPoints
//
//
//---------------------------------------------------------------------------

void CVectorShape::DrawPoints(const SShapeParams& shape)
{
    /*
     * glPointSize(2.5);
     * glPushMatrix();
     * glTranslatef(shape.mPosition.x, shape.mPosition.y, 0.0);
     * glRotatef(shape.mRotation, 0.0, 0.0, 1.0);
     *
     * glColor4f(mColor[0], mColor[1], mColor[2], 1.0);
     * for (vector<CPolylineObject>::iterator iv  = mPolylist.begin();
     *                                     iv != mPolylist.end();
     ++iv)
     * {
     * iv->DrawPoints();
     * }
     * glPopMatrix();
     */
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorShape
// Methode:   SetBound
//
//
//---------------------------------------------------------------------------

void CVectorShape::SetBound(CBoundingObject& bound)
{
    mBound = bound;
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorShape
// Methode:   AddPoly
//
//
//---------------------------------------------------------------------------

void CVectorShape::AddPoly(CPolylineObject& poly)
{
    mPolylist.push_back(poly);
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorShape
// Methode:   Inside
//
//
//---------------------------------------------------------------------------

bool CVectorShape::Inside(const CVectorShape& Other) const
{
    return mBound.Inside(Other.mBound) > 0;
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorShape
// Methode:   Inside
//
//
//---------------------------------------------------------------------------

bool CVectorShape::Inside(float x, float y) const
{
    return mBound.Inside(x, y);
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorShape
// Methode:   SetColor
//
//
//---------------------------------------------------------------------------

void CVectorShape::SetColor(float r, float g, float b, float a)
{
    mColor[0] = r;
    mColor[1] = g;
    mColor[2] = b;
    mColor[3] = a;

/*
 * for (vector<CPolylineObject>::iterator iv  = mPolylist.begin();
 *                                       iv != mPolylist.end();
 ++iv)
 * {
 *  iv->SetColor(r, g, b, a);
 * }
 */
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorShape
// Methode:   SetName
//
//
//---------------------------------------------------------------------------

void CVectorShape::SetName(const string& name)
{
    mName = name;
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorShape
// Methode:   CenterShape
//
//
//---------------------------------------------------------------------------

void CVectorShape::CenterShape()
{
#if 1
    CVector2<float> ShapeMin;
    CVector2<float> ShapeMax;

    ShapeMin.Set(100000.0, 100000.0);
    ShapeMax.Set(-100000.0, -100000.0);

    for (vector<CPolylineObject>::iterator ip = mPolylist.begin();
        ip != mPolylist.end();
        ++ip)
    {
        CVector2<float> PolyMin;
        CVector2<float> PolyMax;

        ip->GetMinMax(&PolyMin, &PolyMax);

        if (PolyMin.x < ShapeMin.x)
        {
            ShapeMin.x = PolyMin.x;
        }
        if (PolyMin.y < ShapeMin.y)
        {
            ShapeMin.y = PolyMin.y;
        }
        if (PolyMax.x > ShapeMax.x)
        {
            ShapeMax.x = PolyMax.x;
        }
        if (PolyMax.y > ShapeMax.y)
        {
            ShapeMax.y = PolyMax.y;
        }
    }

    float CenterX = (ShapeMin.x + ShapeMax.x) / 2;
    float CenterY = (ShapeMin.y + ShapeMax.y) / 2;

    for (vector<CPolylineObject>::iterator ip = mPolylist.begin();
        ip != mPolylist.end();
        ++ip)
    {
        ip->Translate(-CenterX, -CenterY);
    }

    ShapeMin.x -= CenterX;
    ShapeMin.y -= CenterY;
    ShapeMax.x -= CenterX;
    ShapeMax.y -= CenterY;

    mBound.Clear();
    mBound.AddVertex(ShapeMin.x * gGlobalScale, ShapeMin.y * gGlobalScale);
    mBound.AddVertex(ShapeMax.x * gGlobalScale, ShapeMin.y * gGlobalScale);
    mBound.AddVertex(ShapeMax.x * gGlobalScale, ShapeMax.y * gGlobalScale);
    mBound.AddVertex(ShapeMin.x * gGlobalScale, ShapeMax.y * gGlobalScale);
    mBound.AddVertex(ShapeMin.x * gGlobalScale, ShapeMin.y * gGlobalScale);
#endif
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorShape
// Methode:   Scale
//
//
//---------------------------------------------------------------------------

void CVectorShape::Scale(float f)
{
    for (vector<CPolylineObject>::iterator ip = mPolylist.begin();
        ip != mPolylist.end();
        ++ip)
    {
        ip->Scale(f);
    }
    mBound.Scale(f);
}
