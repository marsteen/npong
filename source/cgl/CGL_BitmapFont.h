//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CGL_BitmapFont.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGL_BITMAPFONT_H
#define CGL_BITMAPFONT_H

// CGL_BitmapFont is a class which encapsulates the details necessary
// to draw bitmapped text in OpenGL on the Windows platform.

class CGL_BitmapFont
{
    public:

        //CGL_BitmapFont(CDC* dc, char* fontname);
        ~CGL_BitmapFont();

        void DrawStringAt(GLfloat x, GLfloat y, GLfloat z, char* s);

    private:

        GLuint m_listbase;
        CDC* m_pDC;

    private:

        // Hide these.
        CGL_BitmapFont() { }
        CGL_BitmapFont(const CGL_BitmapFont& obj) { }
        CGL_BitmapFont& operator=(const CGL_BitmapFont& obj) { return *this; }
};

#endif // CGL_BITMAPFONT
