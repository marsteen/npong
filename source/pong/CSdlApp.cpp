//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CSdlApp.cpp
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

#include <SDL2/SDL.h>
#include <tools/CStringTool.h>
#include <tools/CKeymap.h>
#include <global/GlobalSystemFunctions.h>
#include <pong/CSdlApp.h>

extern float gGlobalLineWidth;
extern float gGlobalScale;
extern float gGlobalScorePos;

using namespace std;

#define VERSION_STRING "1.0.0"

// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlApp
// METHODE       : CSdlApp
//
//
//
// ---------------------------------------------------------------------------

CSdlApp::CSdlApp()
{
    mFullscreen = false;
    mMouseFaktor = 10.0;
    mJoystick = nullptr;
    mJoystickType = nullptr;
    mJoystickCount = 0;
    mAxis0 = 0.0f;
    mAxis1 = 0.0f;

    mScale = 1.0f;
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlApp
// METHODE       : ParseArgVec
//
//
//
// ---------------------------------------------------------------------------

void CSdlApp::ParseArgVec(const vector<string>& ArgStr)
{
    CStringTool st;

    for (int i = 0; i < ArgStr.size(); i++)
    {
        if (ArgStr[i] == "-scale")
        {
            mScale = st.StringTo<float>(ArgStr[i+1]);
        }
        else
        if (ArgStr[i] == "-version")
        {
            cout << "Version:" << VERSION_STRING << endl;
            exit(0);
        }
        else
        if (ArgStr[i] == "-help")
        {
            cout << "********************************************************" << endl;
            cout << "NPONG" << endl;
            cout << "written 2025 by Martin Steen" << endl;
            cout << "commandline options:" << endl;
            cout << "  -scale <float>: change scale" << endl;
            cout << "Version: " << VERSION_STRING << endl;
            cout << "********************************************************" << endl;
            exit(0);
        }
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlApp
// METHODE       : ParseArgs
//
//
//
// ---------------------------------------------------------------------------

void CSdlApp::ParseArgs(int argc, char* argv[])
{
    char AppPath[256];

    mFullscreen = true;
    vector<string> ArgVec;

    strcpy(AppPath, argv[0]);
    char* Path = strrchr(AppPath, GlobalSystem::getPathDiv());

    if (Path != NULL)
    {
        *Path = 0;
        GlobalSystem::setPath(AppPath);
        //cout << "mAppPath=" << mAppPath << endl;
    }


    for (int i = 1; i < argc; i++)
    {
        string ArgStr = string(argv[i]);
        ArgVec.push_back(ArgStr);
    }
    ParseArgVec(ArgVec);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlApp
// METHODE       : ParseWinArgs
//
//
//
// ---------------------------------------------------------------------------

void CSdlApp::ParseWinArgs(const char* Commandline)
{
    CStringTool st;
    vector<string> SplitResult;

    mFullscreen = true;

    st.SplitString(Commandline, &SplitResult, ' ');


    ParseArgVec(SplitResult);

    /*
     * for (int i = 0; i < SplitResult.size(); i++)
     * {
     *  ParseArg(SplitResult[i]);
     * }
     */
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlApp
// METHODE       : GameLoop
//
//
//
// ---------------------------------------------------------------------------

void CSdlApp::GameLoop()
{
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlApp
// METHODE       :
//
//
//
// ---------------------------------------------------------------------------

static Uint32 sTimerCallback(Uint32 interval, void* param)
{
    CSdlApp* SdlApp = (CSdlApp*) param;
    SdlApp->Timer();
    return interval;
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlApp
// METHODE       : Timer
//
//
//
// ---------------------------------------------------------------------------

void CSdlApp::Timer()
{
/*
 * static int t;
 * cout << "timer:"  << t << endl;
 * t++;
 */

    //GameLoop();
    //SDL_GL_SwapWindow(mWindow);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlApp
// METHODE       : SetResolution (virtual)
//
//
//
// ---------------------------------------------------------------------------

void CSdlApp::SetResolution(int w, int h)
{
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlApp
// METHODE       :
//
//
//
// ---------------------------------------------------------------------------

void CSdlApp::InitGame()
{
}

#if 0
// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlApp
// METHODE       : GetVideoModes
//
//
//
// ---------------------------------------------------------------------------

bool CSdlApp::GetVideoModes(int* FirstW, int* FirstH, int n)
{
    SDL_Rect** modes;
    int i;
    bool r = false;

    /* Get available fullscreen/hardware modes */
    modes = SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_HWSURFACE);
    /* Check if there are any modes available */
    if (modes == NULL)
    {
        cout << "No modes available!" << endl;
    }
    else
    /* Check if our resolution is restricted */
    if (modes == (SDL_Rect**)-1)
    {
        //cout << "All resolutions available." << endl;
    }
    else
    {
#if 1
        /* Print valid modes */
        cout << "Available Modes:" << endl;
        for (i = 0; modes[i]; ++i)
        {
            cout	<< " " << modes[i]->w
                    << "x" << modes[i]->h << endl;
        }
#endif
        *FirstW = modes[n]->w;
        *FirstH = modes[n]->h;
        r = true;
    }
    return r;
}
#endif


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlApp
// METHODE       : FinishGame
//
//
//
// ---------------------------------------------------------------------------

void CSdlApp::FinishGame()
{
    SDL_ShowCursor(true);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlApp
// METHODE       :
//
//
//
// ---------------------------------------------------------------------------

bool CSdlApp::Init()
{
    bool r = true;

    //cout << "CSdlApp::Init START" << endl;
    //cout << "SDL_GL_SetAttribute ok" << endl;
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
    {
        cout << "SDL konnte nicht initialisiert werden: " << SDL_GetError() << endl;
        r = false;
    }
    // cout << "CSdlApp::Init OK" << endl;
    SDL_ShowCursor(false); // Mousecursor verstecken

    CKeymap::ReadMapFile("files/keymap.txt");

    cout << "Joysticks:" << SDL_NumJoysticks() << endl;



    return r;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlApp
// METHODE       : InitOpenGL
//
//
//
// ---------------------------------------------------------------------------

void CSdlApp::InitOpenGL(int w, int h)
{
    mOpenGL.SetViewport(w, h);
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlPong
// METHODE       : InitJoysticks
//
// ---------------------------------------------------------------------------

void CSdlApp::InitJoysticks()
{
    
    cout << "InitJoysticks START" << endl;
    mJoystickCount = SDL_NumJoysticks();
    if(mJoystickCount)
    {
        cout << " Joysticks:"  << mJoystickCount << endl;
        
        // Erzeuge Array von Joystick-Pointern        
        mJoystick = new SDL_Joystick*[mJoystickCount];
        mJoystickType = new int[mJoystickCount];
        
        
        for (int j = 0; j < mJoystickCount; j++)
        {       
            mJoystick[j] = SDL_JoystickOpen(j);
            const std::string name = SDL_JoystickName(mJoystick[j]);
            if (mJoystick[j])
            {
                cout << "    Opened Joystick:"    << j << endl;
                cout << "    Name: "              << name << endl;
                cout << "    Number of Axes: "    << SDL_JoystickNumAxes(mJoystick[j]) << endl;;
                cout << "    Number of Buttons: " << SDL_JoystickNumButtons(mJoystick[j]) << endl;
                cout << "    Number of Balls: "   << SDL_JoystickNumBalls(mJoystick[j]) << endl;
            }

            if (name.find("PS") != std::string::npos)
            {
                mJoystickType[j] = 0;
                cout << "    Type is PLAYSTATION" << endl;
            }
            else
            {
                mJoystickType[j] = 1;
                cout << "    Type is XBOX" << endl;
            }
        }
    }
    cout << "InitJoysticks OK" << endl;

    // Close if opened
    //if(SDL_JoystickOpened(0))
    //SDL_JoystickClose(joy);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlApp
// METHODE       : forceFullHD
//
// ---------------------------------------------------------------------------

void CSdlApp::forceFullHD(SDL_Window* window)
{
    SDL_DisplayMode dm;
    dm.w = 1920;
    dm.h = 1080;
    dm.refresh_rate = 0;
    dm.driverdata = nullptr;
    if (SDL_SetWindowDisplayMode(mWindow, &dm) < 0)
    {
        cout << "***** error in SDL_SetWindowDisplayMode=" << SDL_GetError() <<  endl;
    }
    else
    {
       mScale = 1.0;
       mXres = 1920;
       mYres = 1080;
       cout << "+++++ forceFullHD success" << endl;
    }
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlApp
// METHODE       : InitScreen
//
//
//
// ---------------------------------------------------------------------------

bool CSdlApp::InitScreen() //int xres, int yres, int Bits)
{

    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);
    mXres = dm.w;
    mYres = dm.h;

    const int windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;

    cout << "xres=" << mXres << " yres=" << mYres << " scale=" << mScale << endl;

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetSwapInterval(1);

    mWindow = SDL_CreateWindow("npong", 0, 0, mXres, mYres, windowFlags);
    SDL_GLContext maincontext = SDL_GL_CreateContext(mWindow);

    int w, h;
    SDL_GetWindowSize(mWindow, &w, &h);
    std::cout << "SDL_GetWindowSize w=" << w << " h=" << h << std::endl;

    //SDL_GL_GetDrawableSize(mWindow, &w, &h);
    //std::cout << "SDL_GL_GetDrawableSize w=" << w << " h=" << h << std::endl;   
    


    if (mWindow == nullptr)
    {
        cout << "***** SDL_CreateWindow failed" << endl;
    }


    SetResolution(mXres, mYres);

    InitOpenGL(mXres, mYres);

    // {
    //     SDL_Renderer* renderer = SDL_GetRenderer(mWindow);
    //     if (renderer == nullptr)
    //     {
    //         std::cout << "***** SDL_GetRenderer is null" << std::endl;
    //     }
    //     float sx = 0, sy = 0;
    //     SDL_RenderGetScale(renderer, &sx, &sy);
    //     std::cout << "SDL_RenderGetScale sx=" << sx << " sy=" << sy << std::endl;


    //     w = 0; h = 0;        
    //     SDL_GetRendererOutputSize(renderer, &w, &h);
    //     std::cout << "SDL_GetRendererOutputSize w=" << w << " h=" << h << std::endl;
    // }

    InitGame();
    InitJoysticks();
    mTimer = SDL_AddTimer(100, sTimerCallback, this);
    return true;
}

/*
bool CSdlApp::InitScreen() //int xres, int yres, int Bits)
{
    cout << "CSdlApp::InitScreen START" << endl;
    
    bool r = true;
    unsigned int flags;
    const SDL_VideoInfo* VideoInfo = NULL;

    VideoInfo = SDL_GetVideoInfo();
    int bpp = VideoInfo->vfmt->BitsPerPixel;

    //cout << "bits per pixel=" << bpp << endl;

    //SDL_Surface* Surface = SDL_GetVideoSurface();
    //cout << "XRES=" << Surface->w << " YRES=" << Surface->h << endl;

    if (mFullscreen)
    {
        flags = SDL_OPENGL | SDL_FULLSCREEN | SDL_HWSURFACE;
    }
    else
    {
        flags = SDL_OPENGL;
    }
    //flags = SDL_OPENGL | SDL_NOFRAME | SDL_DOUBLEBUF | SDL_FULLSCREEN;

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    //SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, bpp);

    if (mFullscreen)
    {
        int FirstW;
        int FirstH;
        if ((GetVideoModes(&FirstW, &FirstH, 0) && mFullscreen))
        {
            mXres = FirstW;
            mYres = FirstH;


            cout << "Setting Mode to " << FirstW << "x" << FirstH << " Bits:" << bpp << endl;
        }
    }
    if (mXres < 1280.0)
    {
       // gGlobalScale = float(mXres) / 1280.0;
    }


    cout << "Setting Mode to " << mXres << "x" << mYres << endl;

    if (mFullscreen)
    {
        mDrawContext = SDL_SetVideoMode(mXres, mYres, 0, flags);
    }

    if (mDrawContext == NULL)
    {
    }


    //SDL_Delay(1000);
    SetResolution(mXres, mYres);
    //cout << "InitOpenGL OK" << endl;
    //SDL_Delay(1000);
    InitOpenGL(mXres, mYres);
    //cout << "InitOpenGL OK" << endl;

    if (mDrawContext == NULL)
    {
        cout << "Fehler beim Umschalten der Auflösung " << mXres << "*" << mYres << ":"  <<  SDL_GetError() << endl;
        r = false;
    }
    InitGame();
    InitJoysticks();
    //mTimer = SDL_AddTimer(100, sTimerCallback, this);
    cout << "CSdlApp::InitScreen OK" << endl;

    return r;
}
*/


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlApp
// METHODE       : DisableKeyRepeat
//
//
//
// ---------------------------------------------------------------------------

void CSdlApp::DisableKeyRepeat()
{
    //SDL_EnableKeyRepeat(0, 0);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlApp
// METHODE       : ParseKeys
//
//
//
// ---------------------------------------------------------------------------

bool CSdlApp::ParseKeys(SDL_Keycode key, bool down)
{
    if (CKeymap::GetMappedKey(key) == SDLK_ESCAPE)
    {
        return false;
    }

    return true;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlApp
// METHODE       : MainLoop
//
//
//
// ---------------------------------------------------------------------------

void CSdlApp::MainLoop()
{
    while (1)
    {
        Uint32 StartTime = SDL_GetTicks();
        EventLoop();
        GameLoop();

        Uint32 EndTime = SDL_GetTicks();
        int DelayTime = 20 - (EndTime - StartTime);
        if (DelayTime > 0)
        {
            //cout << "DelayTime=" << DelayTime << endl;
            SDL_Delay(DelayTime);
        }
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlApp
// METHODE       : ParseMouseRel
//
//
//
// ---------------------------------------------------------------------------

void CSdlApp::ParseMouseRel(float xrel, float yrel)
{
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlApp
// METHODE       : EventLoop
//
//
//
// ---------------------------------------------------------------------------

void CSdlApp::EventLoop()
{
    SDL_Event event;


    while (SDL_PollEvent(&event))
    {
        //cout << "event.type=" << event.type << endl;

        switch (event.type)
        {
            case SDL_USEREVENT:

                //HandleUserEvents(&event);
                break;

            case SDL_KEYDOWN:

                //cout << "SDL_KEYDOWN:" << event.key.keysym.sym << endl;
                //            1073741905 left
                //SDL_KEYDOWN:1073741906 top
                //SDL_KEYDOWN:1073741903 right
                //SDL_KEYDOWN:1073741905 bottom

                switch (event.key.keysym.sym)
                {
                    // case 1073741904: ParseKeys(SDLK_LEFT, true); break;
                    // case 1073741903: ParseKeys(SDLK_RIGHT, true); break;
                    // case 1073741906: ParseKeys(SDLK_UP, true); break;
                    // case 1073741905: ParseKeys(SDLK_DOWN, true); break;
                    case 1073742048: ResetPlayers(); break;
                }





                if (false) //CKeymap::GetMappedKey(event.key.keysym.sym) == SDLK_ESCAPE)
                {
                    if (!ParseKeys(SDLK_ESCAPE, true))
                    {
                        FinishGame();
                        SDL_Quit();
                        exit(0);
                    }
                }
                else
                {
                    //if (mJoystickCount == 0)
                    {
                        ParseKeys(event.key.keysym.sym, true);
                    }
                }
                break;

            case SDL_KEYUP:

                //if (mJoystickCount == 0)
                {
                    ParseKeys(event.key.keysym.sym, false);
                }
                break;

            case SDL_QUIT:

                FinishGame();
                SDL_Quit();
                exit(0);
                //done = true;
                break;

            case SDL_JOYBUTTONDOWN:
            case SDL_CONTROLLERBUTTONDOWN:
            {

                // 0 = button A
                // 7 = Escape
                const SDL_JoystickID which = event.jbutton.which;
                const int jbutton = event.jbutton.button;
                //cout << "SDL_JOYBUTTONDOWN stick:" << which << " button:" << jbutton << endl;
                // Links = 11
                // Rechts= 12
                // Oben  = 13
                // Unten = 14


                if (jbutton == 7)
                {
                    ParseKeys(SDLK_ESCAPE, true);
                }
                else
                {
                    JoystickButtonAction(which, mJoystickType[which], jbutton);
                }
            }
            break;


                
            case SDL_JOYAXISMOTION:
            {

            // typedef struct SDL_JoyAxisEvent
            // {
            //     Uint32 type;        /**< SDL_JOYAXISMOTION */
            //     Uint32 timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
            //     SDL_JoystickID which; /**< The joystick instance id */
            //     Uint8 axis;         /**< The joystick axis index */
            //     Uint8 padding1;
            //     Uint8 padding2;
            //     Uint8 padding3;
            //     Sint16 value;       /**< The axis value (range: -32768 to 32767) */
            //     Uint16 padding4;
            // } SDL_JoyAxisEvent;

                cout << "SDL_JOYAXISMOTION:" << event.jaxis.which
                    << " axis:" << (int) event.jaxis.axis
                    << " value:" << (int) event.jaxis.value << endl;

                moveJoyAxis(event.jaxis.which, event.jaxis.axis, event.jaxis.value);


                
                //mAxis0 = SDL_JoystickGetAxis(mJoystick[event.jaxis.which], 0);
                //mAxis1 = SDL_JoystickGetAxis(mJoystick[event.jaxis.which], 1);
                
                //cout << "mAxis0=" << mAxis0 << " mAxis1=" << mAxis1 << endl;
                
                
                //float xrel = float(mAxis0) / 1000;                
                
                //ParseKeys(SDLK_DOWN, mAxis1 >  2000);
                //ParseKeys(SDLK_UP,   mAxis1 < -2000);
                   
                
                
                //ParseMouseRel(xrel, 0);
                
                //cout << "axis0=" << axis0 << " axis1=" << axis1 << endl;
            }                               
            break;

            default:

                break;
        }   // End switch
    }       // End while
}
