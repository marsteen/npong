//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CGraflibPng.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <file/CFileIO.h>
#include <file/SFileReadInfo.h>
#include <graflib/CDataRect.h>
#include <graflib/CGraflib.h>

#ifndef CGRAFLIBPNG_H
#define CGRAFLIBPNG_H

class CGraflibPng : public CGraflib
{
    public:

        bool Read(const char* Filename, SFileReadInfo* fri = NULL);
        int Write(const char* Filename, CFileIO* fio = NULL);

        bool OpenReadLine(const char* Filename) { return false; }
        void ReadLine(void* LineBuffer) { }
        void CloseReadLine() { }

        bool OpenWriteLine(const char* Filename) { return false; }
        void WriteLine(void* LineBuffer) { }
        void CloseWriteLine() { }

    protected:

        void** MakeRowPointers();
};

#endif
