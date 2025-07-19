//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CEnemyUnit.cpp
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
#include <tools/CRectT.h>
#include <tools/CStringTool.h>
#include <tools/CRandom.h>
#include <pong/CEnemyUnit.h>
#include <pong/CAngle.h>
#include <pong/SGameContext.h>

using namespace std;

extern float gGlobalScale;

//---------------------------------------------------------------------------
//
// Klasse:    CEnemyUnit
// Methode:   CEnemyUnit
//
//
//---------------------------------------------------------------------------

CEnemyUnit::CEnemyUnit(EEnemyType et)
{
    mTargetPos.Set(0, 0);
    mSpeedStatus = ESPEEDSTATUS_ADD;
    mSpeed = 0;
    mMyBait = 0;
    mStatus = EUS_ENY_START;
    mRotFaktor = 1.0;
    mOldRotFaktor = 1.0;
    mSpeedFaktor = 1.0;
    mAttackPlayerNr = -1;
    mEnemyType = et; // ETYPE_BOMBER; //ETYPE_FIGHTER; //ETYPE_THIEF;
}


//---------------------------------------------------------------------------
//
// Klasse:    CVectorUnit
// Methode:   SetTarget
//
//
//---------------------------------------------------------------------------

void CEnemyUnit::SetTarget(const CVectorUnit* vu)
{
    mTarget = vu;
}


#define ENEMY_ANGLE_FAKT    2.0



//---------------------------------------------------------------------------
//
// Klasse:    CEnemyUnit
// Methode:   Run
//
//
//---------------------------------------------------------------------------

void CEnemyUnit::Run(SGameContext* gco)
{
    CAngle<float> Angle;
    float dx = PosX() - mTargetPos.x; // gac->mPlayerPos->x;
    float dy = PosY() - mTargetPos.y;

    float TargetAngle = RAD_TO_DEG(atan2(dx, -dy));
    float diff = Angle.Diff(180.0 - mShapeParams.mRotation, 360.0 - TargetAngle);
    float rot;
    float MaxRot = ENEMY_ANGLE_FAKT * mRotFaktor;
    float av;

    if (mStatus == EUS_ENY_AVOID)
    {
        av = -1.0;
    }
    else
    {
        av = 1.0;
    }
    //cout << "diff=" << diff<<  endl;
    //AddRotation(-diff);

#if 1
    if (fabs(diff) > MaxRot)
    {
        if (diff < 0)
        {
            AddRotation(MaxRot * av);
        }
        else
        {
            AddRotation(-MaxRot * av);
        }
    }
    else
    {
        if (mEnemyType == ETYPE_BOMBER)
        {
            if (mStatus == EUS_ENY_ATTACK)
            {
                if (gco->mPlayField.InRect(PosX(), PosY()))
                {
                    if (gco->mShootTime <= 0)
                    {
                        gco->mShooter = this; // jetzt schiessen
                        gco->mShootTime = 75;
                    }
                }
            }
        }

        AddRotation(-diff * av);
    }
#endif



    mShapeParams.mPosition += (mDirection * gGlobalScale);
    mDirection.x = mSpeed * mShapeParams.mSinRotation * mSpeedFaktor;
    mDirection.y = -mSpeed * mShapeParams.mCosRotation * mSpeedFaktor;

    ChangeSpeed(gco);
    Think(gco, dx, dy);
    //
}


//---------------------------------------------------------------------------
//
// Klasse:    CEnemyUnit
// Methode:   Destroy
//
//
//---------------------------------------------------------------------------

void CEnemyUnit::Destroy()
{
    if (mMyBait != NULL)
    {
        // Beute freilassen
        //cout << "Beute freigelassen" << endl;
        mMyBait->mStatus = EUS_BAIT_STAY;
        mMyBait = NULL;
    }
    CVectorUnit::Destroy();
}


//---------------------------------------------------------------------------
//
// Klasse:    CEnemyUnit
// Methode:   Think
//
//
//---------------------------------------------------------------------------

void CEnemyUnit::ChangeSpeed(const SGameContext* gco)
{
    switch (mSpeedStatus)
    {
        case ESPEEDSTATUS_ADD:

            mSpeed += 0.02;
            if (mSpeed >= gco->mEnemyMaxSpeed)
            {
                mSpeed = gco->mEnemyMaxSpeed;
                mSpeedStatus = ESPEEDSTATUS_NONE;
            }
            break;

        case ESPEEDSTATUS_MINUS:

            mSpeed -= 0.02;
            if (mSpeed <= ENEMY_MIN_SPEED)
            {
                mSpeed = ENEMY_MIN_SPEED;
                mSpeedStatus = ESPEEDSTATUS_NONE;
            }
            break;
    }
}


