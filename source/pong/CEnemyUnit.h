//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CEnemyUnit.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CENEMYUNIT_H
#define CENEMYUNIT_H

#include <pong/CVectorUnit.h>

#define ENEMY_MIN_SPEED		0.8
#define ENEMY_MAX_SPEED		6.0

enum ESpeedStatus
{
    ESPEEDSTATUS_NONE,
    ESPEEDSTATUS_ADD,
    ESPEEDSTATUS_MINUS
};


enum EEnemyType
{
    ETYPE_THIEF,
    ETYPE_FIGHTER,
    ETYPE_BOMBER,
    ETYPE_THIEF2
};

class CEnemyUnit : public CVectorUnit
{
    public:

        CEnemyUnit(EEnemyType et);

        void Run(SGameContext* gac);
        void Destroy();

        //void InitRandomPosition(SGameContext* gco, float* tx, float* ty);
        void InitRandomPosition(SGameContext* gco, float* tx, float* ty);
        void InitRandomPositionPlayfield(SGameContext* gco, float* tx, float* ty);

        EEnemyType mEnemyType;

    protected:

        void ChangeSpeed(const SGameContext* gco);
        void Think(SGameContext* gco, float dx, float dy);
        void SetTarget(const CVectorUnit* vu);
        void CalcBaitAngle();
        void SearchBait(SGameContext* gco);  // Beute suchen


        const CVectorUnit* mTarget;
        CVector2<float> mTargetPos;
        ESpeedStatus mSpeedStatus;
        CVectorUnit* mMyBait;
        int mWaitSearch;
        int mBaitHuntTime;                      // Zeit, die Beute bereits gejagt wird
        int mBaitHuntLimit;                     // Limit fuer jagen von Beute
        float mRotFaktor;
        float mSpeedFaktor;
        float mOldRotFaktor;
        int mAttackPlayerNr;                 // Nummer des anzugreifenden Spielers (0 oder 1)
};

#endif
