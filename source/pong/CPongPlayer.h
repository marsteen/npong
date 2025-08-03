//***************************************************************************
//
//
// @PROJECT  :  npong
// @VERSION  :  1.0
// @FILENAME :  CPongPlayer.h
// @DATE     :  24.8.2024
//
// @AUTHOR   :  Martin Steen
// @EMAIL    :  martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CPONGPLAYER_H
#define CPONGPLAYER_H

#include <vector/CVector2.h>

class CPongPlayer
{
    public:

        CPlayerUnit() : mScore(0), mSpeed(0.0f)
        {}

        int mScore;
        CVector2<float> mPos;
        CVector2<float> mDir;
        float mSpeed;


};

#endif