//---------------------------------------------------------------------------
//
// Klasse:    CEnemyUnit
// Methode:   InitRandomPosition
//
//
//---------------------------------------------------------------------------

void CEnemyUnit::InitRandomPosition(SGameContext* gco, float* tx, float* ty)
{
    CRandom random;

    CVector2<float> mf(gco->CenterX(), gco->CenterY());
    float TargetAngle = DEG_TO_RAD(random.Get(0, 360));

    *tx = (sin(TargetAngle) * mf.x) * 1.5 + mf.x;
    *ty = (cos(TargetAngle) * mf.y) * 1.5 + mf.y;
}


//---------------------------------------------------------------------------
//
// Klasse:    CEnemyUnit
// Methode:   InitRandomPositionPlayfield
//
//
//---------------------------------------------------------------------------

void CEnemyUnit::InitRandomPositionPlayfield(SGameContext* gco, float* tx, float* ty)
{
    CRandom random;

    CVector2<float> mf(gco->CenterX(), gco->CenterY());
    float TargetAngle = DEG_TO_RAD(random.Get(0, 360));

    *tx = (sin(TargetAngle) * mf.x) * 0.5 + mf.x;
    *ty = (cos(TargetAngle) * mf.y) * 0.5 + mf.y;
}


//---------------------------------------------------------------------------
//
// Klasse:    CEnemyUnit
// Methode:   CalcBaitAngle
//
//
//---------------------------------------------------------------------------

void CEnemyUnit::CalcBaitAngle()
{
    CAngle<float> Angle;
    float diff = Angle.Diff(mShapeParams.mRotation, mMyBait->mShapeParams.mRotation);

    if (diff < 0)
    {
        if (diff < -90)
        {
            mMyBait->AddRotation(90.0);
        }

        mMyBait->AddRotation(1.0);
    }
    else
    {
        if (diff > 90)
        {
            mMyBait->AddRotation(-90.0);
        }
        mMyBait->AddRotation(-1.0);
    }
}


//---------------------------------------------------------------------------
//
// Klasse:    CEnemyUnit
// Methode:   Think
//
//
//---------------------------------------------------------------------------

