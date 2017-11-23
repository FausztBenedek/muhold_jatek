#ifndef WINNING_H
#define WINNING_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>

#include "../Button.h"

/**A "Sikerült" képernyő deklarációja.
*/
typedef struct WinningScreen{
    button toMenu;///<A menübe lépésért felelős gomb
    button nextLevel;///<A következő szintre lépésért felelős gomb.
}WinningScreen;

/**Inicializálja a gombokat a megfelelő helyre
*/
WinningScreen winningScreen_init();

/**Megrajzolja a gombokat
*@param *font Ezt a betűtípust használja fel a gomb feliratához
*/
void winningScreen_drw(SDL_Surface *screen, WinningScreen this, TTF_Font *font);

/**A gombokat frissíti.
*/
void winningScreen_upd(WinningScreen *this, SDL_Event ev);

/**Feltakarítja a gombjai által lefoglalt dinamikus memóriát.
*/
void winningScreen_cleanup(WinningScreen *this);

#endif // WINNING_H
