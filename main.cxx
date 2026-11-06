#include "Player.hh"
#include <SDL3/SDL.h>

int main()
{
    int width = 1000;
    int height = 900;

    int pValue = 0;

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

            if (event.type == SDL_EVENT_KEY_DOWN && !event.key.repeat)
            {
                switch (event.key.key)
                {
                    case SDLK_ESCAPE: 
                        running = false;               
                        break;
                    case SDLK_1:      
                        player.window.setMode(false);  
                        player.audio.resetAudio();
                        break;
                    case SDLK_2:      
                        player.window.setMode(true);   
                        player.audio.resetAudio();
                        break;
                    case SDLK_SPACE:
                        pValue += 1;
                        player.pausePlayer(pValue);
                }
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