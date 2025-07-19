//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CVectorObject.cpp
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <iostream>
#include <vector>
#include <cmath>
#include <pong/CVectorObject.h>

using namespace std;


//---------------------------------------------------------------------------
//
// Klasse:		CVectorObject
// Methode:		CVectorObject
//
//
//---------------------------------------------------------------------------

CVectorObject::CVectorObject()
{
    mColor[0] = mColor[1] = mColor[2] = mColor[3] = 1.0;
}


//---------------------------------------------------------------------------
//
// Klasse:		CVectorObject
// Methode:		TransformVertex
//
// Parameter:	v1:     Vector, der Transformiert wird
//            v2:     Ergebnisvector
//            Origin: Vector, um den v1 gedreht wird.
//
//---------------------------------------------------------------------------

void CVectorObject::TransformVertex(const CVector2<float>& v1, CVector2<float>& v2, const SShapeParams& sp)
{
    v2 = v1;
    v2.RotationXY(&sp.mOrigin, sp.mSinRotation, sp.mCosRotation);
    v2 += sp.mPosition;
}


//---------------------------------------------------------------------------
//
// Klasse:		CVectorObject
// Methode:		SetColor
//
//
//---------------------------------------------------------------------------

void CVectorObject::SetColor(float r, float g, float b, float a)
{
    mColor[0] = r;
    mColor[1] = g;
    mColor[2] = b;
    mColor[3] = a;
}
