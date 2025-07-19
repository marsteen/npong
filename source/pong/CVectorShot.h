//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CVectorShot.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CVECTORSHOT_H
#define CVECTORSHOT_H

#include "CVectorUnit.h"

class CVectorShot : public CVectorUnit
{
    public:

        CVectorShot();


        void Draw(int Mode);
        void Run(SGameContext* gac);
        void SetShotColor(float r, float g, float b, float a);

        int mPlayerNum;


    protected:

        float mShotColor[4];
};


#endif
