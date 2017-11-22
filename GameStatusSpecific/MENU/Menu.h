#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>

#include "LevelBox.h"

typedef struct menu menu;
typedef struct menu *Menu;

struct menu{
    LevelBox levelarr;
    int activeLevel;///Az éppen aktuális szintet tároló változó. -1, ha éppen nem választunk.
    int numOf_levels;
};

menu menu_init();


/**Visszaállítja az aktuálist szintet -1-re, ami azt jelenti, hogy nincsen aktuális szint.
*/
void menu_LevelChangeReinit(menu *this, int newActiveLevel);

void menu_upd(Menu theMenu, SDL_Event ev);

void menu_drw(SDL_Surface *screen, menu theMenu, TTF_Font *font);

void menu_cleanup(Menu theMenu);

#endif // MENU_H
