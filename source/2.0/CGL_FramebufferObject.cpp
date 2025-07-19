//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CGL_FramebufferObject.cpp
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************


#include <GL/glew.h>
//#include <GLinclude.h>
#include <CGL_FramebufferObject.h>
#include <NGLprimitives.h>
#include <CGL_NGO_BlurShader.h>
#include <CRandom.h>

#include <iostream>

static CGL_NGO_BlurShader* NoiseShader;

using namespace std;

// ---------------------------------------------------------------------------
//
// KLASSE        : CGL_FramebufferObject
// METHODE       : DrawTexture
//
// ---------------------------------------------------------------------------

#if 0
// Framebuffer anlegen

void CGL_FramebufferObject::CreateFramebufferObject(int Width, int Height)
{
    mWidth = Width;
    mHeight = Height;


    glGenFramebuffers(1, &mFBhandle);
    glGenRenderbuffers(1, &mRenderBuffer);
    glGenTextures(1, &mTexture);


    glBindFramebuffer(GL_FRAMEBUFFER, mFBhandle);
    glBindTexture(GL_TEXTURE_2D, mTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexture, 0);

    {
        GLenum Buffers = GL_COLOR_ATTACHMENT0;
        glDrawBuffers(1, &Buffers);
    }

    glBindRenderbuffer(GL_RENDERBUFFER, mRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, Width, Height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 /* GL_DEPTH_ATTACHMENT */, GL_RENDERBUFFER, mRenderBuffer);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


#endif

// ---------------------------------------------------------------------------
//
// KLASSE        : CGL_FramebufferObject
// METHODE       : DrawTexture
//
// ---------------------------------------------------------------------------


void CGL_FramebufferObject::CreateFramebufferObject(int Width, int Height)
{
    //Debug("CreateFramebufferObject START");

    glewInit();

    mWidth = Width;
    mHeight = Height;

    glEnable(GL_TEXTURE_2D);
    glGenFramebuffers(1, &mFBhandle);
    glBindFramebuffer(GL_FRAMEBUFFER, mFBhandle);



    //Create a color renderbuffer, allocate storage for it, and attach it to the framebuffer�s color attachment point.
    //GLuint colorRenderbuffer;

    glGenRenderbuffers(1, &mColorRenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, mColorRenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, Width, Height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, mColorRenderbuffer);


/*
 * //Create a depth or depth/stencil renderbuffer, allocate storage for it, and attach it to the framebuffer�s depth attachment point.
 *
 * glGenRenderbuffers(1, &mDepthRenderbuffer);
 * glBindRenderbuffer(GL_RENDERBUFFER, mDepthRenderbuffer);
 * glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, Width, Height);
 * glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthRenderbuffer);
 */
// Textur erzeugen

    glGenTextures(1, &mTexture);
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // oder GL_NEAREST
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexture, 0);

    //Test the framebuffer for completeness. This test only needs to be performed when the framebuffer�s configuration changes.

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        // Debug("***** GL_FRAMEBUFFER_COMPLETE failed: Status=", status);
    }
    else
    {
        // Debug("Framebuffer complete!");
    }



    // Textur erzeugen und verlinken



    {
        //GLenum Buffers = GL_COLOR_ATTACHMENT0;
        //  glDrawBuffers(1, &Buffers);
    }

    // Textur und Framebuffer deaktivieren:

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    //Debug("CreateFramebufferObject OK");
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGL_FramebufferObject
// METHODE       : DrawTexture
//
// ---------------------------------------------------------------------------
//
// Zeichnen in den Framebuffer aktivieren:

void CGL_FramebufferObject::DrawToFrameBuffer(bool Enable)
{
    if (Enable)
    {
        glEnable(GL_TEXTURE_2D);
        glBindFramebuffer(GL_FRAMEBUFFER, mFBhandle);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_TEXTURE_2D);
    }
    else
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGL_FramebufferObject
// METHODE       : DrawTexture
//
// ---------------------------------------------------------------------------

void CGL_FramebufferObject::DrawTexture() const
{
    CRectT<float> vrc;

    vrc.Set(0, 0, mWidth, mHeight);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, mTexture);
    NGLprimitives::DrawTexture(&vrc);
    glDisable(GL_TEXTURE_2D);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGL_FramebufferObject
// METHODE       : DrawTexture
//
// ---------------------------------------------------------------------------

void CGL_FramebufferObject::DrawTexture(int Width, int Height) const
{
    if (NoiseShader == NULL)
    {
        glewInit();
        NoiseShader = new CGL_NGO_BlurShader;
        NoiseShader->InitShaders("files/shader/noise.vert", "files/shader/noise.frag", "./files/debug");
    }

    CRectT<float> vrc;

    vrc.Set(0, 0, Width, Height);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    NoiseShader->UseShader(true);
    NoiseShader->SetUniformInt("uShaderMode", 0);
    //NoiseShader->SetUniform("uFboSize", 1, 1);
    NoiseShader->SetUniform("uNoiseSeed", CRandom::Get01(), CRandom::Get01());


    NGLprimitives::DrawTexture(&vrc);
    NoiseShader->UseShader(false);
    glDisable(GL_TEXTURE_2D);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGL_FramebufferObject
// METHODE       : DrawTexture
//
// ---------------------------------------------------------------------------

void CGL_FramebufferObject::DrawTexture(const CRectT<float>* vrc) const
{
    glBindTexture(GL_TEXTURE_2D, mTexture);
    NGLprimitives::DrawTexture(vrc);
}
