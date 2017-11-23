#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>

#include "LevelBox.h"

typedef struct menu menu;
typedef struct menu *Menu;

struct menu{
    levelBox * levelarr;
    int numOf_levels;
};

menu menu_init();

void menu_upd(Menu theMenu, SDL_Event ev, Data data);

void menu_drw(SDL_Surface *screen, menu theMenu, TTF_Font *font, Data data);

void menu_cleanup(Menu theMenu);

#endif // MENU_H