void CEnemyUnit::Think(SGameContext* gco, float dx, float dy)
{
    switch (mStatus)
    {
        //
        // Beute suchen
        //
        case EUS_ENY_START:
            switch (mEnemyType)
            {
                case ETYPE_THIEF:

                    mRotFaktor = 1.0;
                    SearchBait(gco);
                    break;

                case ETYPE_THIEF2:

                    mRotFaktor = 0.8;
                    mSpeedFaktor = 1.0 / 0.8;
                    SearchBait(gco);
                    break;

                case ETYPE_FIGHTER:
                {
                    CRandom Random;
                    if (Random.Get(0, 10) < 1.0)
                    {
                        mStatus = EUS_ENY_ATTACK;
                    }
                    else
                    {
                        mStatus = EUS_ENY_CIRCLE;
                        mWaitSearch = Random.GetInt(100, 150);
                        InitRandomPositionPlayfield(gco, &mTargetPos.x, &mTargetPos.y);
                    }
                    mSpeed = ENEMY_MAX_SPEED;
                    mSpeedStatus = ESPEEDSTATUS_NONE;
                    mRotFaktor = 0.6;
                }
                break;

                case ETYPE_BOMBER:

                    mStatus = EUS_ENY_ATTACK;
                    mSpeed = ENEMY_MAX_SPEED / 3;
                    mSpeedStatus = ESPEEDSTATUS_NONE;
                    mRotFaktor = 0.3;
                    SearchBait(gco);
                    break;
            }

            break;

        //
        // Kurs auf Beute nehmen
        //
        case EUS_ENY_GOBAIT:
        {
            float dist = sqrt(dx * dx + dy * dy);
            if (dist < 10.0)
            {
                mSpeedStatus = ESPEEDSTATUS_MINUS;
                if (dist < 5.0)
                {
                    // Beute erreicht, jetzt noch 24 Einheiten vorwaerts fahren
                    // um Beute anzudocken
                    mStatus = EUS_ENY_GOHOME1;
                    DirOffset(24.0 * gGlobalScale, &mTargetPos);
                    mRotFaktor = mOldRotFaktor;
                }
            }
            if (mBaitHuntTime++ >= mBaitHuntLimit)
            {
                if (mRotFaktor < 1.0)
                {
                    mRotFaktor = 1.0;
                    mBaitHuntLimit = 500;
                }
                else
                {
                    CRandom Random;
                    mOldRotFaktor = mRotFaktor;
                    mRotFaktor = Random.Get(0.1, 0.3);
                    mBaitHuntLimit = 50;
                }
                mBaitHuntTime = 0;
            }
        }
        break;

        //
        // Kollision vermeinden:
        //

        case EUS_ENY_AVOID:



            break;

        //
        // Spieler angreifen
        //
        case EUS_ENY_ATTACK:
        {
            CRandom Random;

            if (mAttackPlayerNr == -1)
            {
                if (gco->mPlayers == 2)
                {
                    mAttackPlayerNr = Random.GetInt(0, 1);
                }
                else
                {
                    mAttackPlayerNr = 0;
                }
            }

            if (gco->mPlayer->mStatus == EUS_PLAYER_RUN)
            {
                CVectorUnit* player = gco->mPlayer + mAttackPlayerNr;
                mTargetPos.x = player->PosX();
                mTargetPos.y = player->PosY();

                if ((mEnemyType == ETYPE_THIEF) ||
                    (mEnemyType == ETYPE_THIEF2))
                {
                    if (--mWaitSearch <= 0)
                    {
                        mStatus = EUS_ENY_START;
                    }
                }
            }
        }
        break;

        case EUS_ENY_CIRCLE:
        {
            float dist = sqrt(dx * dx + dy * dy);

            mWaitSearch -= 1;

            if ((dist < 5.0) || (mWaitSearch < 0))
            {
                // Ziel erreicht oder Timeout
                mStatus = EUS_ENY_START;
            }
        }
        break;

        case EUS_ENY_GOHOME1:
        {
            float dist = sqrt(dx * dx + dy * dy);
            if (dist < 5.0)
            {
                // Beute erreicht, jetzt nach Hause fahren
                mSpeedStatus = ESPEEDSTATUS_ADD;
                mStatus = EUS_ENY_GOHOME2;
                InitRandomPosition(gco, &mTargetPos.x, &mTargetPos.y);
            }
        }
        break;


        //
        // Mit Beute nach Hause fahren
        //
        case EUS_ENY_GOHOME2:
            if (mMyBait != NULL)
            {
                CVector2<float> BaitPos;
                DirOffset(-24 * gGlobalScale, &BaitPos);
                //BaitPos.x = PosX() - mShapeParams.mSinRotation * 24;
                //BaitPos.y = PosY() + mShapeParams.mCosRotation * 24;

                //mMyBait->SetPosition(PosX(), PosY());

                mMyBait->SetPosition(BaitPos.x, BaitPos.y);
                CalcBaitAngle();
                //float dist = sqrt(dx * dx + dy * dy);

                // Befindet sich Bait noch im Spielfeld oder nicht?
                if (!gco->mPlayField.InRect(BaitPos.x, BaitPos.y))
                {
                    // angekommen - loeschen
                    mMyBait->Destroy();
                    gco->mBaitStolen = true;
                    mStatus = EUS_INACTIVE; // Einheit loeschen
                    //EUS_ENY_START;
                }
            }
            break;
    }
}


//---------------------------------------------------------------------------
//
// Klasse:    CEnemyUnit
// Methode:   Think
//
//
//---------------------------------------------------------------------------


void CEnemyUnit::SearchBait(SGameContext* gco)
{
    bool BaitFound = false;
    vector<CVectorUnit*> BaitVec;
    CRandom Random;

    for (list<CVectorUnit*>::iterator it = gco->mBaitList->begin();
        it != gco->mBaitList->end();
        ++it)
    {
        BaitVec.push_back(*it);
    }
    int BaitIndexStart = Random.GetInt(0, BaitVec.size());

    int BaitVecSize = BaitVec.size();

    for (int i = 0; (i < BaitVecSize) && !BaitFound; i++)
    {
        int bi = BaitIndexStart + i;
        if (bi >= BaitVecSize)
        {
            bi -= BaitVecSize;
        }
        CVectorUnit* Bait = BaitVec[bi];

        if (Bait->mStatus == EUS_BAIT_STAY)
        {
            CVector2<float> BaitTargetPos;
            mStatus = EUS_ENY_GOBAIT;
            mTarget = Bait;
            mTargetPos.x = mTarget->PosX();
            mTargetPos.y = mTarget->PosY();
            Bait->mStatus = EUS_BAIT_HIJACKED;
            mMyBait = Bait;
            BaitFound = true;
            mBaitHuntTime = 0;
            mBaitHuntLimit = 500;
        }
    }
    if (!BaitFound)
    {
        CRandom Random;
        mStatus = EUS_ENY_ATTACK;
        mWaitSearch = Random.GetInt(100, 500);
        //cout << "not found!" << endl;
    }
}
