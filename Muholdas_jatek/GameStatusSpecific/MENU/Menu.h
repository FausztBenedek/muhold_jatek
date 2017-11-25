#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>

#include "LevelBox.h"

///@defgroup menuinfos Menu
///@{

/**A menüt és a LevelBox linkelt listáját kezelő struktúra, így a main-ben nem kell listát deklarálni.
*/
typedef struct Menu{
    LevelBox *levelarr;///<A LevelBox-ok linkelt listája
}Menu;

/**Inicializálja a LevelBox-ok linkelt listáját.
*  A levelBox-ok maguk számolják ki a pozíciójukat.
*/
Menu menu_init();


/**Frissíti a szintek linkelt listájának elemeit, ha elérhető a szint.
*@param data Csak akkor frissíti, ha a data.solved tömb megfelelő bool-ja true, tehát csakk akkor ha elérhető.
*/
void menu_upd(Menu *theMenu, SDL_Event ev, Data data);

/**Sorba meghívja a linkelt lista elemeinek a kirajzoló függvényét
*/
void menu_drw(SDL_Surface *screen, Menu theMenu, TTF_Font *font, Data data);

/**Feltakarítja a linkelt listát
*/
void menu_cleanup(Menu *theMenu);

///@}

#endif // MENU_H
