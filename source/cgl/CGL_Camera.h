//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CGL_Camera.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGL_CAMERA_H
#define CGL_CAMERA_H

#include <vector/CVector3T.h>

class CGL_Camera
{
    public:

        CGL_Camera()
        {
            Reset();
        }


        void Reset();

        void operator=(CGL_Camera& cam)
        {
            mStandort = cam.mStandort;
            mVispoint = cam.mVispoint;
            mUpvector = cam.mUpvector;
        }


        void LookAt();

        CVector3<float> mStandort;
        CVector3<float> mVispoint;
        CVector3<float> mUpvector;
};

#endif
