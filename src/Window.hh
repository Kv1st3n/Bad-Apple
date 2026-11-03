#ifndef WINDOW_HH
#define WINDOW_HH

#include <SDL3/SDL.h>
#include "Video.hh"

class Window {
public:
    Window();
    ~Window();

    bool initWindow(int width, int height);
    bool drawFrame();
    SDL_Renderer* getRenderer() const;

    Video video;

private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *texture = nullptr;
};

#endif