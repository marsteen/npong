//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CGL_Texture.cpp
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <GL/glew.h>
#include <iostream>
#include <fstream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <math.h>

#include <file/CFileIO.h>
#include <tools/CRectT.h>
#include <vector/CVector3T.h>
#include <graflib/CPixel24.h>
#include <graflib/CPixel32.h>
#include <graflib/CGraflibTga.h>
#include <graflib/CGraflibPng.h>

#ifdef USE_JPEG
#include <graflib/CGraflibJpeg.h>
#endif

#ifdef USE_PNG
#include <graflib/CGraflibPng.h>
#endif

#include <tools/CException.h>
#include <cgl/CGL_Texture.h>
#include <global/GlobalDebug.h>

using namespace std;
//#define HAS_GLU

//---------------------------------------------------------------------------
//
// Klasse:    static
// Methode:		GetStandardParams
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

static STextureParams* GetStandardParams(STextureParams* tp)
{
    static STextureParams stdtp;

    if (tp == NULL)
    {
        return &stdtp;
    }
    return tp;
}

//---------------------------------------------------------------------------
//
// Klasse:    CGL_Texture
// Methode:		DeleteTexture
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_Texture::DeleteTexture()
{
    if (mTexHandle != 0)
    {
        glDeleteTextures(1, &mTexHandle);
        mTexHandle = 0;
    }
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Texture
// Methode:		SetTexture
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

bool CGL_Texture::SetTexture(void* Pixels24, int SizeX, int SizeY, STextureParams* tp)
{
    bool Status = false;

    tp = GetStandardParams(tp);

    if (Pixels24 != NULL)               //
    {
        glGenTextures(1, &mTexHandle);  // Create One Texture
        //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glBindTexture(GL_TEXTURE_2D, (int)mTexHandle);

        if (tp->mCreateMipmap)
        {
#ifdef HAS_GLU
            SetClampMode();
            SetAnisotropy();

            gluBuild2DMipmaps(GL_TEXTURE_2D, 3,
                SizeX,
                SizeY,
                GL_RGB, GL_UNSIGNED_BYTE,
                Pixels24);
#endif
        }
        else
        {
            //       GL_LINEAR
            // oder  GL_NEAREST

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tp->mMagFilter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tp->mMinFilter);

            SetClampMode();
            SetAnisotropy();

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SizeX, SizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, Pixels24);
        }

        mTexWidth = SizeX;
        mTexHeight = SizeY;
        mTexBitDepth = 24;

        Status = true;
    }
    return Status;                                  // Return The Status
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Texture
// Methode:		SetClampMode
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_Texture::SetClampMode()
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);    //
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);    //
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Texture
// Methode:		SetAnisotropy
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_Texture::SetAnisotropy()
{
    float Anisotropy;

    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &Anisotropy);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, Anisotropy);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Texture
// Methode:		LoadTexture
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------


extern void GlobalShowOpenGLError(void);

