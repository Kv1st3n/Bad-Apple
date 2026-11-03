#ifndef PLAYER_HH
#define PLAYER_HH

#include "Window.hh"
#include "Audio.hh"

class Player
{
public:
    Player();
    ~Player();

    void initPlayer(int width, int height);
    bool pausePlayer();

private:
    Window window;
    Audio audio;
};


#endif