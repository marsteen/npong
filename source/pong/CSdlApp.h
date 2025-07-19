//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CSdlApp.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CSDLAPP_H
#define CSDLAPP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_joystick.h>

#include <iostream>
#include <vector>
#include <string>
#include <global/GlobalSystemFunctions.h>
#include <cgl/CGL_OpenGL.h>


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlApp
//
// ---------------------------------------------------------------------------

class CSdlApp
{
    public:

        CSdlApp();


        bool Init();
        void ParseArgs(int argc, char* argv[]);
        void ParseWinArgs(const char* Commandline);
        bool InitScreen();
        void EventLoop();
        void MainLoop();
        void Finish();
        virtual void Timer();
        virtual void GameLoop();
        virtual void InitGame();
        virtual void FinishGame();
        virtual void ResetPlayers() { };
        virtual void moveJoyAxis(int joystick, int axis, int axisValue) { };

    protected:

        void ParseArgVec(const std::vector<std::string>& ArgStr);
        void DisableKeyRepeat();
        bool GetVideoModes(int* FirstW, int* FirstH, int n);
        void forceFullHD(SDL_Window* window);
        virtual bool ParseKeys(SDL_Keycode key, bool down);
        virtual void JoystickButtonAction(int nr, int type, int jbutton) { };
        virtual void ParseMouseRel(float xrel, float yrel);
        virtual void SetResolution(int w, int h);

        void InitOpenGL(int w, int h);
        void InitJoysticks();


        void HandleUserEvents(SDL_Event* event);

        SDL_Joystick** mJoystick;
        SDL_Window* mWindow;
		SDL_TimerID mTimer;
        int mJoystickCount;
        int* mJoystickType;
        int mXres;
        int mYres;
        float mScale;        
        float mMouseFaktor;
        CGL_OpenGL mOpenGL;
        bool mFullscreen;
        float mAxis0;
        float mAxis1;

        float mUserParamScale;

};

#endif
