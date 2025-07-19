//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CGL_Disk.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGL_DISK_H
#define CGL_DISK_H

class CGL_Disk : public CGL_Object
{
    public:

        void MakeObject();

        CVector3<float> mOrigin;
        int mSegments;
        float mRadius;
};

#endif
