#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <stdbool.h>

#include "../Physics/Vector.h"
#include "../GameStatusSpecific/Button.h"



typedef struct planet pln;
typedef struct planet *Pln;
//Ha nagybetûs a deklaráció, akkor pointer lesz

struct planet {
    int index;
    vect pos;
    int strength;
    bool removeable;

    bool menuIsActive, screenSideLeft, pressing;
    button but_strengthUp, but_strengthDw, but_del;
};

pln pln_init(float x, float y, int strength);

void pln_drw(SDL_Surface *screen, Pln const p);
bool pln_hover(Pln const p, SDL_Event ev);//Az egér éppen benne van a bolygóban
void pln_upd(Pln pln, SDL_Event ev);

float pln_getRad(Pln const p);

///Menüvel kapcsoloatos függvények
float plnMenu_getRad(Pln pln);
vect plnMenu_getPos(Pln pln);

void plnMenu_upd(Pln pln, SDL_Event ev);
void plnMenu_drw(SDL_Surface *screen, Pln const pln, SDL_Event ev);
bool plnMenu_hover(Pln const pln, SDL_Event ev);//Az egér éppen benne van a bolygóban menüjében

///Gombokkal kapcsolatos függvények
void button_strengthUp_action(Pln pln);
void button_strengthDw_action(Pln pln);
//void button_del_action(Pln pln); függvény a satellite-ban van definiálva, és meghívva.

#endif // BLACKHOLE_H