bool CGL_Texture::LoadTexture(const char* TextureFilename, STextureParams* tp)
{
    //cout << "CGL_Texture::LoadTexture START file" << TextureFilename << endl;
    CGraflib* Graflib;
    CFileIO fio;
    bool Status = false;

    tp = GetStandardParams(tp);

    switch (fio.GuessFileFormat(TextureFilename))
    {
        case EFILETYPE_PNG:

            Graflib = new CGraflibPng;
            break;

        case EFILETYPE_TGA:

            // Debug2 << "TGA FILE" << DBLF;
            Graflib = new CGraflibTga;
            break;

        default:
            std::cout << "***** CGL_Texture::LoadTexture unknown format:" << TextureFilename << std::endl;
            break;
        }

    GlobalDebug("Reading..");

    try
    {
        Graflib->Read(TextureFilename);
    }
    catch (CGraflibException& ex)
    {
        stringstream mstr;
        std::cout  <<  "***** Datei nicht gefunden: " <<  TextureFilename << std::endl;
        mTexHandle = 0;
        exit(0);
    }

    int Format;

    {
        stringstream mstr;

        cout << "Filename=" << TextureFilename << endl;
        cout << "    Graflib->mBits=" << Graflib->mBits << endl;
        cout << "    W=" << Graflib->mWidth << " H=" << Graflib->mHeight << endl;
        cout << "    mCreateMipmap=" << tp->mCreateMipmap << endl;
        //GlobalDebug(mstr);
    }


    if (Graflib->mBits == 24)
    {
        // Debug2 << "Format: GL_RGB" << DBLF;
        Format = GL_RGB;
    }
    else
    if (Graflib->mBits == 32)
    {
        GlobalDebug("Format=GL_RGBA");
        Format = GL_RGBA;
    }



    //gGlobalTextureParams.mBildfilter.ApplyFilter(Pixels, SizeX * SizeY * 3);

    glGenTextures(1, &mTexHandle);              // Create One Texture
    GlobalShowOpenGLError(__func__);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, (int)mTexHandle);
    GlobalShowOpenGLError(__func__);

    {
        stringstream mstr;
        mstr << "CGL_Texture::LoadTexture Texure handle=" << mTexHandle;
        GlobalDebug(mstr);
    }

    if (tp->mCreateMipmap)
    {
#ifdef HAS_GLU
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tp->mMagFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tp->mMinFilter);

        SetClampMode();
        SetAnisotropy();

        gluBuild2DMipmaps(GL_TEXTURE_2D,
            Graflib->mBits / 8,
            Graflib->mWidth,
            Graflib->mHeight,
            Format,
            GL_UNSIGNED_BYTE,
            Graflib->mData);
#endif
    }
    else
    {
        //       GL_LINEAR
        // oder  GL_NEAREST

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tp->mMagFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tp->mMinFilter);

        SetClampMode();
        SetAnisotropy();

        glTexImage2D(GL_TEXTURE_2D, 0, Format, Graflib->mWidth, Graflib->mHeight, 0, Format, GL_UNSIGNED_BYTE, Graflib->mData);
    }

    mTexWidth = Graflib->mWidth;
    mTexHeight = Graflib->mHeight;
    mTexBitDepth = Graflib->mBits;

    // Debug2 << " W=" << mTexWidth << '\n';
    // Debug2 << " H=" << mTexHeight << '\n';

    delete Graflib->mData;
    delete Graflib;

    Status = true;
    //GlobalDebug("CGL_Texture::LoadTexture OK ");

    return Status;
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Texture
// Methode:		LoadTexture
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

bool CGL_Texture::LoadTexture(CGraflib* Graflib, STextureParams* tp)
{
    tp = GetStandardParams(tp);

    if (Graflib != NULL)
    {
        int Format;

        if (Graflib->mBits == 24)
        {
            // Debug2 << "Format: GL_RGB" << DBLF;
            Format = GL_RGB;
        }
        else
        if (Graflib->mBits == 32)
        {
            // Debug2 << "Format: GL_RGBA" << DBLF;
            Format = GL_RGBA;
        }



        //gGlobalTextureParams.mBildfilter.ApplyFilter(Pixels, SizeX * SizeY * 3);

        glGenTextures(1, &mTexHandle);              // Create One Texture
        //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glBindTexture(GL_TEXTURE_2D, (int)mTexHandle);

        if (tp->mCreateMipmap)
        {
#ifdef HAS_GLU
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tp->mMagFilter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tp->mMinFilter);

            SetClampMode();
            SetAnisotropy();

            gluBuild2DMipmaps(GL_TEXTURE_2D,
                Graflib->mBits / 8,
                Graflib->mWidth,
                Graflib->mHeight,
                Format,
                GL_UNSIGNED_BYTE,
                Graflib->mData);
#endif
        }
        else
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tp->mMagFilter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tp->mMinFilter);

            SetClampMode();
            SetAnisotropy();

            glTexImage2D(GL_TEXTURE_2D, 0, Format, Graflib->mWidth, Graflib->mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, Graflib->mData);
        }

        mTexWidth = Graflib->mWidth;
        mTexHeight = Graflib->mHeight;
        mTexBitDepth = Graflib->mBits;
    }

    return true;                                    // Return The Status
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Texture
// Methode:		LoadTransparentTexture
//
// Parameter: TextureFile - Name der Textur-Datei
//
// Return:
//
// Unterst?tzt werden die Formate:
//
// PNG 24, 32 Bit (Alpha)
// JPG 24 Bit
// TGA 24 Bit
//
//---------------------------------------------------------------------------

