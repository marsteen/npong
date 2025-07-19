//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CSdlPong.cpp
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#define APP_NAME "snake"

#ifdef _WIN32
#include <windows.h>
#endif


#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <sstream>
#include <math.h>
#include <cstdlib>
#include <cstdio>
#include <cmath>

#include <cgl/CGL_include.h>
#include <cgl/CGL_FramebufferObject.h>
#include <vector/CVector3T.h>
#include <file/CFileIO.h>
#include <tools/CException.h>
#include <tools/CRandom.h>
#include <tools/CKeymap.h>
#include <resource/CG3DGlobals.h>
#include <pong/CSdlPong.h>
#include <pong/CPong.h>
#include <pong/gamedefines.h>

using namespace std;


static CGL_FramebufferObject* StaticFramebufferObject;

int gGlobalWindowHeight;
float gGlobalLineWidth = 1.0;
float gGlobalScale = 1.0;
float gGlobalScorePos = 0;


const float colorOrange[] = { 1.0f, 0.5f, 0.0f, 1.0f };
const float colorCyan[]   = { 0.0f, 1.0f, 1.0f, 1.0f };
const float colorGreen[]  = { 0.2f, 1.0f, 0.2f, 1.0f };
const float colorWhite[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const float colorYellow[] = { 1.0f, 1.0f, 0.0f, 1.0f };
const float colorGrey[]   = { 1.0f, 1.0f, 1.0f, 0.5f };

// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlPong
// METHODE       : CSdlPong
//
//
//
// ---------------------------------------------------------------------------

CSdlPong::CSdlPong()
{
    mInitFlag = false;
    mShowInterface = true;
    mFullscreen = false;
    mInitEnemies = false;
    mExploded = false;
    mGameContext.mPlayers = 0;
    mScore[0] = mScore[1] = 0;
    mLevel = 0;
    mHighScore = 0;
    //mGameStatus = EGAMESTATUS_WAITING;
    mGameStatus = EGAMESTATUS_PLAYING;
    mScreenSaveMode = false;
	mBait.Set(20, 10);

    player0pos = 400;
    player1pos = 400;
    player0dir = 0;
    player1dir = 0;

//    ballPosX = 400;
//    ballPosY = 480 - 64;
    ballPosX = 0;
    


    for (int i = 0; i < 4; i++)
    {
        CVector2<int> bait;
        mBaits.push_back(bait);
        createNewBait(i);
    }

    static const float orange[] = { 1.0f, 0.5f, 0.0, 1.0 };
    static const float cyan[]   = { 0.0f, 1.0f, 1.0, 1.0 };

    
    mSnake[0].mColor  = colorOrange;
    mSnake[0].mNumber = 0;
    mSnake[0].reset();
    
    mSnake[1].mColor  = colorCyan;
    mSnake[1].mNumber = 1;
    mSnake[1].reset();
}

void CSdlPong::InitSprites()
{
	spriteWand.load("files/bilder/wall-c2.png");
	spriteKopf1.load("files/bilder/kopf1-b.png");
	spriteKopf2.load("files/bilder/kopf2-b.png");
	spriteKopf3.load("files/bilder/kopf3-b.png");
	spriteKopf4.load("files/bilder/kopf4-b.png");
	spriteRumpf.load("files/bilder/rumpf-b.png");
	spriteFutter.load("files/bilder/futter-b.png");

    spritePaddle.load("files/bilder/paddle-b.png");
    spriteBall.load("files/bilder/ball-b.png");

    spritePaddle.mOffset.y = -32;
    ballPosY = (1080 / 2) - spriteBall.height() / 2;

	snakeSprites[0] = &spriteKopf1;
	snakeSprites[1] = &spriteKopf2;
	snakeSprites[2] = &spriteKopf3;
	snakeSprites[3] = &spriteKopf4;
	snakeSprites[4] = &spriteRumpf;
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlPong
// METHODE       : ~CSdlPong
//
//
//
// ---------------------------------------------------------------------------

CSdlPong::~CSdlPong()
{
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlPong
// METHODE       : InitGame
//
//
//
// ---------------------------------------------------------------------------

void CSdlPong::InitGame()
{
    //mOpenAL.Init();
    if (!mSdlSound.InitAudio())
    {
        exit(0);
    }
    // cout << "Loading sounds.." << endl;
    //SDL_WM_SetCaption("Thieves", "Thieves");
    //SDL_WM_SetIcon(SDL_LoadBMP("files/icon.bmp"), NULL);

    mSdlSound.LoadWav("files/sounds/run1.wav");
    mSdlSound.LoadWav("files/sounds/run2.wav");
    mSdlSound.LoadWav("files/sounds/bait.wav");

    // mSdlSound.LoadWav("files/sounds/explosion1.wav");
    // mSdlSound.LoadWav("files/sounds/explosion2.wav");
    // mSdlSound.LoadWav("files/sounds/schuss2.wav");
    //
    // mSdlSound.LoadWav("files/sounds/1_y.wav"); // 3
    // mSdlSound.LoadWav("files/sounds/2_y.wav");
    // mSdlSound.LoadWav("files/sounds/3_y.wav");
    // mSdlSound.LoadWav("files/sounds/4_y.wav");
    // mSdlSound.LoadWav("files/sounds/4_y.wav");
    // mSdlSound.LoadWav("files/sounds/5_y.wav");
    // mSdlSound.LoadWav("files/sounds/6_y.wav");
    // mSdlSound.LoadWav("files/sounds/7_y.wav");
    // mSdlSound.LoadWav("files/sounds/8_y.wav");
    // mSdlSound.LoadWav("files/sounds/9_y.wav");
    // mSdlSound.LoadWav("files/sounds/10_y.wav"); // 13


    STextureParams tp;

    tp.mMinFilter = GL_NEAREST;
    tp.mMagFilter = GL_NEAREST;
    mMainTex.LoadTexture(GlobalSystem::getPath("files/snake.tga").c_str(), nullptr);
    mGameOverTex.LoadTexture(GlobalSystem::getPath("files/gameover.tga").c_str(), nullptr);
    ReadHighScore();

    mSdlSound.StartPlaying();



    //cout << "Loading sounds ok" << endl;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlPong
// METHODE       : FinishGame
//
//
//
// ---------------------------------------------------------------------------

void CSdlPong::FinishGame()
{
    mSdlSound.Finish();
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlPong
// METHODE       :
//
//
//
// ---------------------------------------------------------------------------

void CSdlPong::SetResolution(int w, int h)
{
    mGameContext.mPlayField.Set(0, 0, w, h);
    gGlobalWindowHeight = h;

    if (!mInitFlag)
    {
        mInitFlag = true;
    }
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlPong
// METHODE       : ParseMouseRel
//
//
//
// ---------------------------------------------------------------------------

void CSdlPong::ParseMouseRel(float xrel, float yrel)
{
    float f1 = fabs(float(xrel));
    float f2 = 1.1;
    float frot = pow(f1, f2) / mMouseFaktor;
    

    //mPlayer[0].AddRotation(-float(xrel) / 7.0);
    
   // cout << "xrel=" << xrel << " yrel=" << yrel << " frot=" << frot << endl;

    if (xrel < 0)
    {
        mPlayer[0].AddRotation(frot);
    }
    else
    {
        mPlayer[0].AddRotation(-frot);
    }
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlPong
// METHODE       : StartGame
//
//
//
// ---------------------------------------------------------------------------

void CSdlPong::StartGame()
{
    mSdlSound.PlayMusic(3);
    mSdlSound.NewMusic(3);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlPong
// METHODE       : moveJoyAxis
//
//
//
// ---------------------------------------------------------------------------

void CSdlPong::moveJoyAxis(int joystick, int axis, int axisValue)
{
    int dir = 0;
    if (abs(axisValue) >= 2000)
    {
        if (axis == 1)
        {
            if (axisValue > 0)
            {
                dir = -10;
            }
            else
            {
                dir = 10;
            }
        }
    }
    switch (joystick)
    {
        case 0:  player0dir = dir; break;
        case 1:  player1dir = dir;; break;
    }    
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlPong
// METHODE       : ParseKeys
//
//
//
// ---------------------------------------------------------------------------

bool CSdlPong::ParseKeys(SDL_Keycode key, bool down)
{
    bool bQuit = -1;

    //cout << "key=" << (int) key << endl;

    //if (mGameStatus != EGAMESTATUS_PLAYING)
    if (true)
    {
        switch (key)
        {

            case SDLK_ESCAPE:

                if (down)
                {
                    bQuit = false;
                }
                break;
        }
    }
    //if (mJoystickCount == 0)
    if (true)
    {
        switch (CKeymap::GetMappedKey(key))
        {
            //
            // Spielsteuerung
            //


            case SDLK_9:

                if (down)
                {
                    mScreenSaveMode = !mScreenSaveMode;

                    if (!mScreenSaveMode)
                    {
                        mSaveScreenGL.Write();
                    }
                }


                break;

            case SDLK_ESCAPE:

                if (down)
                {
                    if (mGameStatus == EGAMESTATUS_PLAYING)
                    {
                        GotoWaitStatus();
                    }
                    else
                    {
                        bQuit = false;
                    }
                }
                break;


            case SDLK_TAB:
            case SDLK_LCTRL:

                if (down)
                {
                }
                break;
        }
    }
    return bQuit;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlPong
// METHODE       : Zoom
//
//
//
// ---------------------------------------------------------------------------

void CSdlPong::Zoom(float f)
{
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlPong
// METHODE       : LeftMouseButtonDown
//
//
//
// ---------------------------------------------------------------------------

void CSdlPong::LeftMouseButtonDown()
{
    mGameContext.mLeftButton = true;
//    Shot(0);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlPong
// METHODE       : LeftMouseButtonUp
//
//
//
// ---------------------------------------------------------------------------

void CSdlPong::LeftMouseButtonUp()
{
    mGameContext.mLeftButton = false;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlPong
// METHODE       : RightMouseButtonDown
//
//
//
// ---------------------------------------------------------------------------

void CSdlPong::RightMouseButtonUp()
{
    mGameContext.mRightButton = false;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlPong
// METHODE       : RightMouseButtonDown
//
//
//
// ---------------------------------------------------------------------------

void CSdlPong::RightMouseButtonDown()
{
    mGameContext.mRightButton = true;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlPong
// METHODE       : GameLoop
//
//
//
// ---------------------------------------------------------------------------

#define FB_WIDTH		960 * 4
#define FB_HEIGHT		540 * 4

//#define USE_FB




void CSdlPong::GameLoop()
{
    //cout << "CSdlPong::GameLoop" << endl;
    
    if (mJoystickCount > 0)
    {
        if (mGameStatus == EGAMESTATUS_PLAYING)
        {
            float xrel = mAxis0 / 1000;
            //cout << "mAxis0=" << mAxis0 << " Axis1=" << mAxis1 << endl;
            ParseMouseRel(xrel, 0);
        }
    }
    

#ifdef USE_FB
    if (StaticFramebufferObject == NULL)
    {
        StaticFramebufferObject = new CGL_FramebufferObject;
        StaticFramebufferObject->CreateFramebufferObject(FB_WIDTH, FB_HEIGHT);
    }
#endif

    mGameContext.mPlayField.Set(0, 0, mXres, mYres);

#ifdef USE_FB
    StaticFramebufferObject->DrawToFrameBuffer(true);
#endif

    Draw2DObjects();

#ifdef USE_FB
    StaticFramebufferObject->DrawToFrameBuffer(false);
    StaticFramebufferObject->DrawTexture(mXres, mYres);
#endif

    player0pos += player0dir;
    player1pos += player1dir;


    SDL_GL_SwapWindow(mWindow);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlPong
// METHODE       : DrawCenterTex
//
//
//
// ---------------------------------------------------------------------------

void CSdlPong::DrawCenterPatch(CGL_Patch2d* pat)
{


    //cout << "mGameContext.mPlayField.Width()=" << mGameContext.mPlayField.Width() << endl;
    //cout << "mGameContext.mPlayField.Height()=" << mGameContext.mPlayField.Height() << endl;
    const float zspeed = 1.0003f;
    static float nx = 1.0f;
    static float nd = zspeed;


    const float Scale = gGlobalScale * nx;

    float ox = 0;
    float oy = 0;

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    pat->mPos.x = (mGameContext.mPlayField.Width() / 2) - (pat->mWidth / 2 * Scale) + ox;
    pat->mPos.y = (mGameContext.mPlayField.Height() / 2)- (pat->mHeight / 2 * Scale) + oy;
    pat->DrawScaled(Scale);

    nx *= nd;
    if (nx > 1.5f)
    {
        nd = 1.0f / zspeed;
    }
    if (nx < 1.0f)
    {
        nd = zspeed;
    }

    //pat->Draw();
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlPong
// METHODE       : GotoWaitStatus
//
//
//
// ---------------------------------------------------------------------------

void CSdlPong::GotoWaitStatus()
{
    mGameStatus = EGAMESTATUS_WAITING;
    mSdlSound.StopMusic();
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlPong
// METHODE       : Digits
//
//
//
// ---------------------------------------------------------------------------

int CSdlPong::Digits(int k)
{
    stringstream mstr;

    mstr << k;
    return mstr.str().size();
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlPong
// METHODE       : WriteHighScore
//
//
//
// ---------------------------------------------------------------------------

void CSdlPong::WriteHighScore()
{
    ofstream of(GlobalSystem::getPath("hiscore.txt"));

    if (of.good())
    {
        of << mHighScore << endl;
        of.close();
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlPong
// METHODE       : ReadHighScore
//
//
//
// ---------------------------------------------------------------------------

void CSdlPong::ReadHighScore()
{
    ifstream infile(GlobalSystem::getPath("hiscore.txt"));

    if (infile.good())
    {
        infile >> mHighScore;
        infile.close();
    }
}

// Size: 1920x960

void CSdlPong::DrawSpriteOnField(const CSprite& sprite, int x, int y) const
{
	sprite.draw(x * 40, (21-y) * 40, mScale);
    
    
}

void CSdlPong::Timer()
{
    static int interval;

//    if (interval++ % 5 == 0) mSdlSound.PlayWav(1);
//    else                     mSdlSound.PlayWav(0);



    

}

void CSdlPong::createNewBait()
{
	while (1)
	{
	    CVector2<int> tkoor(CRandom::GetInt(1, FIELD_SIZE_X-2), CRandom::GetInt(1, FIELD_SIZE_Y-2));
		
		if (!mSnake[0].hasKoor(tkoor) &&
            !mSnake[1].hasKoor(tkoor))
		{
			mBait = tkoor;
			break;
		}
	}	
}

void CSdlPong::createNewBait(int nr)
{
	while (1)
	{
	    CVector2<int> tkoor(CRandom::GetInt(1, FIELD_SIZE_X-2), CRandom::GetInt(1, FIELD_SIZE_Y-2));
		
		if (!mSnake[0].hasKoor(tkoor) &&
            !mSnake[1].hasKoor(tkoor))
		{
			mBaits[nr] = tkoor;
			break;
		}
	}	
}



void CSdlPong::ResetPlayers()
{
    mSnake[0].reset();
    mSnake[1].reset();
    mGameStatus = EGAMESTATUS_PLAYING;
}


void CSdlPong::JoystickButtonAction(int nr, int type, int jbutton)
{
    cout << "nr:" << nr << " type:" << type << " jbutton:" << jbutton << endl;

    if (type == 0) // Playstation
    {
        switch (jbutton)
        {
            case  2: /* BLAU */ 
                if (nr == 0)
                {
                    mSnake[0].reset();
                    mSnake[1].reset();
                    mGameStatus = EGAMESTATUS_PLAYING; 
                }
                break;

            case 13: mSnake[nr].changeDir(ESnakeDir::LEFT); break;
            case 14: mSnake[nr].changeDir(ESnakeDir::RIGHT); break;
            case 11: mSnake[nr].changeDir(ESnakeDir::UP); break;
            case 12: mSnake[nr].changeDir(ESnakeDir::DOWN); break;
        }
    }
    else // Xbox
    {
        switch (jbutton)
        {
            case  2: /* BLAU */ 
                if (nr == 0)
                {
                    mSnake[0].reset();
                    mSnake[1].reset();
                    mGameStatus = EGAMESTATUS_PLAYING; 
                }
                break;

            case 11: mSnake[nr].changeDir(ESnakeDir::LEFT); break;
            case 12: mSnake[nr].changeDir(ESnakeDir::RIGHT); break;
            case 13: mSnake[nr].changeDir(ESnakeDir::UP); break;
            case 14: mSnake[nr].changeDir(ESnakeDir::DOWN); break;
        }
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlPong
// METHODE       : DrawPlayfield
//
// The Playfield has a size of 40x20 (FIELD_SIZE_X * FIELD_SIZE_Y))
//
//
// ---------------------------------------------------------------------------

void CSdlPong::DrawPlayfield() const
{
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glColor4fv(colorGrey);
	for (int x = 0; x < FIELD_SIZE_X; x++)
	{
		DrawSpriteOnField(spriteWand, x, 0);
		DrawSpriteOnField(spriteWand, x, FIELD_SIZE_Y-1);
    }
	for (int y = 1; y < FIELD_SIZE_Y-1; y++)
	{
		DrawSpriteOnField(spriteWand,  0, y);
		DrawSpriteOnField(spriteWand, FIELD_SIZE_X-1, y);
	}
    glColor4fv(colorWhite);
    spritePaddle.draw(100, player0pos, mScale);
    spritePaddle.draw(1600 - 140, player1pos, mScale);

    spriteBall.draw(ballPosX, ballPosY, mScale);

// 	mSnake[0].draw(snakeSprites, mScale);
//     mSnake[1].draw(snakeSprites, mScale);
	
//     glColor4fv(colorYellow);
// //	DrawSpriteOnField(spriteFutter, mBait.x, mBait.y);

//     for (auto bait = mBaits.begin(); bait != mBaits.end(); ++bait)
//     {
//     	DrawSpriteOnField(spriteFutter, bait->x, bait->y);    
//     }


	// ,,
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlPong
// METHODE       : Draw2DObjects
//
//
//
// ---------------------------------------------------------------------------

void CSdlPong::Draw2DObjects()
{
    if (mInitFlag)
    {
        static bool initOpenGL;
    	if (!initOpenGL)
    	{    
	    	InitSprites();
	    	initOpenGL = true;
	    }
    
    
        mOpenGL.StartProjectionView();

        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		DrawPlayfield();

        if (mGameStatus == EGAMESTATUS_WAITING)
        {
            DrawCenterPatch(&mMainTex);
        }

        glDisable(GL_BLEND);
    }
}

