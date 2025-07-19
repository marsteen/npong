//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CVectorUnit.cpp
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
#include <cmath>



#include <cgl/CGL_include.h>
#include <file/CFileIO.h>
#include <tools/CStringTool.h>
#include <pong/CVectorUnit.h>

using namespace std;

//---------------------------------------------------------------------------
//
// Klasse:    CVectorUnit
// Methode:   Run
//
//
//---------------------------------------------------------------------------

void CVectorUnit::Run(SGameContext* gac)
{
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CPlayerUnit
// METHODE       : SetColorPtr
//
//
//
// ---------------------------------------------------------------------------

void CVectorUnit::SetColorPtr(const float* Color, float ps)
{
    mVectorShape->mColorPtr = Color;
    mVectorShape->mPointStrength = ps;
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorUnit
// Methode:   Run
//
//
//---------------------------------------------------------------------------

void CVectorUnit::Destroy()
{
    mStatus = EUS_INACTIVE;
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorUnit
// Methode:   SetPosition
//
//
//---------------------------------------------------------------------------

void CVectorUnit::SetPosition(float x, float y)
{
    mShapeParams.mPosition.x = x;
    mShapeParams.mPosition.y = y;
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorUnit
// Methode:   Distance
//
//
//---------------------------------------------------------------------------

float CVectorUnit::Distance(const CVectorUnit* vu) const
{
    float dx = PosX() - vu->PosX();
    float dy = PosY() - vu->PosY();

    return sqrt(dx * dx + dy * dy);
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorUnit
// Methode:   SetTarget
//
//
//---------------------------------------------------------------------------

void CVectorUnit::SetTarget(const CVectorUnit* vu)
{
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorUnit
// Methode:   SetColor
//
//
//---------------------------------------------------------------------------

void CVectorUnit::SetColor(float r, float g, float b, float a)
{
    if (mVectorShape != NULL)
    {
        mVectorShape->SetColor(r, g, b, a);
    }
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorUnit
// Methode:   Inside
//
//
//---------------------------------------------------------------------------

const float* CVectorUnit::GetColor()
{
    static float sColor[] = { 0.7, 0.7, 0.7, 1.0 };
    const float* col;

    if (mVectorShape != NULL)
    {
        col = mVectorShape->Color();
    }
    else
    {
        //cout << "***** mVectorShape NULL!" << endl;
        col = sColor;
    }
    return col;
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorUnit
// Methode:   Inside
//
//
//---------------------------------------------------------------------------

bool CVectorUnit::Inside(CVectorUnit& vu)
{
    return mVectorShape->Inside(*vu.mVectorShape);
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorUnit
// Methode:   DirOffset
//
// Berechnung der Offsetposition zum Objekt
//
//---------------------------------------------------------------------------


void CVectorUnit::DirOffset(float Offset, CVector2<float>* OffPos)
{
    OffPos->x = PosX() + mShapeParams.mSinRotation * Offset;
    OffPos->y = PosY() - mShapeParams.mCosRotation * Offset;
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorUnit
// Methode:   Inside
//
//
//---------------------------------------------------------------------------

bool CVectorUnit::Inside(float x, float y)
{
    return mVectorShape->Inside(x, y);
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorUnit
// Methode:   AddPosX
//
//
//---------------------------------------------------------------------------

void CVectorUnit::AddPosX(float x)
{
    mShapeParams.mPosition.x += x;
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorUnit
// Methode:   AddPosY
//
//
//---------------------------------------------------------------------------

void CVectorUnit::AddPosY(float y)
{
    mShapeParams.mPosition.y += y;
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorUnit
// Methode:   AddRotation
//
//
//---------------------------------------------------------------------------

void CVectorUnit::AddRotation(float r)
{
    mShapeParams.AddRotation(r);
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorUnit
// Methode:   Draw
//
//
//---------------------------------------------------------------------------

void CVectorUnit::Draw(int Mode)
{
    if (mVectorShape != NULL)
    {
        mVectorShape->Draw(mShapeParams);
    }
}

//---------------------------------------------------------------------------
//
// Klasse:    CVectorUnit
// Methode:   PrintShapeParams
//
//
//---------------------------------------------------------------------------

std::string CVectorUnit::PrintShapeParams() const
{
    return mShapeParams.Print() + " Bounds:" + mVectorShape->PrintBounds();
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorUnit
// Methode:   DrawPoints
//
//
//---------------------------------------------------------------------------
void CVectorUnit::DrawPoints()
{
    if (mVectorShape != NULL)
    {
        mVectorShape->DrawPoints(mShapeParams);
    }
}