bool CGL_Texture::LoadTransparentTexture(const char* TextureFile, STextureParams* tp)
{
    bool r = true;
    CGraflib* GrafFile;
    CFileIO fio;
    bool Status = false;
    int Format, Format2;

    tp = GetStandardParams(tp);

    switch (fio.GuessFileFormat(TextureFile))
    {
#ifdef USE_JPEG
        case EFILETYPE_JPG:

            GrafFile = new CGraflib;
            break;
#endif

#ifdef USE_PNG
        case EFILETYPE_PNG:

            GrafFile = new CGraflibPng;
            break;
#endif

        case EFILETYPE_TGA:

            GrafFile = new CGraflibTga;
            break;

        default:
        {
            stringstream mstr;
            mstr << __func__ << "Texture not known: " << TextureFile;
            GlobalShowError(mstr);
            r = false;
        }
    }

    if (!GrafFile->Read(TextureFile))
    {
        stringstream mstr;
        mstr << __func__ << "Texture not known: " << TextureFile;
        GlobalShowError(mstr);
        r = false;

        exit(0);
        r = false;
    }

    Format = GL_RGBA;
    mTexBitDepth = GrafFile->mBits;

    if (mTexBitDepth == 24)
    {
        Format = GL_RGB;
        Format2 = GL_RGB;
    }
    else
    if (mTexBitDepth == 32)
    {
        Format = GL_RGBA;
        Format2 = GL_RGBA;
    }
    else
    if (mTexBitDepth == 8)
    {
        Format = GL_ALPHA8;
        Format2 = GL_ALPHA;
    }
    else
    {
        char msgbuff[512];
        sprintf(msgbuff, "Unsupported Bitformat in: %s %d", TextureFile, mTexBitDepth);
        GlobalShowError(msgbuff);
        exit(0);
    }

    // Debug2 << "Filename=" << TextureFile << " W=" << GrafFile->mWidth << " Bits=" << GrafFile->mBits << DBLF;

    if (tp->mYflip)
    {
        GrafFile->Yflip();
    }

    glGenTextures(1, &mTexHandle);              // Create One Texture
    glBindTexture(GL_TEXTURE_2D, mTexHandle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tp->mMinFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tp->mMagFilter);

    SetClampMode();
    SetAnisotropy();

    glTexImage2D(GL_TEXTURE_2D, 0, Format,
        GrafFile->mWidth,
        GrafFile->mHeight,
        0, Format2, GL_UNSIGNED_BYTE,
        GrafFile->mData);

    mTexWidth = GrafFile->mWidth;
    mTexHeight = GrafFile->mHeight;
    delete[] GrafFile->mData;
    delete   GrafFile;

    return r;
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Texture
// Methode:		TestAlpha
//
// Parameter:
//
// Return:     Falls Alpha-Maske leer ist: false
//             Sonst: true
//
//---------------------------------------------------------------------------

bool CGL_Texture::TestAlpha(CGraflib* Alpha)
{
    char* DataPtr = (char*)Alpha->mData;

    for (int y = 0; y < Alpha->mHeight; y++)
    {
        for (int x = 0; x < Alpha->mWidth; x++)
        {
            if (*DataPtr != 0)
            {
                return true;
            }
            DataPtr++;
        }
    }
    return false;
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Texture
// Methode:		CreateGraflibObject
//
// Parameter:
//
//
//---------------------------------------------------------------------------


CGraflib* CGL_Texture::CreateGraflibObject(const char* Filename, int* FileType)
{
    CFileIO fio;
    int ft;
    CGraflib* GrafFile = NULL;

    switch (fio.GuessFileFormat(Filename))
    {
#ifdef USE_JPEG
        case EFILETYPE_JPG:

            GrafFile = new CGraflib;
            ft = EFILETYPE_JPG;
            break;
#endif

#ifdef USE_PNG
        case EFILETYPE_PNG:

            GrafFile = new CGraflibPng;
            ft = EFILETYPE_PNG;
            break;
#endif


        case EFILETYPE_TGA:

            GrafFile = new CGraflibTga;
            ft = EFILETYPE_TGA;
            break;

        default:
        {
            stringstream mstr;
            mstr << __func__ << "CGL_TextureU: unbekanntes Texturformat Dateiname: " << Filename;
            GlobalShowError(mstr);
            ft = EFILETYPE_UNKNOWN;
        }
    }

    if (FileType != NULL)
    {
        *FileType = ft;
    }

    return GrafFile;
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Texture
// Methode:
//
// Parameter:
//
// Return:		0 - Fehler beim Laden
//            1 - Alles ok
//            2 - Alpha-Maske leer (Textur nicht erzeugt)
//
//---------------------------------------------------------------------------


int CGL_Texture::LoadTexture(const char* TextureFile, const char* AlphaFile, STextureParams* tp)
{
    GlobalDebug("CGL_Texture::LoadTexture Alpha START File=", TextureFile);

    int r;
    CGraflib* GrafFile = CreateGraflibObject(TextureFile);
    CGraflib* GrafAlpha = CreateGraflibObject(AlphaFile);
    bool Status = false;
    int Format;

    tp = GetStandardParams(tp);

    if (AlphaFile != NULL)
    {
        Format = GL_RGBA;
        mTexBitDepth = 32;
    }
    else
    {
        Format = GL_RGB;
        mTexBitDepth = 24;
        GrafAlpha = NULL;
    }

    try
    {
        if (!GrafFile->Read(TextureFile))
        {
            throw (CException(0, TextureFile));
        }

        if (Format == GL_RGBA)
        {
            if (!GrafAlpha->Read(AlphaFile))
            {
                throw (CException(0, AlphaFile));
            }
            else
            {
                if (!TestAlpha(GrafAlpha))
                {
                    throw (CException(1));
                }


                GrafFile->InterleaveAlpha(GrafAlpha);

                if ((GrafFile->mWidth != GrafAlpha->mWidth) ||
                    (GrafFile->mHeight != GrafAlpha->mHeight))
                {
                    // Debug2 << "***** CGL_Texture::LoadTransparentTexture Gr??e verschieden: "
                    //			 << TextureFile << " und " << AlphaFile << DBLF;
                }
            }
        }
        DeleteTexture();

        if (tp->mYflip)
        {
            GrafFile->Yflip();
        }

        glGenTextures(1, &mTexHandle);              // Create One Texture
        glBindTexture(GL_TEXTURE_2D, mTexHandle);

        /*
         *  CreateMipmap = true;
         *  gGlobalTextureParams.mMagFilter = GL_LINEAR;
         *  gGlobalTextureParams.mMinFilter = GL_LINEAR;
         */

        if (tp->mCreateMipmap)
        {
#ifdef HAS_GLU
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tp->mMagFilter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tp->mMinFilter);
            SetClampMode();
            SetAnisotropy();


            //	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            //	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

            gluBuild2DMipmaps(GL_TEXTURE_2D,
                GrafFile->mBits / 8,
                GrafFile->mWidth,
                GrafFile->mHeight,
                Format,
                GL_UNSIGNED_BYTE,
                GrafFile->mData);
#endif

            // Debug2 << "  Textur MIT Mipmap erzeugt!" << DBLF;
        }
        else
        {
            //     GL_LINEAR
            // or  GL_NEAREST


            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tp->mMagFilter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tp->mMinFilter);

            SetClampMode();
            SetAnisotropy();

            glTexImage2D(GL_TEXTURE_2D, 0, Format,
                GrafFile->mWidth,
                GrafFile->mHeight,
                0, Format, GL_UNSIGNED_BYTE,
                GrafFile->mData);

            // Debug2 << "  Textur OHNE Mipmap erzeugt!" << DBLF;
        }
        mTexWidth = GrafFile->mWidth;
        mTexHeight = GrafFile->mHeight;

        r = 1;
    }
    catch (CException& ce)
    {
        stringstream mstr;
        if (ce.mErrstr == NULL)
        {
            mstr << "***** Textur ladefehler Num=" << ce.mErrnum;
        }
        else
        {
            mstr << "***** Textur ladefehler:" << ce.mErrstr << " Num=" << ce.mErrnum;
        }

        GlobalDebug(mstr);
        //GlobalShowError("Textur Ladefehler #1");
        switch (ce.mErrnum)
        {
            case 0:

                if (ce.mErrstr != NULL)
                {
                    GlobalShowError(mstr);
                }
                r = 0;
                break;

            case 1:

                GlobalShowError(mstr);
                r = 2;
                break;
        }
    }

    if (GrafFile != NULL)
    {
        delete[] GrafFile->mData;
        delete   GrafFile;
    }
    if (GrafAlpha != NULL)
    {
        delete[] GrafAlpha->mData;
        delete   GrafAlpha;
    }


    GlobalDebug("CGL_Texture::LoadTexture Alpha OK");


    // Debug2 << "CGL_Texture::LoadTransparentTexture OK" << DBLF;

    return r;
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Texture
// Methode:		DownScale2
//
// Wenn mScale2Limit nicht 0 ist werden Texturen skaliert, falls
// die Texturgr??e mScale2Limit ?berschreitet
//
//---------------------------------------------------------------------------

template<typename Tpixel>
void CGL_Texture::DownScale2(STextureParams* tp, CGraflib* glib)
{
    if (tp->mScale2Limit > 0)
    {
        if (glib->mWidth >= tp->mScale2Limit)
        {
            int NewWidth = glib->mWidth / 2;
            int NewHeight = glib->mHeight / 2;

            CPixel32* NewData = new CPixel32[NewWidth * NewHeight];
            CPixel32* OldData = (CPixel32*)glib->mData;

            CPixel32* NewDataPtr = NewData;
            CPixel32* OldDataPtr = OldData;

            for (int y = 0; y < NewHeight; y++)
            {
                glib->DownScaleLine2(OldDataPtr, NewDataPtr, glib->mWidth * sizeof(Tpixel));
                OldDataPtr += glib->mWidth * 2;
                NewDataPtr += NewWidth;
            }
            delete[] OldData;
            glib->mData = NewData;
            glib->mWidth = NewWidth;
            glib->mHeight = NewHeight;
        }
    }
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Texture
// Methode:		LoadTransparentTexture
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

int CGL_Texture::LoadTransparentTexture(const char* ContainerFile, int FileType, int AlphaType,
    SFileReadInfo* FriFile, SFileReadInfo* FriAlpha,
    STextureParams* tp)
{
    //// Debug2 << DBON;

/*
 *  // Debug2 << "CGL_Texture::LoadTransparentTexture START" << DBLF;
 *  // Debug2 << "  Texturefile: " << TextureFile << DBLF;
 *  // Debug2 << "  AlphaFile: " << AlphaFile << DBLF;
 */
    int r = 0;
    CGraflib* GrafFile = NULL;
    CGraflib* GrafAlpha = NULL;
    CFileIO fio;
    bool Status = false;
    int Format;

    tp = GetStandardParams(tp);

    switch (FileType)
    {
#ifdef USE_JPEG
        case EFILETYPE_JPG:

            GrafFile = new CGraflibJpeg;
            break;
#endif

#ifdef USE_PNG
        case EFILETYPE_PNG:

            GrafFile = new CGraflibPng;
            break;
#endif


        case EFILETYPE_TGA:

            GrafFile = new CGraflibTga;
            break;

        default:
        {
            char msgbuff[512];
            sprintf(msgbuff, "CGL_Texture::LoadTransparentTexture Texture not known");
            GlobalShowError(msgbuff);
        }
    }


    if (AlphaType != EFILETYPE_VOID)
    {
        Format = GL_RGBA;
        mTexBitDepth = 32;
        switch (AlphaType)
        {
#ifdef USE_JPEG
            case EFILETYPE_JPG:

                GrafAlpha = new CGraflibJpeg;
                break;
#endif

#ifdef USE_PNG
            case EFILETYPE_PNG:

                GrafAlpha = new CGraflibPng;
                break;
#endif


            case EFILETYPE_TGA:

                GrafAlpha = new CGraflibTga;
                break;
        }
    }
    else
    {
        Format = GL_RGB;
        mTexBitDepth = 24;
        GrafAlpha = NULL;
    }

    try
    {
        if (!GrafFile->Read(ContainerFile, FriFile))
        {
            throw (CException(0, "CGL_Texture::LoadTransparentTexture Texture nicht gefunden"));
        }


        if (Format == GL_RGBA)
        {
            // Debug2 << DBON;
            // Debug2 << "Reading Alpha-Data" << DBLF;


            if (!GrafAlpha->Read(ContainerFile, FriAlpha))
            {
                throw (CException(0, "Alpha-Texture not Found"));
            }

            if (!TestAlpha(GrafAlpha))
            {
                throw (CException(1));
            }
            GrafFile->InterleaveAlpha(GrafAlpha);

            if ((GrafFile->mWidth != GrafAlpha->mWidth) ||
                (GrafFile->mHeight != GrafAlpha->mHeight))

            {
                throw (CException(0, "Alpha-Textur und Grafik verschieden gro?"));
            }



            DownScale2<CPixel32>(tp, GrafFile);
        }
        else
        {
            DownScale2<CPixel24>(tp, GrafFile);
        }

        DeleteTexture();


/*
 *      extern bool gHaltet;
 *
 *      char msg[256];
 *      sprintf(msg, "W=%d H=%d B=%d", GrafFile->mWidth, GrafFile->mHeight, GrafFile->mBits);
 *      gHaltet = true;
 *      ShowError(msg);
 *      gHaltet = false;
 *
 *
 *      //exit(0);
 *
 *      GrafFile->DownScaleFix2(GrafFile->mWidth / 2, GrafFile->mHeight / 2);
 */
        glGenTextures(1, &mTexHandle);              // Create One Texture
        glBindTexture(GL_TEXTURE_2D, mTexHandle);



        if (tp->mCreateMipmap)
        {
#ifdef HAS_GLU
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

            SetClampMode();
            SetAnisotropy();

            gluBuild2DMipmaps(GL_TEXTURE_2D, mTexBitDepth/8,
                GrafFile->mWidth,
                GrafFile->mHeight,
                Format, GL_UNSIGNED_BYTE,
                GrafFile->mData);
#endif
        }
        else
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tp->mMagFilter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tp->mMinFilter);

            SetClampMode();
            SetAnisotropy();

            glTexImage2D(GL_TEXTURE_2D, 0, Format,
                GrafFile->mWidth,
                GrafFile->mHeight,
                0, Format, GL_UNSIGNED_BYTE,
                GrafFile->mData);
        }


        mTexWidth = GrafFile->mWidth;
        mTexHeight = GrafFile->mHeight;
        r = 1;
    }
    catch (CException& ce)
    {
        switch (ce.mErrnum)
        {
            case 0:

                if (ce.mErrstr != NULL)
                {
                    GlobalShowError(ce.mErrstr);
                    // Debug2 << "***** " << ce.mErrstr << DBLF;
                }
                r = 0;
                break;

            case 1:

                r = 2;
                break;
        }
    }

    if (GrafFile != NULL)
    {
        delete[] GrafFile->mData;
        delete   GrafFile;
    }
    if (GrafAlpha != NULL)
    {
        delete[] GrafAlpha->mData;
        delete   GrafAlpha;
    }


    // Debug2 << "CGL_Texture::LoadTransparentTexture OK r=" << r << DBLF;

    return r;
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Texture
// Methode:   ReplaceTexture
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_Texture::ReplaceTexture(CRect* rc, void* Pixels)
{
    glBindTexture(GL_TEXTURE_2D, mTexHandle);
    //glTexSubImage2D(GL_TEXTURE_2D, 0,0,0, rc->Width(), rc->Height(), GL_RGBA, GL_UNSIGNED_BYTE, Pixels);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mTexWidth, mTexHeight, GL_RGBA, GL_UNSIGNED_BYTE, Pixels);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Texture
// Methode:   SetColor
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_Texture::SetColor(CRect* rc, void* Color)
{
    int Size = rc->Width() * rc->Height();
    //int Size = mTexWidth * mTexHeight;

    unsigned int* ColorField = new unsigned int[Size];

    for (int i = 0; i < Size; i++)
    {
        ColorField[i] = *((unsigned int*)Color);
    }

    glBindTexture(GL_TEXTURE_2D, mTexHandle);
    glTexSubImage2D(GL_TEXTURE_2D, 0, rc->left, mTexHeight - rc->bottom, rc->Width(), rc->Height(), GL_RGBA, GL_UNSIGNED_BYTE, ColorField);

    delete[] ColorField;
}


#if 0
//---------------------------------------------------------------------------
//
// Klasse:    CGL_Texture
// Methode:   ReplaceTexture
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

bool CGL_Texture::ReplaceTexture(char* TextureFilename, bool yflip)
{
    CGraficsLoader GrafLoad;


    int SizeX, SizeY;
    int PixelSize;

    void* Pixels = GrafLoad.ReadGraficsFile(TextureFilename, &SizeX, &SizeY, mTexBitDepth);

    if (Pixels != NULL)
    {
        //gGlobalTextureParams.mBildfilter.ApplyFilter(Pixels, SizeX * SizeY * 3);

        //// Debug2 << "ReadGraficsFile OK SizeX=" << SizeX << " SizeY=" << SizeY << DBLF;

        GrafLoad.Swapper(Pixels, SizeX, SizeY, true, yflip, mTexBitDepth);

        //// Debug2 << "Swapper OK" << DBLF;

        glBindTexture(GL_TEXTURE_2D, mTexHandle);

        //// Debug2 << "glBindTexture OK" << DBLF;

        switch (mTexBitDepth)
        {
            case 8:
                PixelSize = GL_ALPHA;
                break;

            case 24:
                PixelSize = GL_RGB;
                break;

            case 32:
                PixelSize = GL_RGBA;
                break;
        }

        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, SizeX, SizeY, PixelSize, GL_UNSIGNED_BYTE, Pixels);

        delete[] Pixels;
    }
    else
    {
        //		// Debug2 << "***** CGL_Texture::ReplaceTexture File not found:" << TextureFilename << DBLF;
    }
}


#endif

#if 1
//---------------------------------------------------------------------------
//
// Klasse:    CGL_Texture
// Methode:		LoadShadowMap
//
//
//---------------------------------------------------------------------------

bool CGL_Texture::LoadShadowMap(char* TextureFilename, STextureParams* tp)
{
    CGraflib* Alpha = CreateGraflibObject(TextureFilename);

    cout << "SizeX=" << mTexWidth << endl;
    cout << "SizeY=" << mTexHeight << endl;

    tp = GetStandardParams(tp);

    if (Alpha->mData != NULL)   // Load Particle Texture
    {
        mTexWidth = Alpha->mWidth;
        mTexHeight = Alpha->mHeight;

        glGenTextures(1, &mTexHandle);              // Create One Texture
        //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glBindTexture(GL_TEXTURE_2D, mTexHandle);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tp->mMagFilter);  // GL_LINEAR); // only first two can be used
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tp->mMinFilter);  //GL_LINEAR); // all of the above can be used

        SetClampMode();
        SetAnisotropy();

        glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA8, mTexWidth, mTexHeight, 0, GL_ALPHA, GL_UNSIGNED_BYTE, Alpha->mData);

        //cout << "Textur OHNE Mipmap erzeugt!" << endl;

        mTexBitDepth = 8;

        delete[] Alpha->mData;
    }
    else
    {
        return false;
    }
    delete Alpha;

    return true;                                    // Return The Status
}


