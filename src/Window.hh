#ifndef WINDOW_HH
#define WINDOW_HH

#include <SDL3/SDL.h>
#include "Video.hh"
#include "AsciiVideo.hh"

class Window {
public:
    Window();
    ~Window();

    bool initWindow(int width, int height);
    bool drawFrame(int pValue, int rampValue);
    SDL_Renderer* getRenderer() const;

    Video video;
    AsciiVideo asciiVideo;
    bool asciiMode = false;
    void setMode(bool ascii);

private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *texture = nullptr;
};

#endif