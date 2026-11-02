#include "Window.hh"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>


Window::Window()
{

}
Window::~Window()
{

}

void Window::init_window(int width, int height)
{
    SDL_Window *window;
    bool done = false;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow
    (
        "Bad Apple",
        width,
        height,
        SDL_WINDOW_OPENGL
    );

    if (window == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
    }

    while (!done)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                done = true;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}