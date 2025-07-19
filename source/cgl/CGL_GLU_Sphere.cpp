//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CGL_GLU_Sphere.cpp
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cgl/CGL_GLU_Sphere.h>

using namespace std;
//---------------------------------------------------------------------------
//
// Klasse:    CGL_GLU_Sphere
// Methode:		CreateSphere
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_GLU_Sphere::CreateSphere(float Radius, int Slices, int Stacks, float* DiffuseMaterial)
{
    SetParams(GLU_OUTSIDE, GLU_FILL, GLU_SMOOTH, GL_FALSE);

    mRadius = Radius;
    mSlices = Slices;
    mStacks = Stacks;

    for (int i = 0; i < 4; i++)
    {
        mDiffuseMaterial[i] = DiffuseMaterial[i];
        mAmbientMaterial[i] = DiffuseMaterial[i];
    }
    mUseTexture = false;
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_GLU_Sphere
// Methode:		CreateTexturedSphere
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_GLU_Sphere::CreateTexturedSphere(float Radius, int Slices, int Stacks, const char* TextureFile, const char* AlphaFile)
{
    //SetParams(GLU_INSIDE, GLU_FILL, GLU_SMOOTH, GL_TRUE);
    SetParams(GLU_OUTSIDE, GLU_FILL, GLU_SMOOTH, GL_TRUE);
    LoadTextureTga(TextureFile, false);

    /*
     * if (AlphaFile == NULL)
     * {
     *    LoadTexture(TextureFile, false);
     * }
     * else
     * if (TextureFile == NULL)
     * {
     *    LoadShadowMap(AlphaFile, false);
     *    mStatus |= CGL_STATUS_ALPHA;
     * }
     * else
     * {
     *    LoadTransparentTexture(TextureFile, AlphaFile);
     *    mStatus |= CGL_STATUS_ALPHA;
     * }
     */

    mRadius = Radius;
    mSlices = Slices;
    mStacks = Stacks;

    mUseTexture = true;
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_GLU_Sphere
// Methode:		MakeObject
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_GLU_Sphere::MakeObject()
{
    if (mUseTexture)
    {
        glEnable(GL_TEXTURE_2D);

        if (mStatus & CGL_STATUS_ALPHA)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        glBindTexture(GL_TEXTURE_2D, mTexHandle);
        gluSphere(mQuadObj, mRadius, mSlices, mStacks);
        glDisable(GL_TEXTURE_2D);

        if (mStatus & CGL_STATUS_ALPHA)
        {
            glDisable(GL_BLEND);
        }
    }
    else
    {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuseMaterial);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mAmbientMaterial);
        gluSphere(mQuadObj, mRadius, mSlices, mStacks);
    }
}
