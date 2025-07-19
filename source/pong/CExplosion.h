//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CExplosion.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CEXPLOSION_H
#define CEXPLOSION_H

#include <vector>
#include <cstdio>
#include "CVectorUnit.h"

class CExplosion : public CVectorUnit
{
    public:

        CExplosion()
        {
            mSpikeVector = NULL;
            mSpikes = 0;
        }


        ~CExplosion();

        void Init(float xpos, float ypos);
        void Draw(int Mode);
        void DrawPoints();

    protected:

        float mStep;
        int mStage;
        int mSpikes;
        CVector2<float>* mSpikeVector;
        int* mSpikeLen;
        std::vector<CVector2<float> > mPointVec;
};

#endif
