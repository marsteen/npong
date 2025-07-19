//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	main.cpp
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>

#include <global/GlobalDebug.h>
#include <pong/CSdlPong.h>

using namespace std;

// ---------------------------------------------------------------------------
//
//
//
//
// ---------------------------------------------------------------------------

#ifdef _WIN32

// ---------------------------------------------------------------------------
//
// WINDOWS
//
// ---------------------------------------------------------------------------


#include <windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int iCmdShow)
{
    CSdlPong sdlSnake;

    GlobalDebugInit();

    if (sdlSnake.Init())
    {
        sdlSnake.ParseWinArgs(lpCmdLine);
        if (sdlSnake.InitScreen())
        {
            sdlSnake.MainLoop();
        }
    }
    return 0;
}


#else

// ---------------------------------------------------------------------------
//
// UNIX
//
// ---------------------------------------------------------------------------


int main(int argc, char* argv[])
{
    CSdlPong sdlSnake;

    GlobalDebugInit();

    if (sdlSnake.Init())
    {
        sdlSnake.ParseArgs(argc, argv);
        if (sdlSnake.InitScreen())
        {
            sdlSnake.MainLoop();
        }
    }
    return 0;
}


#endif
