#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <stdbool.h>

#include "../Physics/Vector.h"
#include "../GameStatusSpecific/Button.h"

/** A Pln (planet) struktúra a bolygókat és a hozzájuk tartozó menüt tárolja.
*Minden bolygó rendelkezik egy saját menüvel. A menü adatai bele vannak ágyazva ebbe a struktúrába.
*A bolygó menüje nem azonos a játék menüjével. Minden bolygónak saját menüje van.
*/
typedef struct Pln {
    int index;///<Minden bolygónak van egy indexe, amivel
    Vect pos;///<Helyzetet tároló pont
    int strength;///<A bolygó vonzerejének mértéke. Ez nem a bolygó sugara, de ebből számolja a pln_getRad() függvény.
    bool removeable;///<Nincs funkció (későbbi fejlesztéshez kell)

    /**Akkor true, ha az adott bolygó menüjét kezeljük
    *   1. Ha az egér a BOLYGÓ fölé ér true lesz és az is marad.
    *   2. Ha az egér nincs a MENÜ fölött false lesz és az is marad.
    */
    bool menuIsActive;

    /**Ha a bolygó a képernyő bal oldalán van akkor true, egyébként false.
    *Ez a bolygó menüjének megnyitásakor fontos.
    */
    bool screenSideLeft;

    bool pressing;///<A bolygó vonszolásához kell
    Button but_strengthUp;///<A bolygó méretét növeli. Funkció: (button_strengthUp_action(...))
    Button but_strengthDw;///<A bolygó méretét csökkenti. Funkció: (button_strengthDw_action(...))
    Button but_del;///<Törli a bolygót. Funkció a satellite modulban: (sat_plnarr_button_del_action(...))
}Pln;


/**Egyszerre inicializálja magát a bolygót, illetve a bolygóhoz tartozó menüt.
*
*/
Pln pln_init(float x, float y, int strength);

/**Kirajzolja a bolygót a képernyőre. CSAK a bolygót, a menüjét nem.
*/
void pln_drw(SDL_Surface *screen, Pln * const p);

/**Megállapítja, hogy az egér a bolygó felett van-e.
*@return true, ha benne van az egér a bolygóban és false, ha nem.
*/
bool pln_hover(Pln * const this, SDL_Event ev);

/**Ez a függvény CSAK a vonszolásért felelős. A menüböl kezelhető változók a plnMenu_upd() függvényben frissülnek.
*/
void pln_upd(Pln * this, SDL_Event ev);

///@return A bolygó sugarát számítja a srength változóból.
float pln_getRad(Pln * const p);

//--------------------------------------
//Menüvel kapcsoloatos függvények
//--------------------------------------

/**@return A menü körének sugarát számítja ki.
*/
float plnMenu_getRad(Pln * this);
/**@return A menü középpontjának koordinátáival tér vissza. Ennek megállapításához a bool screenSideLeft változót is felhasználja.
*/
Vect plnMenu_getPos(Pln * this);

/**Feladatai:
*   1. Frissíti mindhárom gombot.
*   2. A strength változót növelő és csökkentő gomb funkcionalitását intézi.
*   3. Beállítja a bool menuIsActive változót.
*/
void plnMenu_upd(Pln * this, SDL_Event ev);

/**Kirajzolja a:
*   1. Menüt ábrázoló kört
*   2. Gombokat
*/
void plnMenu_drw(SDL_Surface *screen, Pln * const this, SDL_Event ev, TTF_Font *font);

/**@return true, ha benne van az egér a menüben és false, ha nem.
*CSAK AKKOR szabad MEGHÍVNI, amikor a menuIsActive == true.
*/
bool plnMenu_hover(Pln * const this, SDL_Event ev);

//--------------------------------------
//Gombokkal kapcsolatos függvények
//--------------------------------------
/**A bolygó erejét növeli, ha a but_strengthUp gombot megnyomjuk.
*/
void button_strengthUp_action(Pln * this);

/**A bolygó erejét csökkenti, ha a but_strengthDw gombot megnyomjuk.
*/
void button_strengthDw_action(Pln * this);

#endif // BLACKHOLE_H
