//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CGL_Patch.cpp
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************


#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <cmath>
#include <cgl/CGL_include.h>
#include <cgl/CVertexArrays.h>
#include <cgl/CGL_Patch.h>

using namespace std;

//---------------------------------------------------------------------------
//
// Klasse:    CGL_Object
// Methode:   SetSphereVertex
//
//
//---------------------------------------------------------------------------

void CGL_Patch::SetSphereVertex(CVector3<float>* Origin, CVector3<float>* cf)
{
    CVector3<float> norm; // (0,0,1);

    norm.SubtractVector(cf, Origin);
    norm.Normalize();

    glNormal3fv(&norm.x);
    glVertex3fv(&cf->x);
}


#if 1

#define FTEX1    1.0 // 0.99999

//---------------------------------------------------------------------------
//
// Klasse:    CGL_Patch
// Methode:   MakePatch
//
//
//---------------------------------------------------------------------------

void CGL_Patch::MakePatch(float StartS, float StartT, float StepS, float StepT, int PsegS, int PsegT)
{
    float TexCoordStepS = FTEX1 / PsegS;
    float TexCoordStepT = FTEX1 / PsegT;

    float AngleS1 = StartS;
    float TexCoordS1 = FTEX1;

    CVector3<float> Origin(0, 0, 0);

    for (int s = 0; s < PsegS; s++)
    {
        glBegin(GL_TRIANGLE_STRIP);

        float AngleT = StartT + (M_PI / 2);
        float TexCoordT = FTEX1;

        float AngleS2 = AngleS1 + StepS;
        float TexCoordS2 = TexCoordS1 - TexCoordStepS;

        for (int t = 0; t <= PsegT; t++)
        {
            CVector3<float> vert;

            vert.x = cos(AngleT) * mSCircleRad;
            vert.y = sin(AngleT) * mTCircleRad;
            vert.z = 0;

            vert.RotationXZ(&Origin, sin(AngleS1), cos(AngleS1));

            glTexCoord2f(TexCoordS1, TexCoordT);
            SetSphereVertex(&Origin, &vert);

            vert.x = cos(AngleT) * mSCircleRad;
            vert.y = sin(AngleT) * mTCircleRad;
            vert.z = 0;

            vert.RotationXZ(&Origin, sin(AngleS2), cos(AngleS2));

            glTexCoord2f(TexCoordS2, TexCoordT);
            SetSphereVertex(&Origin, &vert);

            AngleT -= StepT;
            TexCoordT -= TexCoordStepT;
        }

        AngleS1 += StepS;
        TexCoordS1 -= TexCoordStepS;

        glEnd();
    }
}


#endif


#if 1
//---------------------------------------------------------------------------
//
// Klasse:    CGL_Patch
// Methode:   MakePatchDrawElements
//
//
//---------------------------------------------------------------------------

