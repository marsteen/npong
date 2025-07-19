//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	GlobalSystemFunctions.cpp
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <string>
#include <cstdio>
#include <cstring>
#include <global/GlobalSystemFunctions.h>


static std::string StaticAppPath;

namespace GlobalSystem
{
    // ---------------------------------------------------------------------------
    //
    // KLASSE        : global
    // METHODE       : setPath
    //
    //
    //
    // ---------------------------------------------------------------------------

    void setPath(const std::string& path)
    {
        StaticAppPath = path;
    }


    // ---------------------------------------------------------------------------
    //
    // KLASSE        : global
    // METHODE       : path
    //
    //
    //
    // ---------------------------------------------------------------------------

    std::string getPath(const std::string& filename)
    {
        return StaticAppPath + getPathDiv() + filename;
    }
}
