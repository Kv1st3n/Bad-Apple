#include "Audio.hh"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_mixer/SDL_mixer.h>

Audio::Audio()
{

}
Audio::~Audio()
{   
    clearAudio();  
}

void Audio::clearAudio()
{
    if (props)
    {
        SDL_DestroyProperties(props);
    }

    if (track) 
    {
        MIX_DestroyTrack(track);
        track = nullptr;
    }

    if (audio) 
    {
        MIX_DestroyAudio(audio);
        audio = nullptr;
    }

    if (mixer) 
    {
        MIX_DestroyMixer(mixer);
        mixer = nullptr;
    }

    MIX_Quit();
}

void Audio::initAudio()
{
    if (!MIX_Init())
    {
        fprintf(stderr, "Error initializing SDL3_mixer: %s\n", SDL_GetError());
        return;
    }

    mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    if (!mixer)
    {
        fprintf(stderr, "Error creating mixer device: %s\n", SDL_GetError());
        return;
    }

    const char *path = "bad-apple-audio.mp3";
    bool predecode = false;

    audio = MIX_LoadAudio(mixer, path, predecode);
    if (!audio)
    {
        fprintf(stderr, "Error getting audio: %s\n", SDL_GetError());
        return;
    }

    track = MIX_CreateTrack(mixer);
    SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, -1);

    bool trackAudio = MIX_SetTrackAudio(track, audio);
    if (!trackAudio)
    {
        fprintf(stderr, "Error building track audio: %s\n", SDL_GetError());
        return;
    }

    if (!MIX_PlayTrack(track, props))
    {
        fprintf(stderr, "Error playing track: %s\n", SDL_GetError());
    }
}

void Audio::resetAudio()
{
    clearAudio();
    initAudio();
}

void Audio::pauseAudio()
{
    if (track != nullptr)
    {
        MIX_PauseTrack(track);
    }
}

void Audio::resumeAudio()
{
    if (track != nullptr)
    {
        MIX_ResumeTrack(track);
    }
}
