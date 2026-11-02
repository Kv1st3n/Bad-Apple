#ifndef WINDOW_HH
#define WINDOW_HH

#include <SDL3/SDL.h>

class Window {
public:
    Window();
    ~Window();

    bool initWindow(int width, int height);

private:
    SDL_Window *window = nullptr;
};

#endif