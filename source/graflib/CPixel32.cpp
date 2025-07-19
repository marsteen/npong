//---------------------------------------------------------------------------
//
// PROJECT : Die Planeten
//
//
// AUTOR   : Martin Steen
//           email: martin@martin-steen.de
//
//
//----------------------------------------------------------------------------

#include <iostream>
#include <graflib/CPixel32.h>

using namespace std;

//---------------------------------------------------------------------------
//
// KLASSE        : CPixel32
// METHODE       : operator ==
//
//
//
//---------------------------------------------------------------------------

bool CPixel32::operator==(CPixel32& p2)
{
    return (rgba[0] == p2.rgba[0]) &&
           (rgba[1] == p2.rgba[1]) &&
           (rgba[2] == p2.rgba[2]) &&
           (rgba[3] == p2.rgba[3])
    ;
}


//---------------------------------------------------------------------------
//
// KLASSE        : CPixel32
// METHODE       :
//
//
//
//---------------------------------------------------------------------------

bool CPixel32::operator!=(CPixel32& p2)
{
    return (rgba[0] != p2.rgba[0]) ||
           (rgba[1] != p2.rgba[1]) ||
           (rgba[2] != p2.rgba[2]) ||
           (rgba[3] != p2.rgba[3])
    ;
}


//---------------------------------------------------------------------------
//
// KLASSE        : CPixel32
// METHODE       :
//
//
//
//---------------------------------------------------------------------------

void CPixel32::SwapRedBlue()
{
    unsigned char swap = rgba[0];

    rgba[0] = rgba[2];
    rgba[2] = swap;
}


//---------------------------------------------------------------------------
//
// KLASSE        : CPixel32
// METHODE       :
//
//
//
//---------------------------------------------------------------------------

void CPixel32::Set(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    rgba[0] = r;
    rgba[1] = g;
    rgba[2] = b;
    rgba[3] = a;
}


inline static void Swap(unsigned char* rgba, int a, int b)
{
    unsigned char swap = rgba[a];

    rgba[a] = rgba[b];
    rgba[b] = swap;
}


//---------------------------------------------------------------------------
//
// KLASSE        : CPixel32
// METHODE       : SwapBigEndian
//
//
//
//---------------------------------------------------------------------------

void CPixel32::SwapBigEndian()
{
    Swap(rgba, 0, 2); // Rot und Blau tauschen
}


//---------------------------------------------------------------------------
//
// KLASSE        : CPixel32
// METHODE       :
//
//
//
//---------------------------------------------------------------------------

int CPixel32::Brightness()
{
    return rgba[0] + rgba[1] + rgba[2];
}
