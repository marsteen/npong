//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CParser.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CPARSER_H
#define CPARSER_H

class CParser
{
    public:

        char** SplitLine(char* line, char t, int* AnzahlParams);
        void DeleteSplitLine(char** sline);
};

#endif
