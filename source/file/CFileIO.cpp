//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CFileIO.cpp
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifdef __WIN32
#include <windows.h>
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include <file/CFileIO.h>

using namespace std;

//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   GetInt
//
//
//---------------------------------------------------------------------------

int CFileIO::GetInt(const char* str)
{
    if (str != NULL)
    {
        int x;
        sscanf(str, "%d", &x);
        return x;
    }
    return 0;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   GetChar
//
// Parameter: char* Filename - Name der Datei
//
// Return:    int - Gr??e der Datei in Bytes
//
//---------------------------------------------------------------------------

int CFileIO::GetChar()
{
    char ch;

    mFs->get(ch);
    return ch;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   IsEof
//
//
//---------------------------------------------------------------------------

bool CFileIO::IsEof()
{
    if (mFs == NULL)
    {
        return true;
    }
    return mFs->eof();
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   Clear
//
//
//
//
//---------------------------------------------------------------------------

void CFileIO::Clear()
{
    if (mFs != NULL)
    {
        mFs->clear();
    }
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   SkipBytes
//
// Parameter: int nBytes - Anzahl an Bytes ueberspringen (Eingabedatei)
//
//
//---------------------------------------------------------------------------

void CFileIO::SkipBytes(int nBytes)
{
    mFs->seekg(nBytes, ios_base::cur);
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   GetFileSize
//
// Parameter: char* Filename - Name der Datei
//
// Return:    Groesse der Datei in Bytes
//
//---------------------------------------------------------------------------

streampos CFileIO::GetFileSize(const char* Filename, bool* FileExists)
{
    streampos FileSize = 0;
    ifstream fin(Filename, ios::in | ios::binary);

    if (fin.good())
    {
        fin.seekg(0, ios::end);
        FileSize = fin.tellg();
        fin.close();

        if (FileExists != NULL)
        {
            *FileExists = true;
        }
    }
    else
    {
        if (FileExists != NULL)
        {
            *FileExists = false;
        }
    }
    return FileSize;
}


#if 0
//--------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   FileExists
//
// Parameter: char* Filename - Name der Datei
//
// Return:    true  - Datei wurde ge?ffnet
//            false - Datei konnte nicht ge?ffnet werden
//
// ?berpr?fen, ob Datei existiert
//
//---------------------------------------------------------------------------

bool CFileIO::FileExists(const char* Filename)
{
    ifstream fin(Filename, ios::in | ios::binary);
    bool s = fin.good();

    if (s)
    {
        fin.close();
    }
    return s;
}


#endif

#if 0
//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:		FileAttribut
//
// return: 0 = Datei nicht gefunden
//         1 = "normale" Datei
//         2 = Ordner
//
//---------------------------------------------------------------------------

int CFileIO::FileAttribut(const char* Filename)
{
    int r = EFA_FILE;

#ifdef __WIN32__
    DWORD fa = GetFileAttributes(Filename);
    if (fa == 0xFFFFFFFF)
    {
        r = EFA_NOT_FOUND;
    }
    else
    if (fa & FILE_ATTRIBUTE_DIRECTORY)
    {
        r = EFA_FOLDER;
    }
#endif

    return r;
}


#endif


//--------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   OpenFileRead
//
// Parameter: char* Filename - Name der Datei
//
// Return:    true  - Datei wurde geoeffnet
//            false - Datei konnte nicht geoeffnet werden
//
// Oeffnen einer Datei zum Lesen
//
//---------------------------------------------------------------------------



bool CFileIO::OpenFileRead(const char* Filename, _Ios_Openmode OpenMode)
{
    if (mFs != NULL)
    {
        delete mFs;
    }
    mFs = new fstream(Filename, ios::in | OpenMode);
    mOpenRead = mFs->good();
    return mOpenRead;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   OpenFileWrite
//
// Parameter: char* Filename - Name der Datei
//
// Return:    true  - Datei wurde ge?ffnet
//            false - Datei konnte nicht ge?ffnet werden
//
// ?ffnen einer Datei zum Lesen
//
//---------------------------------------------------------------------------

bool CFileIO::OpenFileWrite(const char* Filename, _Ios_Openmode OpenMode)
{
    if (mFs != NULL)
    {
        delete mFs;
    }
    mFs = new fstream(Filename, ios::out | OpenMode);
    mOpenWrite = mFs->good();
    return mOpenWrite;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   OpenFileAppend
//
// Parameter: char* Filename - Name der Datei
//
// Return:    true  - Datei wurde ge?ffnet
//            false - Datei konnte nicht ge?ffnet werden
//
// ?ffnen einer Datei zum Lesen
//
//---------------------------------------------------------------------------

bool CFileIO::OpenFileAppend(const char* Filename, _Ios_Openmode OpenMode)
{
    if (mFs != NULL)
    {
        delete mFs;
    }
    mFs = new fstream(Filename, ios::app | ios::out| OpenMode);
    mOpenWrite = mFs->good();
    return mOpenWrite;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   OpenFileChange
//
// Parameter: char* filename - Name der Datei
//            int pos        - Schreibposition
//
// Return:    true  - Datei wurde ge?ffnet
//            false - Datei konnte nicht ge?ffnet werden
//
// ?ffnen einer Datei zum ?ndern
//
//---------------------------------------------------------------------------

bool CFileIO::OpenFileChange(const char* Filename, int Position)
{
    bool suc = OpenFileWrite(Filename, ios::out | ios::binary | ios::in);

    if (suc)
    {
        SetReadPos(Position);
        SetWritePos(Position);
    }
    return suc;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   ReadFile
//
// Parameter: char* Filename - Name der Datei
//
//            int* nBytes    - Anzahl der Bytes die gelesen wurden (Gr??e
//                             der Datei).
//
// Return:    void* - Zeiger auf Puffer, in den die Daten gelesen wurden,
//                    oder NULL (Fehlerfall)
//
//
//
// Lesen des Inhalts einer Datei in einen Puffer. Der Speicher f?r den
// Puffer wird reserviert. Zur?ckgegeben werden ein Zeiger auf den
// Puffer sowie die Anzahl der eingelesenen Bytes
//
//---------------------------------------------------------------------------

void* CFileIO::ReadFile(const char* Filename, int* nBytes)
{
    char* buffer = NULL;

    *nBytes = CFileIO::GetFileSize(Filename);
    if (*nBytes > 0)
    {
        if (OpenFileRead(Filename, ios::binary))
        {
            buffer = new char[*nBytes+1];
            if (buffer != NULL)
            {
                ReadBytes(buffer, *nBytes);
                buffer[*nBytes] = 0;
            }
        }
        CloseFile();
    }
    return buffer;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   WriteFile
//
// Parameter: char* Filename - Name der Datei
//
//            int   nBytes    - Anzahl der Bytes die gelesen wurden (Gr??e
//                             der Datei).
//
//            const void* - Zeiger auf Puffer, dessen Daten geschrieben
//                          werden
//
//
//---------------------------------------------------------------------------

bool CFileIO::WriteFile(const char* Filename, const void* buffer, int nBytes)
{
    bool suc = false;

    if (nBytes > 0)
    {
        if (OpenFileWrite(Filename, ios::binary))
        {
            WriteBytes(buffer, nBytes);
            suc = true;
            CloseFile();
        }
    }
    return suc;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   WriteBytes
//
//
//
// Einlesen einer Anzahl von Bytes aus einer ge?ffneten Datei
//
//---------------------------------------------------------------------------

bool CFileIO::WriteBytes(const void* buffer, int nBytes)
{
    if (mOpenWrite)
    {
        mFs->write((const char*)buffer, nBytes);
    }
    return mOpenWrite;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   WriteString
//
//
//---------------------------------------------------------------------------

bool CFileIO::WriteString(const char* str)
{
    return WriteBytes(str, strlen(str));
}


#if 0
//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   ReplaceAllStrings
//
//
//---------------------------------------------------------------------------

class CStrpos : public CListElem<CStrpos>
{
    public:

        char* mPos;
};

class CStrposList : public CList<CStrpos>
{
};


static void CopyStringBytes(char* dst, char* src, int num)
{
    int i;

    for (i = 0; (i < num) && (*src != 0); i++)
    {
        *(dst++) = *(src++);
    }
    *dst = 0;
}


char* CFileIO::ReplaceAllStrings(char* SrcString, char* SearchString, char* SubString, int* Count)
{
    CStrposList slist;
    int cnt = 0;
    char* pos;
    char* StartPos = SrcString;
    int LenSearch = strlen(SearchString);
    int LenSub = strlen(SubString);
    int LenNew;
    char* NewString = NULL;

    do
    {
        pos = strstr(StartPos, SearchString);
        if (pos != NULL)
        {
            CStrpos* se = slist.NewListElem();
            se->mPos = pos;
            StartPos = pos + LenSearch;
            cnt++;
        }
    }while (pos != NULL);

    *Count = cnt;

    if (cnt > 0)
    {
        LenNew = strlen(SrcString) + (cnt * (LenSub - LenSearch));

        NewString = new char[LenNew+1];
        char* NewStringPos = NewString;

        StartPos = SrcString;
        for (CStrpos* se = slist.GetFirst();
            se != NULL;
            se = slist.GetNext())
        {
            int len = se->mPos - StartPos;
            CopyStringBytes(NewStringPos, StartPos, len);
            NewStringPos += len;
            CopyStringBytes(NewStringPos, SubString, LenSub);
            NewStringPos += LenSub;

            StartPos = se->mPos + LenSearch;
        }
        CopyStringBytes(NewStringPos, StartPos, strlen(StartPos));
        slist.ClearList();
    }
    else
    {
        NewString = new char[strlen(SrcString) + 1];
        strcpy(NewString, SrcString);
    }

    return NewString;
}


#endif

//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   ReadBytes
//
// Parameter: void* buffer - Zeiger auf Puffer, in den die Datei eingelesen
//                           werden
//
//            int nBytes   - Anzahl der Bytes, die eingelesen werden sollen
//
// Return:    true  - Daten wurden eingelesen
//            false - Daten konnten nicht eingelesen werden
//
//
//
// Einlesen einer Anzahl von Bytes aus einer ge?ffneten Datei
//
//---------------------------------------------------------------------------

bool CFileIO::ReadBytes(void* buffer, int nBytes)
{
    if (mOpenRead)
    {
        mFs->read((char*)buffer, nBytes);
    }
    return mOpenRead;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   ReadLine
//
// Einlesen einer Text-Zeile aus einer Datei
// Die Datei muss im Bin?r-Modus ge?ffnet sein
//
//---------------------------------------------------------------------------

int CFileIO::ReadLine(vector<char>* Line)
{
    char ch;
    bool EndLine = false;

    Line->clear();
    do
    {
        mFs->get(ch);
        if (!mFs->eof())
        {
            if (ch != 0x0D)
            {
                if (ch != 0x0A)
                {
                    Line->push_back(ch);
                }
                else
                {
                    EndLine = true;
                }
            }
        }
        else
        {
            EndLine = true;
        }
    }while (!EndLine);
    return true;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   ReadLine
//
// Einlesen einer Text-Zeile aus einer Datei
// Die Datei muss im Bin?r-Modus ge?ffnet sein
//
//---------------------------------------------------------------------------

int CFileIO::ReadLine(string* Line)
{
    char ch;
    bool EndLine = false;
    bool IsEof = false;

    Line->clear();
    do
    {
        mFs->get(ch);
        if (!mFs->eof())
        {
            if (ch != 0x0D)
            {
                if (ch != 0x0A)
                {
                    Line->push_back(ch);
                }
                else
                {
                    EndLine = true;
                }
            }
        }
        else
        {
            EndLine = true;
            IsEof = true;
        }
    }while (!EndLine);
    return !IsEof;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   ReadBytes
//
// Parameter:
//
// Return:
//
//
// Lesen von Bytes aus einer Datei
//
//---------------------------------------------------------------------------

void* CFileIO::ReadBytes(int nBytes)
{
    char* buffer = NULL;

    if (mOpenRead)
    {
        buffer = new char[nBytes];
        mFs->read(buffer, nBytes);
    }
    return buffer;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   CloseFile
//
// Parameter:
//
// Return:
//
//
// Schliessen einer Datei
//
//---------------------------------------------------------------------------

void CFileIO::CloseFile()
{
    if (mOpenWrite || mOpenRead)
    {
        mFs->close();
        mOpenRead = false;
        mOpenWrite = false;
        delete mFs;
        mFs = NULL;
    }
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   SetReadPos
//
//
//
//
//---------------------------------------------------------------------------

bool CFileIO::SetReadPos(int pos)
{
    mFs->seekg(pos, ios::beg);
    return (int)mFs->tellg() == pos;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   SetReadPos
//
//
//
//
//---------------------------------------------------------------------------

bool CFileIO::SetReadPos2(int pos, std::_Ios_Seekdir where)
{
    mFs->seekg(pos, where);
    return (int)mFs->tellg() == pos;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   SetReadPos
//
//
//
//
//---------------------------------------------------------------------------

void CFileIO::SetWritePosEnd()
{
    mFs->seekp(0, ios_base::end);
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   SetReadPos
//
//
//
//
//---------------------------------------------------------------------------

void CFileIO::SetWritePos(unsigned int pos)
{
    mFs->seekp(pos, ios_base::beg);
    //mFs->seekg(pos, ios_base::beg);
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   GetReadPos
//
//
//
//
//---------------------------------------------------------------------------

int CFileIO::GetReadPos()
{
    return mFs->tellg();
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   GetWritePos
//
//
//
//
//---------------------------------------------------------------------------

int CFileIO::GetWritePos()
{
    return mFs->tellp();
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:		GuessFileFormat
//
// Return:
//
//  EFILETYPE_UNKNOWN,
//  EFILETYPE_JPG,
//  EFILETYPE_TIF,
//  EFILETYPE_PNG,
//  EFILETYPE_TGA,
//  EFILETYPE_RAW
//
//---------------------------------------------------------------------------

int CFileIO::GuessFileFormat(const char* Filename)
{
    const char* AppList[] =
    {
        ".JPG",
        ".TIF",
        ".PNG",
        ".TGA",
        ".RAW",
        ".GIF",
        NULL
    };

    int FileType;
    char FilenameCopy[256];

    strcpy(FilenameCopy, Filename);

    if (strlen(FilenameCopy) > 4)
    {
        for (int i = 0; FilenameCopy[i] != 0; i++)
        {
            FilenameCopy[i] = toupper(FilenameCopy[i]);
        }

        for (int i = 0; AppList[i] != NULL; i++)
        {
            char* FilenameCopyPtr = FilenameCopy + strlen(FilenameCopy) - strlen(AppList[i]);
            if (strcmp(FilenameCopyPtr, AppList[i]) == 0)
            {
                return i+1;
            }
        }
    }
    return EFILETYPE_UNKNOWN;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:		ReplaceApp
//
//---------------------------------------------------------------------------

char* CFileIO::ReplaceApp(const char* Filename, const char* neuApp)
{
    char NameBuffer[512];
    char* NeuFilename;

    strcpy(NameBuffer, Filename);
    char* Punkt = strrchr(NameBuffer, '.');

    if (Punkt != NULL)
    {
        *Punkt = 0;
    }

    strcat(NameBuffer, neuApp);

    NeuFilename = new char[strlen(NameBuffer) + 1];

    strcpy(NeuFilename, NameBuffer);

    return NeuFilename;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:		Strcmpx
//
//---------------------------------------------------------------------------

bool CFileIO::Strcmpx(const char* s1, const char* s2)
{
    if ((s1 == NULL) || (s2 == NULL))
    {
        return false;
    }

    char* bstr1 = new char[strlen(s1) + 1];
    char* bstr2 = new char[strlen(s2) + 1];

    strcpy(bstr1, s1);
    strcpy(bstr2, s2);

    for (char* c1 = bstr1; *c1 != 0; c1++)
    {
        *c1 = toupper(*c1);
    }
    for (char* c1 = bstr2; *c1 != 0; c1++)
    {
        *c1 = toupper(*c1);
    }

    int s = strcmp(bstr1, bstr2);

    delete bstr2;
    delete bstr1;

    return s == 0;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:		ResolveWildCard
//
//---------------------------------------------------------------------------

bool CFileIO::ResolveWildCard(const char* Dir, const char* WildCard, vector<string>* FileList)
{
    struct stat FileInfo;
    struct dirent* CurrentFile;
    DIR* Directory;
    char** DirList = NULL;
    bool r = false;

    Directory = opendir(Dir);

    cout << "CFileIO::ResolveWildCard Dir=" << Dir << " Wildcard=" << WildCard << endl;

    if (WildCard[0] == '*')
    {
        WildCard++;
    }
    FileList->clear();

    if (Directory != NULL)
    {
        r = true;
        Directory = opendir(Dir);

        int i = 0;
        while ((CurrentFile = readdir(Directory)) != NULL)
        {
            char* EndString = CurrentFile->d_name + (strlen(CurrentFile->d_name) - strlen(WildCard));

            if (Strcmpx(EndString, WildCard))
            {
                string Filename = CurrentFile->d_name;
                FileList->push_back(Filename);
            }

            //cout << "File:" << CurrentFile->d_name << endl;
        }

        closedir(Directory);
    }
    return r;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:		ResolveWildCard
//
//---------------------------------------------------------------------------

char** CFileIO::ResolveWildCard(const char* Dir, const char* WildCard, int* DirCount)
{
    struct stat FileInfo;
    struct dirent* CurrentFile;
    DIR* Directory;
    char** DirList = NULL;

    *DirCount = 0;
    Directory = opendir(Dir);

    cout << "CFileIO::ResolveWildCard Dir=" << Dir << " Wildcard=" << WildCard << endl;

    if (WildCard[0] == '*')
    {
        WildCard++;
    }

    if (Directory != NULL)
    {
        while ((CurrentFile = readdir(Directory)) != NULL)
        {
            char* EndString = CurrentFile->d_name + (strlen(CurrentFile->d_name) - strlen(WildCard));

            //cout << "Filename=" << CurrentFile->d_name <<  " EndString=" << EndString << endl;

            if (Strcmpx(EndString, WildCard))
            {
                (*DirCount)++;
            }
        }

        closedir(Directory);

        if (*DirCount > 0)
        {
            DirList = new char*[*DirCount + 1];

            Directory = opendir(Dir);

            int i = 0;
            while ((CurrentFile = readdir(Directory)) != NULL)
            {
                char* EndString = CurrentFile->d_name + (strlen(CurrentFile->d_name) - strlen(WildCard));

                if (Strcmpx(EndString, WildCard))
                {
                    DirList[i++] = NewString(CurrentFile->d_name);
                }

                //cout << "File:" << CurrentFile->d_name << endl;
            }

            closedir(Directory);
            DirList[*DirCount] = NULL;
        }
    }
    return DirList;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   FileExists
//
// Parameter: char* Foldername - Name des Ordners
//
// Return:    true  - Datei existiert
//            false - Datei existiert nicht
//
//---------------------------------------------------------------------------


int CFileIO::FileType(const char* Filename)
{
    struct stat attribut;
    int r;

    if (stat(Filename, &attribut))
    {
        if (attribut.st_mode & S_IFREG)
        {
            r = 1; // Regul�re Datei
        }
        else
        if (attribut.st_mode & S_IFDIR)
        {
            r = 2; // Ordner
        }
        else
        {
            r = -1; // unbekannt/nicht unterst�tzt
        }
    }
    else
    {
        r = 0;
    }
    return r;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   FileExists
//
// Parameter: char* Foldername - Name des Ordners
//
// Return:    true  - Datei existiert
//            false - Datei existiert nicht
//
//---------------------------------------------------------------------------


bool CFileIO::FileExists(const char* Filename)
{
    struct stat attribut;

    return stat(Filename, &attribut) != -1;
}


#ifdef __WIN32

// ---------------------------------------------------------------------------
//
// METHODE       : ResolveWildCards
//
// KLASSE        : CParserExt
//
// RETURN        : char** - Zeiger auf Dateiliste (endet mit NULL)
//
// PARAMETER     : char* WildCardString - String mit Wildcards (*, ?)
//
// BESCHREIBUNG  : Erstellen einer Datei-Liste aus einem Wildcard-String
//
// HISTORY       :
//
// 28.11.2001 erstellt
//
// ---------------------------------------------------------------------------

char** CFileIO::ResolveWildCards(const char* WildCardString, int* nFiles)
{
    WIN32_FIND_DATA FindData;
    int AnzahlFiles = 0;

    HANDLE fhand = FindFirstFile(WildCardString, &FindData);

    if (fhand != INVALID_HANDLE_VALUE)
    {
        list<char*> FileList;

        do
        {
            char* Filename = new char[strlen(FindData.cFileName) + 1];
            strcpy(Filename, FindData.cFileName);

            FileList.push_back(Filename);

            AnzahlFiles++;
        }while (FindNextFile(fhand, &FindData));

        char** FilePtrList = new char*[AnzahlFiles + 2];

        int i = 0;
        for (list<char*>::iterator fn = FileList.begin();
            fn != FileList.end();
            fn++)
        {
            FilePtrList[i++] = *fn;
        }
        FilePtrList[AnzahlFiles] = NULL;

        if (nFiles != NULL)
        {
            *nFiles = AnzahlFiles;
        }
        FileList.clear();

        return FilePtrList;
    }

    char** FilePtrList = new char*[1];

    FilePtrList[0] = NULL;

    if (nFiles != NULL)
    {
        *nFiles = AnzahlFiles;
    }

    return FilePtrList;
}


#endif


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:		StripExtension
//
// Liefert den Dateinamen ohne Datei-Anhang zurueck
//
//---------------------------------------------------------------------------

string CFileIO::StripExtension(const char* FullPathName)
{
    string OutString;
    char* TmpName = NewString(FullPathName);
    char* slash = strrchr(TmpName, '.');

    if (slash != NULL)
    {
        *slash = 0;
        OutString = TmpName;
    }
    else
    {
        OutString = FullPathName;
    }
    return OutString;
}


//---------------------------------------------------------------------------
//
//
// Klasse:  DeleteStringList
// Methode:
//
//
//---------------------------------------------------------------------------

void CFileIO::DeleteStringList(char** StringList)
{
    if (StringList != NULL)
    {
        for (int i = 0; StringList[i] != NULL; i++)
        {
            delete StringList[i];
        }
        delete StringList;
    }
}


//---------------------------------------------------------------------------
//
//
// Klasse:  CFileIO
// Methode: Fill0
//
//   Integer-Zahl in String umwandeln und dabei mit Nullen
//   auff?llen.
//
//   int i - Zahl
//   int n - Anzahl der Stellen
//
//---------------------------------------------------------------------------

char* CFileIO::Fill0(int i, int n)
{
    static char strbuffer[16];

    return Fill0(strbuffer, i, n);
}


//---------------------------------------------------------------------------
//
//
// Klasse:  CFileIO
// Methode: Fill0
//
//   Integer-Zahl in String umwandeln und dabei mit Nullen
//   auff?llen.
//
//   int i - Zahl
//   int n - Anzahl der Stellen
//
//---------------------------------------------------------------------------

string CFileIO::Fill0str(int i, int n)
{
    string fstr = Fill0(i, n);

    return fstr;
}


//---------------------------------------------------------------------------
//
//
// Klasse:  CFileIO
// Methode: Fill0
//
//   Integer-Zahl in String umwandeln und dabei mit Nullen
//   auff?llen.
//
//   int i - Zahl
//   int n - Anzahl der Stellen
//
//---------------------------------------------------------------------------

char* CFileIO::Fill0(char* strbuffer, int i, int n)
{
    sprintf(strbuffer, "%d", i);

    char len = strlen(strbuffer);

    if (len < n)
    {
        char strbuffer2[16];

        strcpy(strbuffer2, strbuffer);
        strcpy(strbuffer + (n - len), strbuffer2);

        for (int j = 0; j < n - len; j++)
        {
            strbuffer[j] = '0';
        }
    }
    return strbuffer;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   CreateDir
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

bool CFileIO::CreateDir(const char* NewFolder)
{
#if defined _WIN32
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;
    return CreateDirectory(NewFolder, &sa);
#else
    mkdir(NewFolder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
    return 1;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   CreateDir
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

bool CFileIO::CreateDir(const string& NewFolder)
{
    return CreateDir(NewFolder.c_str());
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   CreateDir
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

char* CFileIO::NewString(const char* OldStr)
{
    char* NewStr = new char[strlen(OldStr) + 1];

    strcpy(NewStr, OldStr);
    return NewStr;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:		ExtractFilename
//
//---------------------------------------------------------------------------

char* CFileIO::ExtractFilename(const char* FullPathName)
{
    const char* slash = strrchr(FullPathName, '/');

    if (slash == NULL)
    {
        slash = strrchr(FullPathName, '\\');

        if (slash == NULL)
        {
            return NewString(FullPathName);
        }
    }
    return NewString(slash + 1);
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:		ExtractPath
//
//---------------------------------------------------------------------------

const char* CFileIO::ExtractPath(const char* FullPathName)
{
    char* PathName = new char[strlen(FullPathName) + 1];

    strcpy(PathName, FullPathName);

    char* slash = strrchr(PathName, '\\');

    // cout << "Slash=" << slash << endl;

    if (slash != NULL)
    {
        slash[1] = 0;
    }
    else
    {
        slash = strrchr(PathName, '/');
        if (slash != NULL)
        {
            slash[1] = 0;
        }
    }
    return PathName;
}
