//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CStringConverter.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CSTRINGCONVERTER_H
#define CSTRINGCONVERTER_H

class CStringConverter
{
    public:

        int ToInt(string& s);
        float ToFloat(string& s);
        float ToDouble(string& s);

        string ToStr(int n);
};

#endif // CSTRINGCONVERTER
