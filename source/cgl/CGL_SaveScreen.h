//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CGL_SaveScreen.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CSAVESCREENGL_H
#define CSAVESCREENGL_H

#include <vector>

struct SCompInfo
{
    unsigned char*	mBuffer;
    int				mBufferSize;
};


class CGL_SaveScreen
{
    public:

        void SaveScreen(int Width, int Height);
        void Write();

    protected:

        std::vector<SCompInfo> mScreenVec;
        int mWidth;
        int mHeight;
};

#endif
