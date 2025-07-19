//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CGraflibJpeg.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGRAFLIBJPEG_H
#define CGRAFLIBJPEG_H

#include <CFileIO.h>
#include <SFileReadInfo.h>
#include <CDataRect.h>
#include <CGraflib.h>

class CGraflibJpeg : public CGraflib
{
    public:

        CGraflibJpeg()
        {
            mJpegInterface = NULL;
            mJpegQuality = 80;
        }


        bool Read(const char* Filename, SFileReadInfo* fri = NULL);
        int Write(const char* Filename, CFileIO* fio = NULL);

        bool OpenReadLine(const char* Filename);
        void ReadLine(void* LineBuffer);
        void CloseReadLine();

        bool OpenWriteLine(const char* Filename);
        void WriteLine(void* LineBuffer);
        void CloseWriteLine();

        void SetAppendMode(bool b);
        bool GetSize(const char* fname, int FileIndex, int FileSize);


        int mJpegQuality;

    protected:

        void* mJpegInterface;
};

#endif
