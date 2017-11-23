#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <stdbool.h>

#include "../Physics/Vector.h"
#include "../GameStatusSpecific/Button.h"







typedef struct Pln {
    int index;///<Minden bolygónak van egy indexe, amivel
    Vect pos;///<Helyzetet tároló pont
    int strength;
    bool removeable;

    bool menuIsActive, screenSideLeft, pressing;
    button but_strengthUp, but_strengthDw, but_del;
}Pln;


/**Inicializás
*/
Pln pln_init(float x, float y, int strength);

void pln_drw(SDL_Surface *screen, Pln * const p);
bool pln_hover(Pln * const this, SDL_Event ev);//Az egér éppen benne van a bolygóban
void pln_upd(Pln * this, SDL_Event ev);

float pln_getRad(Pln * const p);

///Menüvel kapcsoloatos függvények
float plnMenu_getRad(Pln * this);
Vect plnMenu_getPos(Pln * this);

void plnMenu_upd(Pln * this, SDL_Event ev);
void plnMenu_drw(SDL_Surface *screen, Pln * const this, SDL_Event ev, TTF_Font *font);
bool plnMenu_hover(Pln * const this, SDL_Event ev);//Az egér éppen benne van a bolygóban menüjében

///Gombokkal kapcsolatos függvények
void button_strengthUp_action(Pln * this);
void button_strengthDw_action(Pln * this);
//void button_del_action(Pln pln); függvény a satellite-ban van definiálva, és meghívva.

#endif // BLACKHOLE_H