void CGL_Patch::MakePatchDrawElements(float StartS, float StartT, float StepS, float StepT, int PsegS, int PsegT)
{
    float TexCoordStepS = (FTEX1 / PsegS);
    float TexCoordStepT = (-FTEX1 / PsegT);

    float AngleS = StartS;
    float TexCoordS = FTEX1;

    CVector3<float> NormalVector;

    PsegS += 1;
    PsegT += 1;


    //int nElems = (PsegS + 1) * (PsegT + 1);
    int nElems = PsegS * PsegT;

    CVector3<float> Origin(0, 0, 0);

    CVertexArrays vr;

    CVector3<float>* va = vr.MakeVertexArray(nElems);
    CVector3<float>* na = vr.MakeNormalArray(nElems);
    CVector2<float>* ta = vr.MakeTexCoordArray(nElems);
    unsigned short* ix = vr.MakeIndexArray(PsegT * 2);

    // Vertex, Normal und TexCoord Arrays berechnen:

    for (int s = 0; s < PsegS; s++)
    {
        float AngleT = StartT + (M_PI / 2);
        float TexCoordT = 0;

        for (int t = 0; t < PsegT; t++)
        {
            CVector3<float> Vertex;

            Vertex.x = cos(AngleT) * mSCircleRad;
            Vertex.y = sin(AngleT) * mTCircleRad;
            Vertex.z = 0;

            Vertex.RotationXZ(&Origin, sin(AngleS), cos(AngleS));

            NormalVector.SubtractVector(&Vertex, &Origin);
            NormalVector.Normalize();

            *(va++) = Vertex;           // Vertex speichern
            *(na++) = NormalVector;     // Normale speichern
            ta->x = TexCoordS;          // Texturkoordinaten speichern
            ta->y = TexCoordT;
            ta++;

            TexCoordT -= TexCoordStepT;
            AngleT -= StepT;
        }

        AngleS += StepS;
        TexCoordS -= TexCoordStepS;
    }

    glVertexPointer(3, GL_FLOAT, 0, vr.mVertex);
    glNormalPointer(GL_FLOAT, 0, vr.mNormal);
    glTexCoordPointer(2, GL_FLOAT, 0, vr.mTexCoord);

    // Index-Arrays berechnen und Triangle-Strips erzeugen:

    int k = 0;

//	for (int s = 0; s < PsegS-1; s++)
    for (int s = 0; s < PsegS-1; s++)
    {
        ix = vr.mIndex;

/*
 *      for (int t = 0; t < PsegT; t++)
 *      {
 *(ix++) = k;
 *(ix++) = k + PsegT;
 *
 *    k++;
 *      }
 *
 *      glDrawElements(GL_TRIANGLE_STRIP, PsegT * 2, GL_UNSIGNED_SHORT, vr.mIndex);
 */

        glBegin(GL_TRIANGLE_STRIP);
        for (int t = 0; t < PsegT; t++)
        {
            glTexCoord2fv(vr.mTexCoord[k].v());
            glNormal3fv(vr.mNormal[k].v());
            glVertex3fv(vr.mVertex[k].v());

            glTexCoord2fv(vr.mTexCoord[k + PsegT].v());
            glNormal3fv(vr.mNormal[k + PsegT].v());
            glVertex3fv(vr.mVertex[k + PsegT].v());
            k++;
        }
        glEnd();
    }
}


#endif


void CGL_Patch::MakePatchDrawElementsST(float StartS, float StartT, float StepS, float StepT, int PsegS, int PsegT)
{
    float TexCoordStepS = 1.0;
    float TexCoordStepT = 1.0;

    float AngleS = StartS;
    float TexCoordS = 0.0;

    CVector3<float> NormalVector;

    PsegS += 1;
    PsegT += 1;


    int nElems = PsegS * PsegT;

    CVector3<float> Origin(0, 0, 0);

    CVertexArrays vr;

    CVector3<float>* va = vr.MakeVertexArray(nElems);
    CVector3<float>* na = vr.MakeNormalArray(nElems);
    CVector2<float>* ta = vr.MakeTexCoordArray(nElems);
    unsigned short* ix = vr.MakeIndexArray(PsegT * 2);

    // Vertex, Normal und TexCoord Arrays berechnen:

//	TexCoordS =

    float StartTexS = 0.0;

    for (int s = 0; s < PsegS; s++)
    {
        float AngleT = StartT + (M_PI / 2);
        float TexCoordT = 0;

        //TexCoordS = StartTexS;

        for (int t = 0; t < PsegT; t++)
        {
            CVector3<float> Vertex;

            Vertex.x = cos(AngleT) * mSCircleRad;
            Vertex.y = sin(AngleT) * mTCircleRad;
            Vertex.z = 0;

            Vertex.RotationXZ(&Origin, sin(AngleS), cos(AngleS));

            NormalVector.SubtractVector(&Vertex, &Origin);
            NormalVector.Normalize();

            *(va++) = Vertex;           // Vertex speichern
            *(na++) = NormalVector;     // Normale speichern

            float f = fabs(cos(AngleT));
            if (f == 0.0)
            {
                f = 0.01;
            }

            ta->x = TexCoordS; //(AngleS / (M_PI*2.0)) * 6; //PsegS;          // Texturkoordinaten speichern0
            ta->y = TexCoordT;
            ta++;

            TexCoordT += 0.1;

            AngleT -= StepT;
        }

        AngleS += StepS;
        TexCoordS += 0.1;
    }

    glVertexPointer(3, GL_FLOAT, 0, vr.mVertex);
    glNormalPointer(GL_FLOAT, 0, vr.mNormal);
    glTexCoordPointer(2, GL_FLOAT, 0, vr.mTexCoord);

    // Index-Arrays berechnen und Triangle-Strips erzeugen:

    int k = 0;

    for (int s = 0; s < PsegS-1; s++)
    {
        ix = vr.mIndex;

/*
 *      for (int t = 0; t < PsegT; t++)
 *      {
 *(ix++) = k;
 *(ix++) = k + PsegT;
 *
 *    k++;
 *      }
 *      glDrawElements(GL_TRIANGLE_STRIP, PsegT * 2, GL_UNSIGNED_SHORT, vr.mIndex);
 */
        glBegin(GL_TRIANGLE_STRIP);
        for (int t = 0; t < PsegT; t++)
        {
            glTexCoord2fv(vr.mTexCoord[k].v());
            glNormal3fv(vr.mNormal[k].v());
            glVertex3fv(vr.mVertex[k].v());

            glTexCoord2fv(vr.mTexCoord[k + PsegT].v());
            glNormal3fv(vr.mNormal[k + PsegT].v());
            glVertex3fv(vr.mVertex[k + PsegT].v());
            k++;
        }
        glEnd();
    }
}


