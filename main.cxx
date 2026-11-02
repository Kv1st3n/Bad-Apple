#include "Player.hh"
#include <SDL3/SDL.h>

int main()
{
    int width = 620;
    int height = 480;
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

        SDL_Delay(16); 
    }

    return 0;
}