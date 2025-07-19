//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	SGameContext.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef SGAMECONTEXT_H
#define SGAMECONTEXT_H

#include <list>
#include <tools/CRectT.h>
#include <pong/CVectorUnit.h>

struct SGameContext
{
    SGameContext()
    {
        mPlayer = NULL;
        mBaitList = NULL;
        mEnemyMaxSpeed = 2.2;
        mBaitStolen = false;
        mShooter = NULL;
        mShootTime = 25;
    }


    float CenterX() { return mPlayField.Width() / 2.0; }
    float CenterY() { return mPlayField.Height() / 2.0; }

    CRectT<float>				mPlayField;
    bool						mLeftButton;
    bool						mRightButton;

    float						mEnemyMaxSpeed;
    CVectorUnit*				mPlayer;
    int							mPlayers;
    std::list<CVectorUnit*>*	mBaitList;
    CVectorUnit*				mShooter;
    int							mShootTime;
    int							mBaitStolen;
};

#endif
