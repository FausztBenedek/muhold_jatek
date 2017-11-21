#ifndef WINNING_H
#define WINNING_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>

#include "../Button.h"

typedef struct WinningScreen{
    button toMenu, nextLevel;
}WinningScreen;

WinningScreen winningScreen_init();

void winningScreen_drw(SDL_Surface *screen, WinningScreen this, TTF_Font *font);

void winningScreen_upd(WinningScreen *this, SDL_Event ev);

#endif // WINNING_H
