#ifndef PLANET_H
#define PLANET_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <stdbool.h>

#include "../Physics/Vector.h"
#include "Planet.h"
#include "../GameStatusSpecific/GameStatus.h"
#include "Obstacles/Asteroid.h"
#include "Obstacles/Wall.h"
#include "Gate.h"

typedef struct satellite sat;
typedef struct satellite *Sat;
//Ha nagybetûs a deklaráció, akkor pointer lesz

struct satellite{
    vect pos;
    vect vel;
    vect force;
    float rad;

    Pln plnarr;//(planet array)
    int numOf_pln;//A bolygók száma

    Astr astrarr;
    int numOf_astr;

    Wall wallarr;
    int numOf_wall;

    gate gate;
};

sat sat_init(float x, float y, float rad);
void sat_resetMotion(Sat s); //Újrainicializál a bolygók eltörlése nélkül
void sat_game_cleanup(Sat s);

void sat_drw(SDL_Surface *screen, Sat const s);//Megrajzolja a műholdat

//Hatások az objektumoktól
void sat_RUNNING_upd(Sat s);//Frissíti az adatokat (satellite_update())
void sat_SETTINGS_upd(Sat s, SDL_Event ev);
void sat_changeGameIfCollision(enum gameStatus *gameStatus, Sat const s);

//Bolygókhoz tartozó függvények
void sat_addPln(Sat s, Pln const p);//Hozzáad egy bolygót a műholdhoz és false-al tér vissza, ha túlindexelés van
bool sat_remPln(Sat s, int index); //Törli a bolygót lyukat a műhold struktúrájából (removePlanet()), visszatér, hogy sikeres-e

//Aszteroidákhoz tartozó függvények
Astr sat_astr_init(Sat s);

//Falakhoz tartozó függvények
void sat_wall_init(Sat s, int level, FILE *settings);
void sat_gate_init(Sat this, int level, FILE *settings);


#endif // PLANET_H