#if 0
//---------------------------------------------------------------------------
//
// Klasse:    CGL_Patch
// Methode:   MakePatchNotTexture
//
//
//---------------------------------------------------------------------------

void CGL_Patch::MakePatchNotTexture(float StartS, float StartT, float StepS, float StepT, int PsegS, int PsegT)
{
    float AngleS = StartS;
    float TexCoordS = FTEX1;

    CVector3<float> NormalVector;

    PsegS += 1;
    PsegT += 1;


    int nElems = (PsegS + 1) * (PsegT + 1);

    CVector3<float> Origin(0, 0, 0);

    CArrayListElem* al = new CArrayListElem;

    CVector3<float>* va = al->MakeVertexArray(nElems);
    CVector3<float>* na = al->MakeNormalArray(nElems);
    unsigned short* ix = al->MakeIndexArray(PsegT * 2);

    for (int s = 0; s < PsegS; s++)
    {
        float AngleT = StartT + (M_PI / 2);
        float TexCoordT = 0;

        for (int t = 0; t < PsegT; t++)
        {
            CVector3<float> Vertex;

            Vertex.x = cos(AngleT) * mSCircleRad;
            Vertex.y = sin(AngleT) * mTCircleRad;
            Vertex.z = 0;

            Vertex.RotationXZ(&Origin, sin(AngleS), cos(AngleS));



            NormalVector.SubtractVector(&Vertex, &Origin);
            NormalVector.Normalize();


            *(va++) = Vertex;           // Vertex speichern
            *(na++) = NormalVector;     // Normale speichern

            AngleT -= StepT;
        }

        AngleS += StepS;
    }


    glVertexPointer(3, GL_FLOAT, 0, al->mVertex);
    glNormalPointer(GL_FLOAT, 0, al->mNormal);

    // Index-Arrays berechnen und Triangle-Strips erzeugen:

    int k = 0;

    for (int s = 0; s < PsegS-1; s++)
    {
        ix = al->mIndex;

        for (int t = 0; t < PsegT; t++)
        {
            *(ix++) = k;
            *(ix++) = k + PsegT;

            k++;
        }

        glDrawElements(GL_TRIANGLE_STRIP, PsegT * 2, GL_UNSIGNED_SHORT, al->mIndex);
    }
    delete al;
}


#endif