#endif

//---------------------------------------------------------------------------
//
// Klasse:    CGL_Object
// Methode:   ConvertPixelARGB32
//
// Konvertieren in das 32-Bit Zielpixelformat RGBA32
//
// SourceBits: 24 Bits oder 32 Bits
//
//---------------------------------------------------------------------------

CPixel32* CGL_Texture::ConvertPixelARGB32(CPixel* SourceData, int SourceBits, unsigned char* MaskData, int PicSize)
{
    CPixel32* DstPixel32;

    if (SourceBits == 24)
    {
        DstPixel32 = new CPixel32[PicSize];

        CPixel24* PicPtr = (CPixel24*)SourceData;
        CPixel32* DstPtr = DstPixel32;
        unsigned char* MaskPtr = MaskData;

        for (int i = 0; i < PicSize; i++)
        {
            DstPtr->rgba[0] = PicPtr->rgb[2];
            DstPtr->rgba[1] = PicPtr->rgb[1];
            DstPtr->rgba[2] = PicPtr->rgb[0];
            DstPtr->rgba[3] = *(MaskPtr++);

/*
 *          DstPtr->rgba[0] = PicPtr->rgb[0];
 *          DstPtr->rgba[1] = PicPtr->rgb[1];
 *          DstPtr->rgba[2] = PicPtr->rgb[2];
 *          DstPtr->rgba[3] = *(MskPtr++);
 */


            DstPtr++;
            PicPtr++;
        }
        delete[] SourceData;
        delete[] MaskData;
    }
    else
    {
        unsigned char* MaskPtr = MaskData;
        CPixel32* DstPixel32 = (CPixel32*)SourceData;
        CPixel32* DstPtr = DstPixel32;

        for (int i = 0; i < PicSize; i++)
        {
            DstPtr->rgba[3] = *(MaskPtr++);
            DstPtr++;
        }
        delete[] MaskData;
    }

    return DstPixel32;
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Texture
// Methode:		CreateEmptyTexture
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_Texture::CreateEmptyTexture(int xres, int yres, int ByteProPixel, STextureParams* tp)
{
    int ColorType = GL_ALPHA;

    char* DummyPixels = new char[xres * yres * ByteProPixel];

    memset(DummyPixels, 0, xres * yres * ByteProPixel);

    tp = GetStandardParams(tp);

    glGenTextures(1, &mTexHandle);              // Create One Texture
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, mTexHandle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tp->mMagFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tp->mMinFilter);

    SetClampMode();
    SetAnisotropy();

    switch (ByteProPixel)
    {
        case 1:
            ColorType = GL_ALPHA;
            break;

        case 3:
            ColorType = GL_RGB;
            break;

        case 4:
            ColorType = GL_RGBA;
            break;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, ColorType, xres, yres, 0, ColorType, GL_UNSIGNED_BYTE, DummyPixels);

    mTexWidth = xres;
    mTexHeight = yres;
    mTexBitDepth = 24;

    delete[] DummyPixels;
}
