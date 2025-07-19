//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CGL_GLU_Sphere.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGL_GLU_SPHERE_H
#define CGL_GLU_SPHERE_H

#include <cgl/CGL_GLU_Object.h>

class CGL_GLU_Sphere : public CGL_GLU_Object
{
    public:

        CGL_GLU_Sphere()
        {
            mUseTexture = false;
        }


        void CreateSphere(float Radius, int Slices, int Stacks, float* DiffuseMaterial);
        void CreateTexturedSphere(float Radius, int Slices, int Stacks, const char* TextureFile, const char* AlphaFile);
        void CreateTexturedInsideSphere(float Radius, int Slices, int Stacks, char* TextureFile, char* AlphaFile);
        void MakeObject();

    protected:


        float mRadius;
        int mSlices;
        int mStacks;
        float mDiffuseMaterial[4];
        float mAmbientMaterial[4];
        bool mUseTexture;
};

#endif
