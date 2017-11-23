#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>

typedef struct button button;
typedef struct button *Button;


/**
A gombok mûködése:
    1. Ahhoz a modulbeli struktúrához kell hozzáadni, amiben használni szeretnénk
    2. A button_init() függvény a megfelelõ _init() függvényben lesz meghívva
    3. A button_upd() függvény a megfelelõ _upd() függvényben lesz meghívva
    4. A button_drw() függvény a megfelelõ _drw() függvényben lesz meghívva
    5. A funkcionalitásának leírása eltérő lehet.
*/
struct button {
    float x, y, w, h;///<(x, y) bal felső sarok koordinátája, w = szélesség, h = magasság
    bool hover;///<Akkor és csak akkor true, ha a gombon van az egér (klikkelés nélkül is)
    bool clicked;///<Akkor és csak akkor true, ha a gombra klikkeltek

    char *subscription;///<A gomb feliratát tárolja egy a megadott szring hosszúságával egyező karaktertömbben (malloc())
};

/**Létrehoz egy gombot. Ha egy struktúrához kell hozzáadni a gombot,
*akkor a struktúrához tartozó _init függvényben kell meghívni.
*A függvény paramétereinek leírását a gomb struktúra tartalmazza.
*/
button button_init(float x, float y, float w, float h, char *subscription);

/**Felelős a clicked és a hover paraméter beállításáért. (A button_hover() függvényt meghívja)
*/
void button_upd(Button b, SDL_Event ev);

/**Kirajzolja a gombot a *screen-re a *font-ot használva a felirathoz,
*és ehhez figyeli a button.clicked és a button.hover állapotát.
*/
void button_drw(SDL_Surface *screen, Button b, TTF_Font *font);

/**Ez a függvény beállítja a button.hoover-t.
*/
bool button_hover(Button b, SDL_Event ev);

/**Felszabadítja az init-ben lefoglalt memórát a subscription-hoz.
*/
void button_cleanup(Button this);

#endif
