//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	COpenGL.cpp
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <iostream>
#include <fstream>

using namespace std;

#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glut.h>
#include <CFileIO.h>
#include "COpenGL.h"

// ---------------------------------------------------------------------------
//
// METHODE       : SetViewport
//
// KLASSE        : COpenGL
//
// RETURN        : -
//
// PARAMETER     : int width
//                 int height  - Breite und Hoehe des Fensters
//
// BESCHREIBUNG  : Initialisieren der Parameter
//
// HISTORY       :
//
// 1.11.1998 erstellt
//
// ---------------------------------------------------------------------------

void COpenGL::SetViewport(int w, int h)
{
    mWidth = w;
    mHeight = h;

    //glEnable(GL_CULL_FACE);
    //glDepthFunc(GL_LESS);              // The Type Of Depth Test To Do
    //glDisable(GL_DEPTH_TEST);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    //SetupLighting();

    glViewport(0, 0, mWidth, mHeight);
    mAspect = (float)mWidth / (mHeight);
    //StartModelView();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    //glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    //ViewportAction(w, h);
}


#if 0
//---------------------------------------------------------------------------
//
// Klasse:    COpenGL
// Methode:   StartModelView
//
//
//---------------------------------------------------------------------------

void COpenGL::StartModelView()
{
    mAspect = (float)mWidth / (mHeight);
    glViewport(0, 0, mWidth, mHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, mAspect, 0.1, 2000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}


#endif

//---------------------------------------------------------------------------
//
// Klasse:    COpenGL
// Methode:   StartProjectionView
//
//
//---------------------------------------------------------------------------

void COpenGL::StartProjectionView()
{
    glViewport(0, 0, mWidth, mHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0, mWidth, 0.0, mHeight, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
}


//---------------------------------------------------------------------------
//
// Klasse:    COpenGL
// Methode:   StartProjectionView
//
//
//---------------------------------------------------------------------------

void COpenGL::StartProjectionView(int Width, int Height) const
{
    glViewport(0, 0, mWidth, mHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    glOrtho(0.0, Width, 0.0, Height, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
}


//


#if 0
// ---------------------------------------------------------------------------
//
// METHODE       : SetupLighting
//
// KLASSE        : COpenGL
//
// RETURN        :
//
// PARAMETER     :
//
// BESCHREIBUNG  :
//
//  OpenGL Lichtquellen konfigurieren
//
// HISTORY       :
//
// 1.11.1998 erstellt
//
// ---------------------------------------------------------------------------

void COpenGL::SetupLighting()
{
    GLfloat Position1[] = { -3000.0, 0.0, 6000.0, 0, 0 };

    GLfloat matSpecular[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat matShininess[] = { 30.0 };

/*
 *
 * GLfloat BlueLight[]    = {0.0, 0.0, 1.0, 1.0};
 * GLfloat OrangeLight[]  = {1.0, 0.5, 0.0, 1.0};
 * GLfloat BlackLight[]   = {0,0,0, 1.0};
 * GLfloat DarkLight[]    = { 0.5, 0.5, 0.5, 1.0 };
 */
    GLfloat WhiteLight[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat LightAmbient[] = { 0.2, 0.2, 0.2, 1.0 };

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShininess);

    mLightPosition.Set(Position1[0], Position1[1], Position1[2]);

    glLightfv(GL_LIGHT0, GL_POSITION, Position1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, WhiteLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, WhiteLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glEnable(GL_NORMALIZE);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightAmbient);


    //glEnable(GL_DEPTH_TEST);

    // Rueckseiten der Polygone nicht zeichnen
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);


    //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}


#endif
