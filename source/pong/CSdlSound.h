//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CSdlSound.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CSDLSOUND_H
#define CSDLSOUND_H

#include <vector>
#include <list>

class CSdlWavSound
{
    public:

        CSdlWavSound()
        {
            mWavLength = 0;
            mWavBuffer = NULL;
        }

        bool LoadWav(const char* WavFilename);
        bool LoadOgg(const char* OggFilename);

        SDL_AudioSpec mWavSpec;
        Uint32 mWavLength;
        Uint8* mWavBuffer;
};

struct SPlaySound
{
    SPlaySound()
    {
        mMusicFlag = false;
        mVolume = 0.3;
    }

    Uint32	mAudioLen;
    Uint8*	mAudioPos;
    float	mVolume; // zwischen 0.0 und 1.0
    bool	mMusicFlag;

    bool operator==(const SPlaySound& k) const
    {
        return mAudioPos == k.mAudioPos;
    }
};


class CSdlSound
{
    public:

        CSdlSound();

        bool InitAudio();
        int LoadWav(const char* WavFilename);
        int LoadOgg(const char* OggFilename);
        void StartPlaying();
        void StopPlaying();
        void PlayWav(int n);
        void PlayMusic(int n, float volume=0.05f);
        void NewMusic(int n);
        void Finish();
        void MixSounds(Uint8* stream, int len);
        void StopMusic();

    protected:

        std::vector<CSdlWavSound*> mSounds;
        std::list<SPlaySound> mPlaySoundsList;
        CSdlWavSound* mMusic;
};

#endif
