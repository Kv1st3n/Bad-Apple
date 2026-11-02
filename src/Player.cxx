#include "Window.hh"
#include "Audio.hh"
#include "Player.hh"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_mixer/SDL_mixer.h>


Player::Player()
{

}

Player::~Player()
{

}

void Player::initPlayer(int width, int height)
{
    window.initWindow(width, height);
    audio.initAudio();
}