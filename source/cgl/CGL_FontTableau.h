//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CGL_FontTableau.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGL_FONTTABLEAU_H
#define CGL_FONTTABLEAU_H

#include <cgl/CGL_Texture.h>
#include <tools/CRectT.h>

class CGL_FontTableau : public CGL_Texture
{
    public:

        bool Load(const char* Folder, const char* FileBase, int wh);
        bool Load(const char* TabFile, const char* AlphaFile, const char* RectFile, int wh);
        void DrawString(const char* Text, int x, int y);
        void DrawStringRaw(const char* Text, float x, float y);
        int FontWidth(const char* tx);
        int FontHeight();


    protected:

        int mWindowHeight;
        CRectT<int> mCharRect[256];
        CRectT<float> mTexRect[256];
};

#endif
