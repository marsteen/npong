//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	GlobalWindow.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef GLOBALWINDOW_H
#define GLOBALWINDOW_H

extern void GlobalSetWindow(int w, int h);
extern int GlobalWindowWidth();
extern int GlobalWindowHeight();
extern int GlobalWindowHeight2();
extern const char* GlobalApplicationName();
extern float GlobalWindowAspect();
extern int GlobalPanelHeight();
extern void GlobalSetPanelHeight(int p);

#endif
