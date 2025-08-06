//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CGL_Patch2d.cpp
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <iostream>
#include <fstream>


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <cmath>
#include <file/CFileIO.h>
#include <cgl/CGL_Patch2d.h>
#include <global/GlobalDebug.h>

extern int gGlobalWindowHeight;

using namespace std;

/*
 * extern CGlobalContext  gContext;
 * extern CWindowContext  gWindow;
 * extern CGlobalMaterial gMaterial;
 * extern CDebug Debug2;
 */


CGL_Patch2d::CGL_Patch2d()
{
    mTexRect.left = 0.0;
    mTexRect.right = 1.0;
    mTexRect.top = 1.0;
    mTexRect.bottom = 0.0;
    mPos.x = 0.0;
    mPos.y = 0.0;
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Patch2d
// Methode:		SetTexRect
//
//
//---------------------------------------------------------------------------

void CGL_Patch2d::SetTexRect(int left, int top, int right, int bottom)
{
    mWidth = right - left;
    mHeight = bottom - top;

    mTexRect.left = float(left) / mTexWidth;
    mTexRect.right = float(right) / mTexWidth;
    mTexRect.top = float(top) / mTexHeight;
    mTexRect.bottom = float(bottom) / mTexHeight;
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Patch2d
// Methode:		DrawRot
//
// Parameter: r - Winkel (in Grad)
//
// Zeichnet den Patch rotiert
//
//---------------------------------------------------------------------------

void CGL_Patch2d::DrawRot(float r)
{
    CVector2<float> Vertex;

    glPushMatrix();

    glEnable(GL_TEXTURE_2D);
//  mHeight = mTexHeight;
// mWidth  = mTexWidth;

    //
    float ty = TransformY(mPos.y, mHeight);

    glTranslatef(mPos.x, ty, 0);
    glRotatef(r, 0.0, 0.0, 1.0);


    glBindTexture(GL_TEXTURE_2D, mTexHandle);
    glBegin(GL_TRIANGLE_STRIP);

    float w2 = float(mWidth) / 2;
    float h2 = float(mHeight) / 2;

    Vertex.x = -w2;
    Vertex.y = -h2;
    glTexCoord2f(mTexRect.left, mTexRect.top);
    glVertex2fv(Vertex.v());

    Vertex.x = w2;
    Vertex.y = -h2;
    glTexCoord2f(mTexRect.right, mTexRect.top);
    glVertex2fv(Vertex.v());

    Vertex.x = -w2;
    Vertex.y = h2;
    glTexCoord2f(mTexRect.left, mTexRect.bottom);
    glVertex2fv(Vertex.v());

    Vertex.x = w2;
    Vertex.y = h2;
    glTexCoord2f(mTexRect.right, mTexRect.bottom);
    glVertex2fv(Vertex.v());

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);


    glPopMatrix();
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Patch2d
// Methode:		Draw
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_Patch2d::Draw()
{
    CVector2<float> Vertex;

    mHeight = mTexHeight;
    mWidth = mTexWidth;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mTexHandle);

    glBegin(GL_TRIANGLE_STRIP);

    float ty = TransformY(mPos.y, mHeight);

    Vertex.x = mPos.x;
    Vertex.y = ty;
    glTexCoord2f(mTexRect.left, mTexRect.top);
    glVertex3fv(Vertex.v());

    Vertex.x = mPos.x + mWidth;
    Vertex.y = ty;
    glTexCoord2f(mTexRect.right, mTexRect.top);
    glVertex3fv(Vertex.v());

    Vertex.x = mPos.x;
    Vertex.y = ty + mHeight;
    glTexCoord2f(mTexRect.left, mTexRect.bottom);
    glVertex3fv(Vertex.v());

    Vertex.x = mPos.x + mWidth;
    Vertex.y = ty + mHeight;
    glTexCoord2f(mTexRect.right, mTexRect.bottom);
    glVertex3fv(Vertex.v());

    glEnd();

    glDisable(GL_TEXTURE_2D);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Patch2d
// Methode:		DrawNoTex
//
// Ohne Textur zeichnen
//
//---------------------------------------------------------------------------

void CGL_Patch2d::DrawNoTex(int w, int h)
{
/*
 *  stringstream mstr;
 *  GlobalDebug("CGL_Patch2d::DrawNoTex START");
 *  mstr << " X=" << mPos.x << " Y=" << mPos.y << " W=" << w << " H=" << h;
 *  GlobalDebug(mstr);
 */

    float ty = TransformY(mPos.y, h);


    CVector2<float> Vertex;

    glBegin(GL_TRIANGLE_STRIP);

    Vertex.x = mPos.x;
    Vertex.y = ty;
    glVertex2fv(Vertex.v());

    Vertex.x = mPos.x + w;
    Vertex.y = ty;
    glVertex2fv(Vertex.v());

    Vertex.x = mPos.x;
    Vertex.y = ty + h;
    glVertex2fv(Vertex.v());

    Vertex.x = mPos.x + w;
    Vertex.y = ty + h;
    glVertex2fv(Vertex.v());

    glEnd();

    GlobalDebug("CGL_Patch2d::DrawNoTex END");
}


//---------------------------------------------------------------------------
//
// Klasse:    static
// Methode:		sSwap
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template<typename T>
static void sSwap(T* a, T* b)
{
    T sw;

    if (*b < *a)
    {
        sw = *b;
        *b = *a;
        *a = sw;
    }
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Patch2d
// Methode:		DrawScaled
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_Patch2d::DrawScaled(float Scale)
{
    mHeight = mTexHeight;
    mWidth = mTexWidth;

    DrawScaled(mPos.x, mPos.y, mPos.x + mWidth * Scale, mPos.y + mHeight * Scale);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Patch2d
// Methode:		DrawScaled
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_Patch2d::DrawScaled(int x1, int y1, int x2, int y2)
{
    CVector2<float> Vertex;

    sSwap<int>(&x1, &x2);
    sSwap<int>(&y1, &y2);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mTexHandle);
    glBegin(GL_TRIANGLE_STRIP);

    Vertex.x = x1;
    Vertex.y = y1;
    glTexCoord2f(mTexRect.left, mTexRect.top);
    glVertex2fv(Vertex.v());

    Vertex.x = x2;
    Vertex.y = y1;
    glTexCoord2f(mTexRect.right, mTexRect.top);
    glVertex2fv(Vertex.v());

    Vertex.x = x1;
    Vertex.y = y2;
    glTexCoord2f(mTexRect.left, mTexRect.bottom);
    glVertex2fv(Vertex.v());

    Vertex.x = x2;
    Vertex.y = y2;
    glTexCoord2f(mTexRect.right, mTexRect.bottom);
    glVertex2fv(Vertex.v());

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Patch2d
// Methode:		TransformY
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

float CGL_Patch2d::TransformY(float y, int h)
{
    return gGlobalWindowHeight - h - y;
}
