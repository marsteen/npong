//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CPixel32.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CPIXEL32_H
#define CPIXEL32_H

#include <graflib/CPixel.h>

class CPixel32 : public CPixel
{
    public:

        unsigned char rgba[4];

        void operator=(CPixel32& p2)
        {
            *(int*)rgba = *(int*)&p2;
        }


        void operator=(int i)
        {
            rgba[0] = i >> 16;
            rgba[1] = (i >> 8) & 0xFF;
            rgba[2] = i & 0xFF;
            rgba[3] = 0;
        }


        bool operator==(CPixel32& p2);
        bool operator!=(CPixel32& p2);

        void Set(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
        int GetInt();
        void SwapRedBlue();
        void SwapBigEndian();
        int Brightness();
};

#endif
