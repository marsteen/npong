//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CDataRect.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CDATARECT_H
#define CDATARECT_H

#include <cstdlib>
#include <cstring>
#include <graflib/CPixel.h>

class CDataRect
{
    public:

        CDataRect()
        {
            mData = NULL;
            mPalette = NULL;
            mWidth = 0;
            mHeight = 0;
            mBits = 0;
        }


        void operator=(CDataRect& dr)
        {
            mPalette = dr.mPalette;
            mWidth = dr.mWidth;
            mHeight = dr.mHeight;
            mBits = dr.mBits;
        }


        void SetData(int b)
        {
            memset(mData, 0, mWidth * mHeight * (mBits/8));
        }


        void CopyDataFrom(CDataRect* dr)
        {
            mData = dr->mData;
            mPalette = dr->mPalette;
            mWidth = dr->mWidth;
            mHeight = dr->mHeight;
            mBits = dr->mBits;
        }


        void CopyDataFrom(CDataRect& dr)
        {
            mData = dr.mData;
            mPalette = dr.mPalette;
            mWidth = dr.mWidth;
            mHeight = dr.mHeight;
            mBits = dr.mBits;
        }


        bool GetPixel1Bit(int Xko, int Yko);
        bool GetPixel1BitOffset(int LineOffset, int xpos);

        int Offset(int x, int y)
        {
            return (y * mWidth) + x;
        }


        void DeleteData()
        {
            delete[] mData;
            mData = 0L;
        }


        CPixel* mData;
        CPixel* mPalette;
        int mWidth;
        int mHeight;
        int mBits;
};
#endif
