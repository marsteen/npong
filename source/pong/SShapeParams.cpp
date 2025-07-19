//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	SShapeParams.cpp
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>

#include <tools/MathDefines.h>
#include <pong/SShapeParams.h>

using namespace std;

//---------------------------------------------------------------------------
//
// Klasse:		SShapeParams
// Methode:		SShapeParams
//
//
//---------------------------------------------------------------------------

SShapeParams::SShapeParams()
{
    mOrigin.x = 0.0f;
    mOrigin.y = 0.0f;

    mPosition.x = 0.0f;
    mPosition.y = 0.0f;
    mScale = 1.0f;
    mSinRotation = 0.0f;
    mCosRotation = 0.0f;

    SetRotation(0.0f);
}

//---------------------------------------------------------------------------
//
// Klasse:		SShapeParams
// Methode:		Print
//
//
//---------------------------------------------------------------------------

std::string SShapeParams::Print() const
{
    stringstream mstr;

    mstr	<< "x=" << mPosition.x << " y=" << mPosition.y
            << " ox=" << mOrigin.y << " oy=" << mOrigin.y
            << " scale=" << mScale << " rot=" << mRotation;

    return mstr.str();
}


//---------------------------------------------------------------------------
//
// Klasse:		SShapeParams
// Methode:		SetRotation
//
//
//---------------------------------------------------------------------------

void SShapeParams::SetRotation(float r)
{
    mRotation = r;
    mSinRotation = sin(DEG_TO_RAD(r));
    mCosRotation = cos(DEG_TO_RAD(r));
}


//---------------------------------------------------------------------------
//
// Klasse:		SShapeParams
// Methode:		AddRotation
//
//
//---------------------------------------------------------------------------

void SShapeParams::AddRotation(float r)
{
    mRotation += r;
    while (mRotation < 0)
    {
        mRotation += 360.0;
    }

    while (mRotation > 360.0)
    {
        mRotation -= 360.0;
    }

    mSinRotation = sin(DEG_TO_RAD(mRotation));
    mCosRotation = cos(DEG_TO_RAD(mRotation));
}
