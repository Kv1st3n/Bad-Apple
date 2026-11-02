#include "Window.hh"
#include <cstdio>

Window::Window() {}

Window::~Window()
{
    if (window)
    {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

bool Window::initWindow(int width, int height)
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(
        "Bad Apple",
        width,
        height,
        SDL_WINDOW_OPENGL
    );

    if (window == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return false;
    }

    return true;
}