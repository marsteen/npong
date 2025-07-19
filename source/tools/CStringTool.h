//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CStringTool.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CSTRINGTOOL_H
#define CSTRINGTOOL_H

#include <string>
#include <vector>

class CStringTool
{
    public:

        static int SplitString(const std::string& InputString, std::vector<std::string>* ResultVector, char SplitChar);
        void TrimString(std::string* InputString);

        template<typename T>
        static T StringTo(const std::string& str);
};

#include <tools/CStringTool.hpp>

#endif
