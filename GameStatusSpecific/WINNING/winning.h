#ifndef WINNING_H
#define WINNING_H

#include "../Button.h"

///@defgroup winningScreen Siker-képenyő
///@{

/**A "Sikerült" képernyő deklarációja.
*A gombok funkcionalitását kezelő függvény: game_status_from_GAMEOVER_to_MENU_or_SETTING(...) a gameStatusChangingFunctions modulban
*/
typedef struct WinningScreen{
    Button toMenu;///<A menübe lépésért felelős gomb
    Button nextLevel;///<A következő szintre lépésért felelős gomb.
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

///@}
#endif // WINNING_H
