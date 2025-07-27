//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CSdlSound.cpp
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <iostream>
#include <SDL2/SDL.h>
#include <global/GlobalSystemFunctions.h>
#include <pong/CSdlSound.h>

using namespace std;

extern "C"
{
    int stb_vorbis_decode_filename(const char *filename, int *channels, int *sample_rate, short **output);
}

static void showAudioSpec(const char* filename, const SDL_AudioSpec* as)
{
    cout << "file: " << filename << endl;
    cout << "  freq:" << as->freq << endl;
    cout << "  format:" << as->format << endl;
    cout << "  channels:" << (int) as->channels << endl;
    cout << "  silence:" << (int) as->silence << endl;
    cout << "  samples:" << as->samples << endl;
    cout << "  padding:" << as->padding << endl;
    cout << "  size:" << as->size << endl;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlSound
// METHODE       : CSdlSound
//
//
//
// ---------------------------------------------------------------------------

CSdlSound::CSdlSound()
{
    mMusic = NULL;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : static
// METHODE       : sMixAudioCallback
//
//
//
// ---------------------------------------------------------------------------



static void sMixAudioCallback(void* udata, Uint8* stream, int len)
{

    CSdlSound* sso = (CSdlSound*)udata;

    sso->MixSounds(stream, len);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlSound
// METHODE       : MixSounds
//
//
//
// ---------------------------------------------------------------------------

void CSdlSound::MixSounds(Uint8* stream, int len)
{
    //cout << "MixSounds len=" << len << " size=" << mPlaySoundsList.size() << endl;

    memset(stream, 0, len);
    if (mPlaySoundsList.size() != 0)
    {

        vector<SPlaySound> RemoveSoundVec;
        for (list<SPlaySound>::iterator it = mPlaySoundsList.begin();
            it != mPlaySoundsList.end();
            ++it)
        {
            if (it->mAudioLen != 0)
            {
                len = (len > it->mAudioLen ? it->mAudioLen : len);
                SDL_MixAudio(stream, it->mAudioPos, len, it->mVolume * SDL_MIX_MAXVOLUME);
                it->mAudioPos += len;
                it->mAudioLen -= len;
            }

            //cout << "audiolen=" << it->mAudioLen << endl;

            if (it->mAudioLen == 0)
            {
                if ((it->mMusicFlag) && (mMusic != NULL))
                {
                    it->mAudioLen = mMusic->mWavLength;
                    it->mAudioPos = mMusic->mWavBuffer;
                }
                else
                {
                    //cout << "remove sound" << endl;
                    RemoveSoundVec.push_back(*it);
                }
            }
        }
        if (RemoveSoundVec.size() > 0)
        {
            for (vector<SPlaySound>::iterator it = RemoveSoundVec.begin();
                it != RemoveSoundVec.end();
                ++it)
            {
                mPlaySoundsList.remove(*it);
            }
            if (mPlaySoundsList.size() == 0)
            {
                 memset(stream, 0, len);
            }
        }
    }



}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlSound
// METHODE       : InitAudio
//
//
//
// ---------------------------------------------------------------------------

bool CSdlSound::InitAudio()
{
    SDL_AudioSpec InAudioSpec;
    SDL_AudioSpec OutAudioSpec;

    //SDL_zero(InAudioSpec);
    //SDL_zero(OutAudioSpec);

    SDL_memset(&InAudioSpec, 0, sizeof(InAudioSpec));
    SDL_memset(&OutAudioSpec, 0, sizeof(OutAudioSpec));

    InAudioSpec.freq = 44100;
    InAudioSpec.format = AUDIO_S16;
    InAudioSpec.channels = 2;
    InAudioSpec.samples = 1024;
    InAudioSpec.callback = sMixAudioCallback;
    InAudioSpec.userdata = this;
    /* Open the audio device, forcing the desired format */
    //SDL_AudioDeviceID dev = SDL_OpenAudioDevice(NULL, 0, &InAudioSpec, &OutAudioSpec, SDL_AUDIO_ALLOW_ANY_CHANGE);
    //if (SDL_OpenAudio(&InAudioSpec, &OutAudioSpec) < 0)
    //if (dev == 0)
    if (SDL_OpenAudio(&InAudioSpec, &OutAudioSpec) < 0)
    {
        cout << "***** Couldn't open audio: " <<  SDL_GetError() << endl;
        return false;
    }
    return true;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlSound
// METHODE       : Finish
//
//
//
// ---------------------------------------------------------------------------

void CSdlSound::Finish()
{
    cout << "CSdlSound::Finish() start"  << endl;
    StopPlaying();
    SDL_Delay(100);
    SDL_LockAudio();
    SDL_Delay(100);
    for (vector<CSdlWavSound*>::iterator it = mSounds.begin(); it != mSounds.end(); ++it)
    {        
        SDL_FreeWAV((*it)->mWavBuffer);
        delete *it;
    }

    cout << "CSdlSound::Finish() ok"  << endl;
    SDL_UnlockAudio();
    SDL_CloseAudio();
    cout << "CSdlSound::Finish() end"  << endl;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlSound
// METHODE       : StartPlaying
//
//
//
// ---------------------------------------------------------------------------

void CSdlSound::StartPlaying()
{
    SDL_PauseAudio(0);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlSound
// METHODE       : StopPlaying
//
//
//
// ---------------------------------------------------------------------------

void CSdlSound::StopPlaying()
{
    SDL_PauseAudio(1);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlSound
// METHODE       :
//
//
//
// ---------------------------------------------------------------------------

int CSdlSound::LoadWav(const char* WavFilename)
{
    int n;


    CSdlWavSound* WavSound = new CSdlWavSound;

    if (WavSound->LoadWav(GlobalSystem::getPath(WavFilename).c_str()))
    {
        if (GlobalSystem::isEndianModeBig())
        {
            short* SoundPtr = (short*)WavSound->mWavBuffer;
            int WavSize16Bit = WavSound->mWavLength / 2;
            for (int n = 0; n < WavSize16Bit; n++)
            {
                GlobalSystem::swapWord(SoundPtr++);
            }
        }


        mSounds.push_back(WavSound);
        n = mSounds.size() - 1;
    }
    else
    {
        n = -1;
    }
    return n;
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlSound
// METHODE       : LoadOgg
//
//
//
// ---------------------------------------------------------------------------

int CSdlSound::LoadOgg(const char* OggFilename)
{
    int n;


    CSdlWavSound* WavSound = new CSdlWavSound;

    if (WavSound->LoadOgg(GlobalSystem::getPath(OggFilename).c_str()))
    {
        if (GlobalSystem::isEndianModeBig())
        {
            short* SoundPtr = (short*)WavSound->mWavBuffer;
            int WavSize16Bit = WavSound->mWavLength / 2;
            for (int n = 0; n < WavSize16Bit; n++)
            {
                GlobalSystem::swapWord(SoundPtr++);
            }
        }


        mSounds.push_back(WavSound);
        n = mSounds.size() - 1;
    }
    else
    {
        n = -1;
    }
    return n;
}



// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlSound
// METHODE       : PlayWav
//
//
//
// ---------------------------------------------------------------------------

void CSdlSound::PlayWav(int n)
{
    if (n >= 0)
    {
        SPlaySound PlaySound;

        PlaySound.mAudioPos = mSounds[n]->mWavBuffer;
        PlaySound.mAudioLen = mSounds[n]->mWavLength;

        SDL_LockAudio();
        mPlaySoundsList.push_back(PlaySound);
        SDL_UnlockAudio();
    }

    //cout << "Sounds=" << mPlaySoundsList.size() << endl;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlSound
// METHODE       : PlayMusic
//
//
//
// ---------------------------------------------------------------------------

void CSdlSound::PlayMusic(int n)
{
    if (mMusic == NULL)
    {
        SPlaySound PlaySound;

        PlaySound.mAudioPos = mSounds[n]->mWavBuffer;
        PlaySound.mAudioLen = mSounds[n]->mWavLength;
        PlaySound.mMusicFlag = true;
        PlaySound.mVolume = 0.05;
        mMusic = mSounds[n];

        SDL_LockAudio();
        mPlaySoundsList.push_back(PlaySound);
        SDL_UnlockAudio();
    }

    //cout << "Sounds=" << mPlaySoundsList.size() << endl;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlWavSound
// METHODE       : NewMusic
//
//
//
// ---------------------------------------------------------------------------

void CSdlSound::NewMusic(int n)
{
    SDL_LockAudio();
    mMusic = mSounds[n];
    SDL_UnlockAudio();
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlWavSound
// METHODE     : StopMusic
//
//
//
// ---------------------------------------------------------------------------

void CSdlSound::StopMusic()
{
    if (mMusic != NULL)
    {
        SDL_LockAudio();
        mMusic = NULL;
        SDL_UnlockAudio();
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlWavSound
// METHODE       : LoadWav
//
//
//
// ---------------------------------------------------------------------------


bool CSdlWavSound::LoadWav(const char* WavFilename)
{
    bool r;

    if (SDL_LoadWAV(WavFilename, &mWavSpec, &mWavBuffer, &mWavLength) == NULL)
    {
        cout	<< "***** Could not open " << WavFilename
                << ":" <<  SDL_GetError() << endl;
        r = false;
    }
    else
    {
        r = true;
    }
    return r;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSdlWavSound
// METHODE       : LoadOgg
//
//
//
// ---------------------------------------------------------------------------

bool CSdlWavSound::LoadOgg(const char* OggFilename)
{


    bool r = false;
    #if 1

    int channels;
    int sample_rate;    
    short * output;
    memset(&mWavSpec, 0, sizeof(SDL_AudioSpec));

    int sc = stb_vorbis_decode_filename(OggFilename, (int*) &mWavSpec.channels, &mWavSpec.freq, (short**) &mWavBuffer);
    if (sc == -1)
    {
        cout    << "***** Could not open OGG file:" << OggFilename << endl;
    }
    else
    {
        showAudioSpec(OggFilename, &mWavSpec);
        mWavLength = (int) sc * mWavSpec.channels * 2;
        mWavSpec.freq = 44100;
        mWavSpec.format = 32784;
        mWavSpec.samples = 4096;
        //mIsOgg = true;

        

        r = true;
    }
    #endif
    return r;
}

