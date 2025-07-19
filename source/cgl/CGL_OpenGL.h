//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CGL_OpenGL.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGL_OPENGL_H
#define CGL_OPENGL_H

class CGL_OpenGL
{
    public:

        void SetViewport(int w, int h);
        void StartModelView();
        void StartProjectionView();
        void StartProjectionView(int Width, int Height) const;
        void SetupLighting();

    protected:

        int mWidth;
        int mHeight;
        float mAspect;
};

#endif
