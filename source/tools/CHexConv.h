//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CHexConv.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CHEXCONV_H
#define CHEXCONV_H

class CHexConv
{
    public:

        int NibbleToInt(char a);
        int ByteToInt(unsigned char a, unsigned char b);
        float ByteToFloat(unsigned char a, unsigned char b);
        int StringToInt(const char* s);
};

#include <tools/CHexConv.hpp>

#endif // CHEXCONV
