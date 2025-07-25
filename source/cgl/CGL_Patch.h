//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CGL_Patch.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGL_PATCH
#define CGL_PATCH

#include <vector/CVector3T.h>
#include <cgl/CGL_Object.h>
#include <cgl/CGL_MatObject.h>

class CGL_Patch : public CGL_Object, public CGL_MatObject
{
    public:

        void MakePatch(float StartS, float StartT, float StepS, float StepT, int PsegS, int PsegT);
        void MakePatchDrawElements(float StartS, float StartT, float StepS, float StepT, int PsegS, int PsegT);
        void MakePatchDrawElementsST(float StartS, float StartT, float StepS, float StepT, int PsegS, int PsegT);
        void MakePatchNotTexture(float StartS, float StartT, float StepS, float StepT, int PsegS, int PsegT);
        void MakePatchPoints(float StartS, float StartT, float StepS, float StepT, int PsegS, int PsegT);



    protected:

        void SetVertex(CVector3<float>* Origin, CVector3<float>* cf);
        void SetSphereVertex(CVector3<float>* Origin, CVector3<float>* cf);


        float mSCircleRad;
        float mTCircleRad;
};

#endif
