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
const float colorGrey[]   = { 0.5f, 0.5f, 0.5f, 1.0f };

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
    mGameContext.mPlayers = 0;
    mScore[0] = mScore[1] = 0;
    mLevel = 0;
    mHighScore = 0;
    mGameStatus = EGAMESTATUS_WAITING;
    mScreenSaveMode = false;

    player0dir = 0;
    player1dir = 0;

    mWaitCounter = 0;
    
    players = 2;

    static const float orange[] = { 1.0f, 0.5f, 0.0, 1.0 };
    static const float cyan[]   = { 0.0f, 1.0f, 1.0, 1.0 };

}

void CSdlPong::InitSprites()
{
    for (int d = 0; d <= 9; d++)
    {
        stringstream mstr;
        mstr << "files/bilder/digits/" << d << "-b.png";
        spriteDigit[d].load(mstr.str().c_str());
    }


    spritePaddle.load("files/bilder/paddle-b.png");
    spriteBall.load("files/bilder/ball-b.png");

    spritePaddle.mBorders.top = 32;
    spritePaddle.mBorders.bottom = 32;

    srand(time(NULL));
    ResetBall();

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

void CSdlPong::ResetBall()
{
    ballPosX = mGameContext.mPlayField.Width() / 2 - spriteBall.logicalWidth() / 2;
    ballPosY = mGameContext.mPlayField.Height() / 2 - spriteBall.logicalHeight() / 2;
    
    ballDirX = CRandom::Get(6.0f, 8.0f) * CRandom::Sign();
    ballDirY = CRandom::Get(4.0f, 8.0f) * CRandom::Sign();

    const int distPaddleToWall = 100;
    const int startPosY = (mGameContext.mPlayField.Height() / 2) - spritePaddle.logicalHeight() / 2;
    player0posX = distPaddleToWall;
    player0posY = startPosY;
    player1posX = mGameContext.mPlayField.Width() - spritePaddle.logicalWidth() - distPaddleToWall;    
    player1posY = startPosY;
    playerSpeed = 15;

    logoScale = 1.0f;
    mGameStatus = EGAMESTATUS_SHOW_LOGO;
    mWaitCounter = 50;

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


    soundBleep0 = mSdlSound.LoadWav("files/sounds/bleep0.wav");
    soundBleep1 = mSdlSound.LoadWav("files/sounds/bleep1.wav");
    soundBleep2 = mSdlSound.LoadWav("files/sounds/bleep2.wav");
    soundGoal   = mSdlSound.LoadWav("files/sounds/goal.wav");
    soundWin    = mSdlSound.LoadWav("files/sounds/win.wav");
    soundMusic  = mSdlSound.LoadOgg("files/sounds/neon-dreams.ogg");

    STextureParams tp;

    tp.mMinFilter = GL_NEAREST;
    tp.mMagFilter = GL_NEAREST;
    mLogoTex.LoadTexture(GlobalSystem::getPath("files/bilder/bs-logo.png").c_str(), nullptr);
    mWin0Tex.LoadTexture(GlobalSystem::getPath("files/bilder/player1wins.png").c_str(), nullptr);
    mWin1Tex.LoadTexture(GlobalSystem::getPath("files/bilder/player2wins.png").c_str(), nullptr);
    mGameOverTex.LoadTexture(GlobalSystem::getPath("files/gameover.tga").c_str(), nullptr);
    ReadHighScore();

    mSdlSound.StartPlaying();

    mSdlSound.PlayMusic(soundMusic, 0.5f);



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
// METHODE       : SetResolution
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
    if (axis == 1)
    {
        int dir = 0;
        if (abs(axisValue) >= 2000)
        {
            if (axisValue > 0)
            {
                dir = -playerSpeed;
            }
            else
            {
                dir = playerSpeed;
            }
        }
        
        switch (joystick)
        {
            case 0:  if (players > 0) player0dir = dir; break;
            case 1:  if (players == 2) player1dir = dir; break;
        }
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
            case SDLK_0: players = 0; break;
            case SDLK_1: players = 1; break;
            case SDLK_2: players = 2; break;
            
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

            case SDLK_UP:

                if (down)
                {
                    player0dir = playerSpeed;
                }
                else
                {
                    player0dir = 0;
                }
                break;

            case SDLK_DOWN:

                if (down)
                {
                    player0dir = -playerSpeed;
                }
                else
                {
                    player0dir = 0;
                }
                break;

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
// METHODE       : CheckIfPlayerHitsBall
//
//
//
// ---------------------------------------------------------------------------

#define FB_WIDTH		960 * 4
#define FB_HEIGHT		540 * 4

//#define USE_FB


bool CSdlPong::CheckIfPlayerHitsBall(const int& playerPosX, const int& playerPosY, float bx, float by) const
{
    if (bx + spriteBall.logicalWidth() > playerPosX && 
        bx < playerPosX + spritePaddle.logicalWidth())
    {
        if ((playerPosY < by + spriteBall.logicalHeight()) && 
            (playerPosY + spritePaddle.logicalHeight() > by))
        {            
            return true;
        }
    }
    return false;
}

void CSdlPong::GameStatusPlaying()
{
    static int dc;
    bool goal = false;
    
    float bx = ballPosX;
    float by = ballPosY;

    if (ballPosX < 0) // Goal Player 1
    {
        ResetBall();
        if (mScore[1] < 4) 
        {
            mSdlSound.PlayWav(soundGoal);
        }
        else 
        {
            mWaitCounter = 100;
            mGameStatus = EGAMESTATUS_WIN_1;
            mSdlSound.PlayWav(soundWin);
        }
        mScore[1] += 1;
        dc = 0;
        goal = true;        
    }
    else
    if (ballPosX + spriteBall.logicalWidth() > mGameContext.mPlayField.Width()) // Goal Player 0
    {
        
        ResetBall();
        if (mScore[0] < 4) 
        {
            mSdlSound.PlayWav(soundGoal);         
        }
        else 
        {
            mWaitCounter = 100;
            mGameStatus = EGAMESTATUS_WIN_0;
            mSdlSound.PlayWav(soundWin);
        }
        mScore[0] += 1;
        dc = 0;
        goal = true;   
    }


    if (!goal)
    {
        
    	constexpr int ballMoveResolution = 25;
    	
    	const float dx = ballDirX / ballMoveResolution;
    	const float dy = ballDirY / ballMoveResolution;
    	
    	for (int r = 0; r < ballMoveResolution; r++)
    	{
    	    //cout << "r=" << r << " of " << ballMoveResolution << endl;
        	const float lastBx = bx;
        	const float lastBy = by;
        	bx += dx;
        	by += dy;
    		if ((by < 0) || (by + spriteBall.logicalHeight() > mGameContext.mPlayField.Height()))
    		{
        		mSdlSound.PlayWav(soundBleep2);
        		ballDirY = -ballDirY;
        		bx = lastBx;
        		by = lastBy;
        		dc = 0;
        		break;
    		}

    		constexpr float speedUp = 1.08f;
    		constexpr float playerHitDiv = 10.0f;


            if (dc == 0)
            {
        		if (CheckIfPlayerHitsBall(player0posX, player0posY, bx, by))
        		{
            		mSdlSound.PlayWav(soundBleep0);
            		ballDirX = -ballDirX * speedUp;
            		ballDirY *= speedUp;
            		ballDirY += float(player0dir) / playerHitDiv;
            		bx = lastBx;
            		by = lastBy;
                    dc = 10;
            		break;                       
        		}
        		else
        		if (CheckIfPlayerHitsBall(player1posX, player1posY, bx, by))
        		{
            		mSdlSound.PlayWav(soundBleep1);
            		//ballPosX = player1posX - spriteBall.logicalWidth();
            		ballDirX = -ballDirX * speedUp;
            		ballDirY *= speedUp;
            		ballDirY += float(player0dir) / playerHitDiv;
            		bx = lastBx;
            		by = lastBy;        		
            		dc = 10;
            		break;
        		}
            }
    	}
        ballPosX = bx;
        ballPosY = by;        
    }
    if (dc > 0)
    {
        dc--;
    }

}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlPong
// METHODE       : GameLoop
//
//
//
// ---------------------------------------------------------------------------

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

    mGameContext.mPlayField.Set(0, 0, mScale * mXres, mScale * mYres);

#ifdef USE_FB
    StaticFramebufferObject->DrawToFrameBuffer(true);
#endif

    Draw2DObjects();

#ifdef USE_FB
    StaticFramebufferObject->DrawToFrameBuffer(false);
    StaticFramebufferObject->DrawTexture(mXres, mYres);
#endif

    if (players == 1)
    {
        AutoPlayer(player1posX, player1posY, player1dir);
    }
    else
    if (players == 0)
    {
        AutoPlayer(player0posX, player0posY, player0dir);
        AutoPlayer(player1posX, player1posY, player1dir);    
    }


    player0posY += player0dir;
    player1posY += player1dir;

    const int maxY = mGameContext.mPlayField.Height() - spritePaddle.logicalHeight();
    if (player0posY < 0) player0posY = 0;
    if (player0posY > maxY) player0posY = maxY;
    if (player1posY < 0) player1posY = 0;
    if (player1posY > maxY) player1posY = maxY;

    switch (mGameStatus)
    {
        case  EGAMESTATUS_PLAYING:
            GameStatusPlaying();
            break;

        case EGAMESTATUS_SHOW_LOGO:

            if (mWaitCounter == 30)
            {
                mGameStatus = EGAMESTATUS_WAITING;
            }
            break;


        case EGAMESTATUS_WAITING:

            if (mWaitCounter == 0)
            {
                mGameStatus = EGAMESTATUS_PLAYING;
            }
            break;

        case EGAMESTATUS_WIN_0:
        case EGAMESTATUS_WIN_1:

            if (mWaitCounter == 0)
            {
                ResetBall();
                mWaitCounter = 30;
                mScore[0] = 0;
                mScore[1] = 0;
                mGameStatus = EGAMESTATUS_WAITING;

            }            
            break;

    }






    SDL_GL_SwapWindow(mWindow);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlPong
// METHODE       : DrawCenterPatch
//
//
//
// ---------------------------------------------------------------------------

void CSdlPong::DrawCenterPatch(CGL_Patch2d* pat, float speed, float scale, float r, float g, float b)
{


    //cout << "mGameContext.mPlayField.Width()=" << mGameContext.mPlayField.Width()
    //     << " mGameContext.mPlayField.Height()=" << mGameContext.mPlayField.Height() << " scale=" << mScale << endl;

    const float effScale = logoScale * scale;
    
    glColor4f(r, g, b, 1.0 - (logoScale - 1.0));
    pat->mPos.x = (mGameContext.mPlayField.Width() / 2) - (pat->mWidth / 2) * effScale;
    pat->mPos.y = (mGameContext.mPlayField.Height()  / 2) - (pat->mHeight / 2) * effScale;    
    pat->DrawScaled(effScale);

    logoScale *= speed;




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
	sprite.draw(x * 48, (21-y) * 48, 1.0f);
    
    
}

void CSdlPong::Timer()
{
    static int interval;
    if (mWaitCounter > 0)
    {
        mWaitCounter--;
    }

//    if (interval++ % 5 == 0) mSdlSound.PlayWav(1);
//    else                     mSdlSound.PlayWav(0);



    

}



void CSdlPong::ResetPlayers()
{
}


void CSdlPong::JoystickButtonAction(int nr, int type, int jbutton)
{
    cout << "nr:" << nr << " type:" << type << " jbutton:" << jbutton << endl;

    if (type == 0) // Playstation
    {
        switch (jbutton)
        {
        }
    }
    else // Xbox
    {
        switch (jbutton)
        {
        }
    }
}


void CSdlPong::AutoPlayer(const int& playerPosX, const int& playerPosY, int& playerDir)
{
    int ps = 0;
    player1dir = 0;
    const int ballMiddleX = ballPosX + spriteBall.logicalWidth() / 2;
    const int paddleMiddleX = playerPosX + spritePaddle.logicalWidth() / 2;
    const int ballMiddleY = ballPosY + spriteBall.logicalHeight() / 2;
    const int paddleMiddleY = playerPosY + spritePaddle.logicalHeight() / 2;

    const int diffX = std::abs(ballMiddleX - paddleMiddleX);
    const int diffY = std::abs(ballMiddleY - paddleMiddleY);
    //cout << "diff=" << diff << " ballMiddleY=" << ballMiddleY << " paddleMiddleY=" << paddleMiddleY << endl;

    if (std::abs(ballMiddleY - paddleMiddleY) < std::abs(playerSpeed))
    {
        ps = std::abs(ballMiddleY - paddleMiddleY);
    }
    else
    {
        ps = playerSpeed;
    }


    
    if (ballMiddleY < paddleMiddleY) playerDir = -ps;
    else
    if (ballMiddleY > paddleMiddleY) playerDir = ps;
    else
    playerDir = 0;

    cout << "diffX=" << diffX << " gameField width=" << mGameContext.mPlayField.Width() << endl;

    if (diffX > mGameContext.mPlayField.Width() * 0.5)
    {
        playerDir *= 0.5f;
    }

    //cout << "player1dir=" << player1dir << endl;
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
    

    // mGameContext.mPlayField.Width()=" << mGameContext.mPlayField.Width()
    //     << " mGameContext.mPlayField.Height(



    glColor4fv(colorWhite);
    spritePaddle.draw(player0posX, player0posY, 1.0);
    spritePaddle.draw(player1posX, player1posY, 1.0);

    if (mGameStatus == EGAMESTATUS_PLAYING || mGameStatus == EGAMESTATUS_WAITING)
    {
        spriteBall.draw(ballPosX, ballPosY, 1.0);
    }


    int x0 = mGameContext.mPlayField.Width() / 2 - spriteDigit[mScore[0]].logicalWidth() - 50;
    int x1 = mGameContext.mPlayField.Width() / 2 + 50;

    glColor3f(0.4f, 1.0f, 0.0f);
    spriteDigit[mScore[0]].draw(x0, 50, 1.0);
    glColor3f(1.0f, 0.4f, 0.0f);
    spriteDigit[mScore[1]].draw(x1, 50, 1.0);
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
        //cout << " xres=" << mXres << " yres=" << mYres << " Scale=" << mScale << endl;
    
    
        mOpenGL.StartProjectionView();

        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_BLEND);
    

        
        {
            glColor4fv(colorGrey);   
            int yd = 0;
            const float scale = 0.242f;
            const int xd = mGameContext.mPlayField.Width() / 2 - (spritePaddle.logicalWidth() / 2) * scale;
            while (yd < mGameContext.mPlayField.Height())
            {
                spritePaddle.draw(xd, yd, scale);
                yd += spritePaddle.logicalHeight() * scale * 2.0f;
            }            
        }

        if (mGameStatus == EGAMESTATUS_SHOW_LOGO)
        {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            DrawCenterPatch(&mLogoTex, 1.01, 1.0f, 1.0f, 1.0f, 1.0f);            
        }
        else
        if (mGameStatus == EGAMESTATUS_WIN_0)
        {
            DrawCenterPatch(&mWin0Tex, 1.003f, 2.0f, 0.4f, 1.0f, 0.0f);
        }
        else
        if (mGameStatus == EGAMESTATUS_WIN_1)
        {
            DrawCenterPatch(&mWin1Tex, 1.003f, 2.0f,  1.0f, 0.4f, 0.0f);
        }


        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		DrawPlayfield();


        glDisable(GL_BLEND);
    }
}

