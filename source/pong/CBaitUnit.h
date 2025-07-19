//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CBaitUnit.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CBAITUNIT_H
#define CBAITUNIT_H

#include "CVectorUnit.h"

class CBaitUnit : public CVectorUnit
{
    public:

        CBaitUnit();
        void Run(SGameContext* gac);



    protected:

        float mPulsar;
        float mPulsarSpeed;
};

#endif
