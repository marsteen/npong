//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	SShapeParams.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef SSHAPEPARAMS_H
#define SSHAPEPARAMS_H

#include <vector>
#include <vector/CVector3T.h>

struct SShapeParams
{
    public:

        SShapeParams();

        void AddRotation(float r);
        void SetRotation(float r);

        std::string Print() const;

        CVector2<float> mPosition;
        CVector2<float> mOrigin;
        float			mRotation;
        float			mSinRotation;
        float			mCosRotation;
        float			mScale;
};

#endif
