//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	GlobalSystemFunctions.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef GLOBAL_SYSTEM_FUNCTIONS_H
#define GLOBAL_SYSTEM_FUNCTIONS_H

namespace GlobalSystem
{

    void setPath(const std::string& path);
    std::string getPath(const std::string& filename);
    
    inline char getPathDiv()
    {
    #ifdef _WIN32
        return '\\';
    #else
        return '/';
    #endif
    }

    //---------------------------------------------------------------------------
    //
    // Klasse:    static
    // Methode:		SwapWord
    //
    //---------------------------------------------------------------------------

    inline static void swapWord(short* w)
    {
        char s;
        char* c = (char*)w;

        s = c[0];
        c[0] = c[1];
        c[1] = s;
    }


    //---------------------------------------------------------------------------
    //
    // Klasse:    static
    // Methode:		SwapWord
    //
    //---------------------------------------------------------------------------

    inline static short swapWord(short w)
    {
        char s;
        char* c = (char*)&w;

        s = c[0];
        c[0] = c[1];
        c[1] = s;
        return w;
    }


    //---------------------------------------------------------------------------
    //
    // Klasse:    static
    // Methode:	  SwapDword
    //
    //---------------------------------------------------------------------------

    inline static void swapDword(int* dw)
    {
        int s = *dw;
        char* c1 = (char*)dw;
        char* c2 = (char*)&s;

        c1[0] = c2[3];
        c1[1] = c2[2];
        c1[2] = c2[1];
        c1[3] = c2[0];
    }


    //---------------------------------------------------------------------------
    //
    // Klasse:    static
    // Methode:		BigEndian
    //
    // Rueckgabe:  true - Prozessor ist Big-Endian (MIPS, MC68000, PowerPC)
    //             false - Prozessor ist Little-Endian (Intel x86)
    //
    //---------------------------------------------------------------------------
    
    inline static bool isEndianModeBig()
    {
        short test = 0x1234;
        return (*((char*)&test) == 0x12);
    }
}


#endif
