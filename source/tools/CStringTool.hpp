//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CStringTool.hpp
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CSTRINGTOOL_HPP
#define CSTRINGTOOL_HPP

#include <string>
#include <sstream>

template<typename T>
T CStringTool::StringTo(const std::string& str)
{
    T Value;
    std::stringstream istr(str);

    istr >> Value;
    return Value;
}


#endif
