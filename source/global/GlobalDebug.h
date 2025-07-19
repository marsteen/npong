//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	GlobalDebug.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef GLOBALDEBUG_H
#define GLOBALDEBUG_H

#include <sstream>

#define DEBUG_LEVEL_0		0
#define DEBUG_LEVEL_10		10
#define DEBUG_LEVEL_STD		10
#define DEBUG_LEVEL_100		100
#define DEBUG_LEVEL_200		200
#define DEBUG_LEVEL_300		300
#define DEBUG_LEVEL_400		400
#define DEBUG_LEVEL_500		500
#define DEBUG_LEVEL_600		600
#define DEBUG_LEVEL_700		700
#define DEBUG_LEVEL_800		800
#define DEBUG_LEVEL_900		900

enum
{
    DBG11	= 11,
    DBG12	= 12,
    DBG13	= 13,
    DBG14	= 14,
    DBG15	= 15,
    DBG16	= 16,
    DBG17	= 17,
    DBG18	= 18,
    DBG19	= 19,
    DBG20	= 20
};

enum EInitStage
{
    EINITSTAGE_START,
    EINITSTAGE_INIT,
    EINITSTAGE_RUN,
    EINITSTAGE_HALT
};

extern void GlobalDebug(const char* txt, int DebugLevel = DEBUG_LEVEL_STD);
extern void GlobalDebug(const char* txt1, const char* txt2, int DebugLevel = DEBUG_LEVEL_STD);
extern void GlobalDebug(const std::stringstream& mstr, int DebugLevel = DEBUG_LEVEL_STD);
extern void GlobalDebug1(const char* txt, int DebugLevel = DEBUG_LEVEL_STD);
extern void GlobalDebug1(const char* txt1, const char* txt2, int DebugLevel = DEBUG_LEVEL_STD);
extern void GlobalDebug1(const std::stringstream& mstr, int DebugLevel = DEBUG_LEVEL_STD);
extern void GlobalDebugInit();
extern void GlobalDebugEmpty();
extern void GlobalShowError(const char* t);
extern void GlobalShowError(const std::stringstream& mstr);
extern void GlobalShowOpenGLError(const char* Function = NULL);
extern void GlobalSetInitStage(EInitStage s);
extern EInitStage GlobalGetInitStage();


#endif
