//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CGL_Texture.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGL_TEXTURE_H
#define CGL_TEXTURE_H

#include <GL/gl.h>

#include <tools/CRectT.h>
#include <graflib/CGraflib.h>
#include <graflib/CPixel24.h>
#include <graflib/CPixel32.h>

typedef CRectT<int> CRect;

struct STextureParams
{
    STextureParams()
    {
        // GL_LINEAR_MIPMAP_LINEAR | GL_LINEAR | GL_NEAREST
        mMinFilter = GL_LINEAR;
        mMagFilter = GL_LINEAR;
        mCreateMipmap = false;
        mYflip = false;
        mScale2Limit = 0;
    }


    int		mMinFilter;
    int		mMagFilter;
    bool	mCreateMipmap;
    bool	mYflip;
    int		mScale2Limit;
};

class CGL_Texture
{
    public:

        CGL_Texture()
        {
            mTexHandle = 0;
        }


        bool LoadTexture(const char* TextureFilename, STextureParams* tp);
        int LoadTexture(const char* TextureFile, const char* AlphaFile, STextureParams* gp);
        bool LoadTexture(CGraflib* Graflib, STextureParams* tp);

        void CreateEmptyTexture(int xres, int yres, int ByteProPixel, STextureParams* tp);

        bool LoadTransparentTexture(const char* TextureFile, STextureParams* gp);

        int LoadTransparentTexture(const char* ContainerFile, int FileType, int AlphaType,
            SFileReadInfo* FriFile, SFileReadInfo* FriAlpha,
            STextureParams* tp);

        bool SetTexture(void* Pixels24, int SizeX, int SizeY, STextureParams* tp);
        bool LoadShadowMap(char* TextureFilename, STextureParams* tp);
        bool ReplaceTexture(char* TextureFilename, bool yflip);
        void ReplaceTexture(CRect* rc, void* Pixels);
        void SetColor(CRect* rc, void* Color);
        void DeleteTexture();

        unsigned int mTexHandle;
        int mTexWidth;
        int mTexHeight;
        int mTexBitDepth;

    protected:

        CGraflib* CreateGraflibObject(const char* Filename, int* FileType = NULL);
        CPixel32* ConvertPixelARGB32(CPixel* SourceData, int SourceBits, unsigned char* MskPtr, int PicSize);
        void SetClampMode();
        void SetAnisotropy();
        bool TestAlpha(CGraflib* Alpha);

        template<typename Tpixel>
        void DownScale2(STextureParams* tp, CGraflib* dr);
};

#endif
