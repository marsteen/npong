//------------------------------------------------------------------------------
//
// PROJECT : Imagon
//
// FILE    : CGraflibPng.cpp
//
// VERSION : 1.0
//
// AUTOR   : Martin Steen
//           Imagon GmbH
//
//
//
//------------------------------------------------------------------------------
//
// Inhalt: Deklaration der Klasse CGraflibPng
//
//------------------------------------------------------------------------------
// Revisionsgeschichte:
//
// 08.01.2001 erstellt - Martin Steen
//
//---------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <graflib/CGraflibPng.h>
#include <file/SFileReadInfo.h>
#include <mvpng/mv_graphics_png.h>

using namespace std;



//---------------------------------------------------------------------------
//
// Klasse:    CGraflibPng
// Methode:   Read
//
//
//---------------------------------------------------------------------------

bool CGraflibPng::Read(const char* Filename, SFileReadInfo* fri)
{
    int fileoffset = (fri == nullptr) ? 0 : fri->mFilePosition;    
    return mv_graphics_png_read(Filename, (char**) &mData, &mWidth, &mHeight, &mBits, fileoffset);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGraflibPng
// Methode:   Write
//
//
//---------------------------------------------------------------------------

int CGraflibPng::Write(const char* Filename, CFileIO* fio)
{
    //return mv_graphics_png_write(const char* png_file, const char* png_data, int png_width, int png_height, int png_bits);
    return 0;
}
