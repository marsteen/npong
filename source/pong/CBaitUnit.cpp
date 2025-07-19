//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CBaitUnit.cpp
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include <cgl/CGL_include.h>
#include <file/CFileIO.h>
#include <tools/CStringTool.h>
#include <tools/CRandom.h>
#include <pong/CBaitUnit.h>

using namespace std;

// ---------------------------------------------------------------------------
//
// KLASSE        : CBaitUnit
// METHODE       : CBaitUnit
//
//
//
// ---------------------------------------------------------------------------

CBaitUnit::CBaitUnit()
{
    CRandom Random;

    mPulsar = Random.Get(0.0, 360.0);
    mPulsarSpeed = Random.Get(45, 50);
    mStatus = EUS_BAIT_STAY;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CBaitUnit
// METHODE       : Run
//
//
//
// ---------------------------------------------------------------------------

void CBaitUnit::Run(SGameContext* gac)
{
    //std::cout << "Plusar=" << mPulsar << endl;
    mPulsar += mPulsarSpeed;
    if (mPulsar > 360)
    {
        mPulsar -= 360;
    }
    mShapeParams.mScale = 1.0 + (sin(DEG_TO_RAD(mPulsar)) / 13.0);
}
