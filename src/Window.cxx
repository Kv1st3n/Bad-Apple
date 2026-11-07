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

    if (asciiMode)
    {
        const int cols = 120;
        const int rows = 90;

        if (!asciiVideo.initAscii("BadApple.mp4", cols, rows))
        {
            return false;
        }

        window = SDL_CreateWindow("Bad Apple (ASCII)", cols * 8, rows * 8, SDL_WINDOW_RESIZABLE);
        if (!window)
        {
            return false;
        }

        renderer = SDL_CreateRenderer(window, nullptr);
        if (!renderer)
        {
            return false;
        }
        SDL_SetRenderVSync(renderer, 1);

        SDL_SetRenderLogicalPresentation(renderer, cols * 8, rows * 8, SDL_LOGICAL_PRESENTATION_LETTERBOX);
        return true;
    }

    if (!video.initVideo())
    {
        fprintf(stderr, "Failed to initialize video decoder.\n");
        return false;
    }

    window = SDL_CreateWindow("Bad Apple", video.getWidth(), video.getHeight(), SDL_WINDOW_OPENGL);
    if (!window)
    {
        return false;
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer)
    {
        return false;
    }
    SDL_SetRenderVSync(renderer, 1);

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
        SDL_TEXTUREACCESS_STREAMING, video.getWidth(), video.getHeight());

    return texture != nullptr;
}

bool Window::drawFrame(int pValue, int rampValue)
{   

    if (pValue % 2 == 0)
    {
        return true;
    }

    if (asciiMode)
    {
        std::string ascii;
        if (!asciiVideo.readAsciiFrame(ascii, rampValue))
        {
            return false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        float y = 0.0f;
        size_t start = 0;
        while (start < ascii.size())
        {
            size_t end = ascii.find('\n', start);
            if (end == std::string::npos)
            {
                end = ascii.size();
            }

            std::string line = ascii.substr(start, end - start);
            SDL_RenderDebugText(renderer, 0.0f, y, line.c_str());

            y += 8.0f;
            start = end + 1;
        }

        SDL_RenderPresent(renderer);
        return true;
    }

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

void Window::setMode(bool ascii)
{
    asciiMode = ascii;

    video.close();
    asciiVideo.close();

    if (texture)  
    { 
        SDL_DestroyTexture(texture);
        texture = nullptr; 
    }
    if (renderer) 
    { 
        SDL_DestroyRenderer(renderer); 
        renderer = nullptr; 
    }
    if (window)   
    { 
        SDL_DestroyWindow(window);     
        window = nullptr; 
    }

    initWindow(0, 0);
}

