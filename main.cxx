#include "Player.hh"
#include <SDL3/SDL.h>

int main()
{
    int width = 1000;
    int height = 900;
    Player player;
    player.initPlayer(width, height);

    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }

        if (!player.window.drawFrame())
        {
            running = false;
        }

        SDL_Delay(30);
    }

    return 0;
}