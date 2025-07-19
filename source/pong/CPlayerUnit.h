//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CPlayerUnit.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CPLAYERUNIT_H
#define CPLAYERUNIT_H

#include "CVectorUnit.h"

class CPlayerUnit : public CVectorUnit
{
    public:

        CPlayerUnit();
        void Run(SGameContext* gac);
        void MoveForward();
        void Move();
        void Draw(int Mode);
        void Reset();


        int mTimeOut;                  // Warteezeit nach Player-Explosion
        bool mLeftTurn;
        bool mRightTurn;
        bool mMoveForward;
        bool mMoveBackward;
        float mRotSpeed;
        int mNumber;                   // Spielernummer: 0 oder 1
};

#endif
