//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CDebrisUnit.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CDEBRISUNIT_H
#define CDEBRISUNIT_H

class CDebris
{
    public:

        void Draw();

        CVector2<float> mPos;
        CVector2<float> mDir;
        int mLife;
};

class CScrap
{
    public:

        CScrap()
        {
            mColor = NULL;
        }


        void Draw();

        CVector2<float> mShape[3];
        CVector2<float> mPos;
        CVector2<float> mDir;
        int mLife;
        float mRotation;
        float mRotSpeed;
        float* mColor;
};


class CDebrisUnit
{
    public:

        CDebrisUnit();
        ~CDebrisUnit();


        void Init(float xpos, int ypos, int BigFaktor, const float* Color, const CVector2<float>& dvec);
        bool Draw();

    protected:

        CDebris* mDebris;
        CScrap* mScrap;
        float mScrapColor[4];

        int mDebrisCount;
        int mScrapCount;
};

#endif
