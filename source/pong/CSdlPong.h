//***************************************************************************
//
//
// @PROJECT  :	npong
// @VERSION  :	1.0
// @FILENAME :	CSdlPong.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGLAPPLICATION_H
#define CGLAPPLICATION_H

#include <string>
#include <vector>
#include <list>

#include <graflib/CGraflibPng.h>
#include <cgl/CGL_Texture.h>
#include <cgl/CGL_Patch2d.h>
#include <cgl/CGL_SaveScreen.h>
#include <pong/CSdlApp.h>
#include <pong/CVectorShape.h>
#include <pong/CVectorUnit.h>
#include <pong/CEnemyUnit.h>
#include <pong/CBaitUnit.h>
#include <pong/CVectorShot.h>
#include <pong/CExplosion.h>
#include <pong/SGameContext.h>
#include <pong/CPlayerUnit.h>
#include <pong/CSdlSound.h>
#include <pong/CDebrisUnit.h>
#include <pong/CSprite.h>
#include <pong/CPong.h>


enum
{
    SOUND_EXPLO1,
    SOUND_EXPLO2,
    SOUND_SCHUSS,
    SOUND_MUSIC
};

enum EGameStatus
{
    EGAMESTATUS_WAITING,    // Warten dass was passiert
    EGAMESTATUS_GAMEOVER,   // 
    EGAMESTATUS_PLAYING,    // Spiel laeuft
    EGAMESTATUS_SHOW_LOGO,  // Logo anzeigen
    EGAMESTATUS_WIN_0,      // Player 0 hat gewonnen
    EGAMESTATUS_WIN_1       // Player 1 hat gewonnen
};

class CSdlPong : public CSdlApp
{
    public:

        CSdlPong();
        ~CSdlPong();

        void Draw3DObjects();
        void Draw2DObjects();

        //void ManageInterface(CGL_Mouse* Mouse);
        bool ParseKeys(SDL_Keycode key, bool down) override;
        void JoystickButtonAction(int nr, int type, int jbutton) override;

        void LeftMouseButtonDown();
        void RightMouseButtonDown();
        void LeftMouseButtonUp();
        void RightMouseButtonUp();
        void MouseWheel(int d);


        void MouseMotion(int x, int y);
        void MouseMotionLeft(int x, int y);
        void MouseMotionRight(int x, int y);

        bool mFullscreen;
        void GameLoop() override;
        void Timer() override;
        void ResetPlayers() override;
        void moveJoyAxis(int joystick, int axis, int axisValue) override;

    protected:

        void SetResolution(int w, int h) override;
        void Zoom(float f);
        void LoadEnvTexture(bool Anaglyph);
        void InitGame();
        void FinishGame() override;


        const char* mActInfobox;
        bool mInitFlag;
        bool mShowInterface;


        /*******************************************
         *
         * GAME
         *
         ********************************************/
         
         
        void InitSprites();
        void DrawPlayfield() const;
		void DrawSpriteOnField(const CSprite& sprite, int x, int y) const;
		void createNewBait();
        void createNewBait(int nr);
        bool CheckIfPlayerHitsBall(const int& playerPosX, const int& playerPosY, float bx, float by) const;
        void ResetBall();
        void GameStatusPlaying();
        void AutoPlayer(const int& playerPosX, const int& playerPosY, int& playerDirY);        
        
        CSprite spriteDigit[10];
        CSprite spritePaddle;
        CSprite spriteBall;

		std::vector<CVector2<int>> mBaits;
        int mWaitCounter;
        int player0posX;
        int player0posY;
        int player1posX;
        int player1posY;
        int player0dir;
        int player1dir;
        int playerSpeed;
        int players;

        float ballPosX;
        float ballPosY;
        float ballDirX;
        float ballDirY;
        float ballStartFaktor;
        float logoScale;

        int soundBleep0;
        int soundBleep1;
        int soundBleep2;
        int soundGoal;
        int soundWin;
        int soundMusic;
		
        SGameContext mGameContext;
        EGameStatus mGameStatus;
        void DrawCenterPatch(CGL_Patch2d* pat,float speed, float scale, float r, float g, float b);

        CGL_Patch2d mLogoTex;                       // Titelbild-Textur
        CGL_Patch2d mWin0Tex;                       // Spieler 1 gewonnen
        CGL_Patch2d mWin1Tex;                       // Spieler 2 gewonnen
        CGL_Patch2d mGameOverTex;                   // "Game Over"-Textur
        CSdlSound mSdlSound;
        int mScore[2];
        
		//
		// ALT:
		//

#if 0		
        void InitEnemies();
        void DrawEnemies();
        void DrawDebris();
        void TestInside();
        void ParseSvg(std::string& SVGstr, CPolylineObject* poly, int Modifier);
        void ReadShapes(const char* Filename);
        void CalcPolyCenter(CPolylineObject* Poly);
        CVectorShape* FindShape(const char* Shapename);
        bool ShotHit(CVectorUnit* shot, std::vector<CVector2<float> >* explo);
        void EnemyShotHit();
        void NewAttackWave(bool Reset = false);
        void NewDebris(float xpos, float ypos, int Fakt, const float* Color, const CVector2<float>& ddir);
        void InitBait();
        void RunPlayers();
        void TestAvoid();
        void TestEnemyShoot();
        void StartGame();
        void GotoWaitStatus();


        void RemoveInactive(std::list<CVectorUnit*>& ul);
        void ClearList(std::list<CVectorUnit*>& ulist);

        void Shot(int Player);
        void ShotEnemy(CVectorUnit* who);
        void RunUnits();
        bool TestCrash(CVectorUnit* vu);
        bool TestPlayerCrash();
        
        void PlayerExplodes(int p);
        void BonusScore();


        void DrawUnitList(std::list<CVectorUnit*>& ulist, int HitStatus);
        void DrawUnitPoints(std::list<CVectorUnit*>& ulist);
        void DrawScore(int xpos, int Score, const float* Color);

        void DrawCenterScore(int xpos, int Score, const float* Color);
        void DrawLevel();
        int Digits(int k);

        void WriteHighScore();
        void ReadHighScore();

        CPlayerUnit mPlayer[2];
        int mScore[2];
        int mHighScore;
        int mLevel;
        std::list<CVectorUnit*> mUnitList;
        std::list<CVectorUnit*> mBaitList;
        std::list<CVectorUnit*> mShotList;
        std::list<CVectorUnit*> mEnemyShotList;
        std::list<CVectorUnit*> mExploList;
        std::list<CVectorShape*> mShapeList;
        std::list<CDebrisUnit*> mDebrisList;
        bool mInitEnemies;
        CVectorUnit mZiffern[10];
        CGL_Patch2d mLogoTex;                       // Titelbild-Textur
        CGL_Patch2d mWin0Tex;                       // Spieler 1 gewonnen
        CGL_Patch2d mWin1Tex;                       // Spieler 2 gewonnen
        CGL_Patch2d mGameOverTex;                   // "Game Over"-Textur
        CSdlSound mSdlSound;
        int mGameOverTime;                          // Zeit fuer GameOver-Status
        bool mExploded;
        float mLevelDrawScale;                      // Scalierung der Levelanzeige
        int mLevelDrawWait;                         // Verzoegerung fuer Levelanzeige
        CGL_SaveScreen mSaveScreenGL;               // Bildschirm abspeichern        
        bool mScreenSaveMode;
#endif        
};

#endif
