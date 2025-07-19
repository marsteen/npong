//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CStringConverter.cpp
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <string>
#include <math.h>
#include <cstdlib>
using namespace std;
#include <CStringConverter.h>

int CStringConverter::ToInt(string& s)
{
    char* EndPtr;

    return strtol(s.c_str(), &EndPtr, 10);
}


float CStringConverter::ToFloat(string& s)
{
    return atof(s.c_str());
}


string CStringConverter::ToStr(int n)
{
    char StrBuffer[32];

    sprintf(StrBuffer, "%d", n);
    return string(StrBuffer);
}
