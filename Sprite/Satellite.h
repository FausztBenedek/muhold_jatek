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
/**Inicializál egy műholdat minden értéket 0-ra illetve a pointereket NULL-ra állítja.
*@param x   koordináta vízszintes komponense
*@param y   koordináta függőleges komponense
*@param rad   műholdat kirajzoló kör sugara
*@return Az inicializált műhold
*/
sat sat_init(float x, float y, float rad);

///Visszaállítja a műhold kiindulási helyzetét.
///Megírás oka: Nem törli ki a bolygókat, de újrainicializál.
void sat_resetMotion(Sat s); //Újrainicializál a bolygók eltörlése nélkül

///Felszabadítja a műhold osztály által lefoglalt memóriát.
void sat_game_cleanup(Sat s);

/**Kirajzolja a műhold aktuális helyzetét a képernyőre.
*Felhasználja a pozíciót, és a sugarat.
*A kaput megrajzoló függvény is itt hívódik meg.
*/
void sat_drw(SDL_Surface *screen, Sat const s);//Megrajzolja a műholdat

/**A műhold változóinak a változásáért felelős RUNNING állapotban.
*   1. Kiszámolja az eredő erőt.
*   2. Megoldja, hogy a műhold visszapattanjon a képernyő széléről
*/
void sat_RUNNING_upd(Sat s);

/**A műhold változóinak a változásáért felelős SETTING állapotban
*   1. Bolygókat ad hozzá oda ahova kattintunk, illetve letilt bizonyos helyeket
*   2. Ehhez teszteli, hogy mi az aktuális event
*/
void sat_SETTINGS_upd(Sat s, SDL_Event ev);

//Bolygókhoz tartozó függvények
/**Hozzáad egy már inicializált bolygót a játékhoz és eltárolja műhold plnarr változójában
**@param p   az inicializált bolygó
*/
void sat_addPln(Sat s, Pln const p);
/**Töröl egybolygót a műhold listájából, ha a bolygó eltávolítható.
*@param index   Minden bolygónak van egy egyedi indexe, ez megfelel a bolygótömb indexének
*@return    Ha a bolygó eltávolítható akkor true, ha nem akkor false
*/
bool sat_remPln(Sat s, int index);

/**Beolvassa a falakhoz szükséges információakt fájból.
*   1. Bal oldal,
*   2. Felső oldal,
*   3. Szélesség,
*   4. Magasság
*@param level   Szint száma a fájl szerint (0.-tól indul)
*@param settings    Fájl elejére mutató pointer
*/
void sat_wall_init(Sat s, int level, FILE *settings);

/**Beolvassa a kapuhoz szükséges információakt fájból.
*   1. Felső oldal,
*   2. Magasság
*@param level   Szint száma a fájl szerint (0.-tól indul)
*@param settings    Fájl elejére mutató pointer
*/
void sat_gate_init(Sat this, int level, FILE *settings);


#endif // PLANET_H
