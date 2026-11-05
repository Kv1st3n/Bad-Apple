#ifndef AUDIO_HH
#define AUDIO_HH

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_mixer/SDL_mixer.h>

class Audio
{
public:
    Audio();
    ~Audio();

    void initAudio();
    void clearAudio();
    void resetAudio();

    void pauseAudio();
    void resumeAudio();

private:
    MIX_Mixer *mixer = nullptr;
    MIX_Track *track = nullptr;
    MIX_Audio *audio = nullptr;
    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_AudioDeviceID device;
};


#endif