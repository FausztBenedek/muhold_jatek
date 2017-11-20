#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>

#include "../Button.h"

typedef struct gameOverScreen{
    button toMenu, newGame;
}gameOverScreen;

gameOverScreen gameOverScreen_init();

void gameOverScreen_drw(SDL_Surface *screen, gameOverScreen this);

void gameOverScreen_upd(gameOverScreen *this, SDL_Event ev);

#endif//GAMEOVER_H
