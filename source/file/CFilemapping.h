//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CFilemapping.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CFILEMAPPING_H
#define CFILEMAPPING_H

class CFilemapping
{
    public:

        CFileMapping()
        {
            mMapHandle = NULL;
            mMapPointer = NULL;
        }

        void* OpenRead(char* Filename);
        void Close();

        int mFilesize;

    protected:

        HANDLE mMapHandle;
        HANDLE mFileHandle;
        LPVOID mMapPointer;
};

#endif
