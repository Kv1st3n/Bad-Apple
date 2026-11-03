#ifndef PLAYER_HH
#define PLAYER_HH

#include "Window.hh"
#include "Audio.hh"

class Player
{
public:
    Player();
    ~Player();

    Window window;

    void initPlayer(int width, int height);
    bool pausePlayer();

private:
    Audio audio;
};


#endif