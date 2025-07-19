//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CGL_FramebufferObject.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGL_FramebufferObject_H
#define CGL_FramebufferObject_H

#include <cgl/CGL_include.h>
#include <tools/CRectT.h>

class CGL_FramebufferObject
{
    public:

        void CreateFramebufferObject(int Width, int Height);
        void DrawToFrameBuffer(bool Enable);

        void DrawTexture() const;
        void DrawTexture(int Width, int Height) const;
        void DrawTexture(const CRectT<float>* vrc) const;


    protected:

        GLuint mFBhandle;
        GLuint mColorRenderbuffer;
        GLuint mDepthRenderbuffer;
        GLuint mTexture;

        unsigned int mWidth;
        unsigned int mHeight;
};

#endif
