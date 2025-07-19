//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	COpenAL.cpp
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

#include <CAL_OpenAL.h>

using namespace std;

//---------------------------------------------------------------------------
//
// Class:    COpenAL
// Method:   LoadSound
//
// Parameter: const char* Filename - name of wav-file
//            bool looping - looping-flag
//
// Return:
//
//---------------------------------------------------------------------------

void COpenALSound::LoadSound(const char* fname, bool looping)
{
    //load our sound
    ALboolean loop;

    loop = looping;

    alutLoadWAVFile((ALbyte*)fname, &alFormatBuffer, (void**)&alBuffer, (ALsizei*)&alBufferLen, &alFreqBuffer, &loop);

    alGenSources(1, &alSource);
    alGenBuffers(1, &alSampleSet);
    alBufferData(alSampleSet, alFormatBuffer, alBuffer, alBufferLen, alFreqBuffer);
    alSourcei(alSource, AL_BUFFER, alSampleSet);

    alutUnloadWAV(alFormatBuffer, alBuffer, alBufferLen, alFreqBuffer);

    //set the pitch
    alSourcef(alSource, AL_PITCH, 1.0f);
    //set the gain
    alSourcef(alSource, AL_GAIN, 1.0f);
    //set looping to true
    alSourcei(alSource, AL_LOOPING, looping);
}


//---------------------------------------------------------------------------
//
// Class:    COpenAL
// Method:   SetSoundPosition
//
// Parameter:
//
//
// Return:
//
//---------------------------------------------------------------------------

void COpenALSound::SetSoundPosition(float x, float y, float z)
{
    //set the sounds position
    alSource3f(alSource, AL_POSITION, x, y, z);
}


//---------------------------------------------------------------------------
//
// Class:    COpenAL
// Method:   SetSoundVelocity
//
// Parameter:
//
//
// Return:
//
//---------------------------------------------------------------------------

void COpenALSound::SetSoundVelocity(float vx, float vy, float vz)
{
    //set the sounds velocity
    alSource3f(alSource, AL_VELOCITY, vx, vy, vz);
}


//---------------------------------------------------------------------------
//
// Class:    COpenAL
// Method:
//
// Parameter:
//
//
// Return:
//
//---------------------------------------------------------------------------
//
// this function makes a sound source relative so all direction and velocity
// parameters become relative to the source rather than the listener
// useful for background music that you want to stay constant relative to the listener
// no matter where they go

void COpenALSound::SetSourceRelative()
{
    alSourcei(alSource, AL_SOURCE_RELATIVE, AL_TRUE);
}


//---------------------------------------------------------------------------
//
// Class:    COpenAL
// Method:   PlaySound
//
// Parameter:
//
//
// Return:
//
//---------------------------------------------------------------------------

void COpenALSound::PlaySound()
{
    alSourcePlay(alSource);
}


//---------------------------------------------------------------------------
//
// Class:    COpenAL
// Method:   StopSound
//
// Parameter:
//
//
// Return:
//
//---------------------------------------------------------------------------

void COpenALSound::StopSound()
{
    alSourceStop(alSource);
}


//---------------------------------------------------------------------------
//
// Class:    COpenAL
// Method:   DestroySound
//
// Parameter:
//
//
// Return:
//
//---------------------------------------------------------------------------

void COpenALSound::DestroySound()
{
    alDeleteSources(1, &alSource);
    alDeleteBuffers(1, &alSampleSet);
}


//---------------------------------------------------------------------------
//
// Class:    COpenAL
// Method:   ~COpenAL
//
// Parameter:
//
//
// Return:
//
//---------------------------------------------------------------------------

COpenAL::~COpenAL()
{
    DestroyAll();
}


//---------------------------------------------------------------------------
//
// Class:    COpenAL
// Method:   Finish
//
// Parameter:
//
//
// Return:
//
//---------------------------------------------------------------------------

void COpenAL::DestroyAll()
{
    for (vector<COpenALSound*>::iterator as = mSounds.begin();
        as != mSounds.end();
        ++as)
    {
        if (*as != NULL)
        {
            (*as)->StopSound();
            (*as)->DestroySound();
            delete (*as);
            *as = NULL;
        }
    }

    mSounds.clear();
    mSoundNr = 0;
}


//---------------------------------------------------------------------------
//
// Class:    COpenAL
// Method:   AddSound
//
// Parameter:
//
//
// Return:
//
//---------------------------------------------------------------------------

unsigned int COpenAL::AddSound(const char* fname, bool looping)
{
    COpenALSound* AlSound = new COpenALSound;

    AlSound->LoadSound(fname, looping);
    mSounds.push_back(AlSound);

    return mSoundNr++;
}


//---------------------------------------------------------------------------
//
// Class:    COpenAL
// Method:   Init
//
// Parameter:
//
//
// Return:
//
//---------------------------------------------------------------------------

void COpenAL::Init()
{
    alutInit(0, NULL);
    mSoundNr = 0;
}


//---------------------------------------------------------------------------
//
// Class:    COpenAL
// Method:   SetListenerPosition
//
// Parameter:
//
//
// Return:
//
//---------------------------------------------------------------------------

void COpenAL::SetListenerPosition(float x, float y, float z)
{
    //set the position using 3 seperate floats
    alListener3f(AL_POSITION, x, y, z);
}


//---------------------------------------------------------------------------
//
// Class:    COpenAL
// Method:   SetListenerOrientation
//
// Parameter:
//
//
// Return:
//
//---------------------------------------------------------------------------

void COpenAL::SetListenerOrientation(float fx, float fy, float fz, float ux, float uy, float uz)
{
    //set the orientation using an array of floats
    float vec[6];

    vec[0] = fx;
    vec[1] = fy;
    vec[2] = fz;
    vec[3] = ux;
    vec[4] = uy;
    vec[5] = uz;
    alListenerfv(AL_ORIENTATION, vec);
}
