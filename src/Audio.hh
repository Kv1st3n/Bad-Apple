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

private:
    MIX_Mixer *mixer = nullptr;
    MIX_Track *track = nullptr;
    MIX_Audio *audio = nullptr;
};


#endif