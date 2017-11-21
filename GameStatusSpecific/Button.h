#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>

typedef struct button button;
typedef struct button *Button;

struct button {
    float x, y, w, h;
    bool hover, clicked;

    char *subscription;
};

/*
A gombok mûködése:
    1. Ahhoz a modulbeli struktúrához kell hozzáadni, amiben használni szeretnénk
    2. Az button_init() függvény a megfelelõ _init() függvényben lesz meghívva
    3. A button_upd() függvény a megfelelõ _upd() függvényben lesz meghívva
    4. A button_drw() függvény a megfelelõ _drw() függvényben lesz meghívva
    5. A funkcionalitásának leírása eltérő lehet, de a deklarációja: button_definedName_action();
*/

button button_init(float x, float y, float w, float h, char *subscription);

void button_upd(Button b, SDL_Event ev);
void button_drw(SDL_Surface *screen, Button b, TTF_Font *font);

bool button_hover(Button b, SDL_Event ev);

#endif
