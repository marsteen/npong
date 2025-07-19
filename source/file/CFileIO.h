//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CFileIO.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CFILEIO_H
#define CFILEIO_H

#include <vector>
#include <string>
#include <fstream>

#include "EFileTypes.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>



#ifndef _Ios_Openmode
#define _Ios_Openmode    ios_base::openmode
#endif


#ifndef _Ios_Seekdir
#define _Ios_Seekdir    ios_base::seekdir
#endif


enum EFileAttribut
{
    EFA_NOT_FOUND,
    EFA_FILE,
    EFA_FOLDER
};

class CFileIO
{
    public:

        CFileIO()
        {
            mOpenRead = false;
            mOpenWrite = false;
            mFs = NULL;
        }


        void*  ReadFile(const char* Filename, int* nBytes);
        bool OpenFileRead(const char* Filename, std::_Ios_Openmode type);
        bool OpenFileWrite(const char* Filename, std::_Ios_Openmode type);
        bool OpenFileAppend(const char* Filename, std::_Ios_Openmode type);
        bool OpenFileChange(const char* Filename, int Position);
        bool ReadBytes(void* buffer, int nBytes);
        void*    ReadBytes(int nBytes);
        bool WriteBytes(const void* buffer, int nBytes);
        bool WriteString(const char* str);
        bool WriteFile(const char* Filename, const void* Buffer, int nBytes);
        char*  ReplaceAllStrings(char* SrcString, char* SearchString, char* SubString, int* Count);
        int GetChar();
        bool IsEof();
        void Clear();
        void SkipBytes(int nBytes);
        int GuessFileFormat(const char* Filename);
        char*  ReplaceApp(const char* Filename, const char* neuApp);
        int ReadLine(std::vector<char>* Line);
        int ReadLine(std::string* Line);

        std::string StripExtension(const char* FullPathName);


        char** ResolveWildCards(const char* WildCardString, int* nFiles);
        char** ResolveWildCard(const char* Dir, const char* WildCard, int* DirCount);
        bool ResolveWildCard(const char* Dir, const char* WildCard, std::vector<std::string>* FileList);

        void DeleteStringList(char** StrList);
        char*  Fill0(int i, int n);
        char*  Fill0(char* strbuffer, int i, int n);
        std::string Fill0str(int i, int n);
        bool CreateDir(const char* NewFolder);
        bool CreateDir(const std::string& NewFolder);
        char*  NewString(const char* OldStr);
        bool FileExists(const char* Filename);
        char*  ExtractFilename(const char* FullPathName);
        const char*  ExtractPath(const char* FullPathName);
        bool Strcmpx(const char* s1, const char* s2);
        int GetInt(const char* str);
        int FileType(const char* Filename);


        bool Good()
        {
            return (int)mFs->good();
        }


        void CloseFile();

        bool SetReadPos(int pos);
        bool SetReadPos2(int pos, std::_Ios_Seekdir where);
        int GetReadPos();

        int GetWritePos();
        void SetWritePos(unsigned int pos);
        void SetWritePosEnd();


        std::streampos GetFileSize(const char* Filename, bool* FileExists = NULL);

    protected:

        std::fstream* mFs;
        bool mOpenWrite;
        bool mOpenRead;
};

#endif
