#include "Window.hh"
#include "Video.hh"
#include <cstdio>
#include <iostream>

Window::Window() {}

Window::~Window()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
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

    if (!video.initVideo()) 
    {
        fprintf(stderr, "Failed to initialize video decoder.\n");
        return false;
    }

    window = SDL_CreateWindow("Bad Apple", video.getWidth(), video.getHeight(), SDL_WINDOW_OPENGL);

    renderer = SDL_CreateRenderer(window, nullptr);
    if (renderer == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create renderer: %s\n", SDL_GetError());
        return false;
    }
    SDL_SetRenderVSync(renderer, 1);

    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA32,
        SDL_TEXTUREACCESS_STREAMING,
        video.getWidth(),
        video.getHeight()
    );

    if (texture == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create texture: %s\n", SDL_GetError());
        return false;
    }

    if (window == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return false;
    }

    return true;
}


bool Window::drawFrame()
{
    if (!video.readFrame())
    {
        return false;
    }

    SDL_UpdateTexture(texture, nullptr, video.getPixels(), video.getWidth() * 4);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);

    return true;
}

SDL_Renderer *Window::getRenderer() const
{
    return renderer;
}