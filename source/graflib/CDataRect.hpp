//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CDataRect.hpp
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

inline bool CDataRect::GetPixel1Bit(int xpos, int ypos)
{
    static int sBitTab[] = { 128, 64, 32, 16, 8, 4, 2, 1 };
    unsigned char* PixelBuffer = (unsigned char*)mData;
    int Offset = (ypos * (mWidth >> 3)) + (xpos >> 3);

    return PixelBuffer[Offset] & sBitTab[xpos & 7];
}


//---------------------------------------------------------------------------
//
// Klasse:    CGraphicsBmp
// Methode:		GetPixel1Bit
//
//
//
//
//
//---------------------------------------------------------------------------

inline bool CDataRect::GetPixel1BitOffset(int LineOffset, int xpos)
{
    static int sBitTab[] = { 128, 64, 32, 16, 8, 4, 2, 1 };
    unsigned char* PixelBuffer = (unsigned char*)mData;
    int Offset = LineOffset + (xpos >> 3);

    return PixelBuffer[Offset] & sBitTab[xpos & 7];
}
