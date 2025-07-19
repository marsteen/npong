//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CGL_Patch2d.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGL_Patch2d_H
#define CGL_Patch2d_H

#include <vector/CVector3T.h>
#include <cgl/CGL_Texture.h>

class CGL_Patch2d : public CGL_Texture
{
    public:

        CGL_Patch2d();

        void Draw();
        void DrawRot(float r);
        void DrawScaled(int x1, int y1, int x2, int y2);
        void DrawScaled(float Scale);
        void DrawNoTex(int w, int h);
        void SetTexRect(int left, int top, int right, int bottom);

        CVector2<float> mPos;
        float mWidth;
        float mHeight;

    protected:

        float TransformY(float y, int h);

        CRectT<float> mTexRect;
};

#endif
