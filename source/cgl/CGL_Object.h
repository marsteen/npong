//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CGL_Object.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGL_OBJECT
#define CGL_OBJECT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cgl/CGL_Texture.h>
#include <vector/CVector3T.h>

enum ECGL_STATUS
{
    CGL_STATUS_ALPHA = 32
};

#define DEG_TO_RAD(x)		((x) / 57.29577951)
#define RAD_TO_DEG(x)		((x) * 57.29577951)

class CGL_Object : public CGL_Texture
{
    public:

        void Init();
        void DeleteDisplayList();
        virtual void MakeObject();
        virtual void Draw();

        CGL_Object();
        ~CGL_Object();

    protected:

        void SetNormalVertex(CVector3<float>* Origin, CVector3<float>* cf);

        GLuint mDisplayListHandle;
        GLfloat mMaterial[4];
        unsigned int mStatus;
};

#endif
