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

struct satellite{
    vect pos;///<A műholdat reprezentáló kör középpontját tároló float x, y számpár
    vect vel;///<A műhold sebességét tároló vektor
    vect force;///<A műholdra ható eredő erőt tároló vektor
    float rad;///<A műholdat reprezentáló kör sugara

    Pln plnarr;///<A műholdra ható bolygók tömbjének pointere
    int numOf_pln;///<A műholdra ható bolygók száma

    Wall wallarr;///<A műholdat akadályozó falak tömbjének pointere (info fájlból olvasva)
    int numOf_wall;///<A műholdat akadályozó falak száma (info fájlból olvasva)

    gate gate;///<A kaput tároló struktúra. Itt kell átjutnia a műholdnak.

    int attempts///<A probálkozások számát tároló változó
};
/**Inicializál egy műholdat minden értéket 0-ra illetve a pointereket NULL-ra állítja.
*@param x   koordináta vízszintes komponense
*@param y   koordináta függőleges komponense
*@param rad   műholdat kirajzoló kör sugara
*@return Az inicializált műhold
*/
sat sat_init(float x, float y, float rad);

///Visszaállítja a műhold kiindulási helyzetét.
///     Megírás oka: Nem törli ki a bolygókat, de újrainicializál.
void sat_resetMotion(Sat s);

/**Ha visszalépünk a menübe, akkor kell ezt meghívni, hogy a memória ne szivárogjon.
*      Fő célja, hogy felszabadítsa a dinamikusan kezelt tömböket amikor a menübe lépünk,
*      mert ha új szintet választunk, akkor az újrainicializál és elveszítené az akkor éppen aktuális tömbök pointerét:
*
*      menü->játék->gameover->(a függvény meghívódik)->menü->új-játék(itt szivárogna a memória, mert a tömb-pointereket újrainicializálja a szintválasztás)
*/
void sat_resetInitialState(sat *this);

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
