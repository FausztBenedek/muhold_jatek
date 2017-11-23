#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>

#include "../Button.h"

/**A gameover képernyő deklarációja
*A gombok funkcionalitása a game_status_from_GAMEOVER_to_MENU_or_SETTING() függvényben a gameStatusChangingFunctions modulban
*/
typedef struct GameOverScreen{
    Button toMenu;///<A menübe lépő gomb
    Button newGame;///<Új játék indítása
}GameOverScreen;

/**Inicializálja a gombokat a megfelelő helyre
*/
GameOverScreen gameOverScreen_init();

/**Megrajzolja a gombokat
*@param *font Ezt a betűtípust használja fel a gomb feliratához
*/
void gameOverScreen_drw(SDL_Surface *screen, GameOverScreen this, TTF_Font *font);

/**A gombokat frissíti.
*/
void gameOverScreen_upd(GameOverScreen *this, SDL_Event ev);

/**Feltakarítja a gombjai által lefoglalt dinamikus memóriát.
*/
void gameOverScreen_cleanup(GameOverScreen *this);

#endif//GAMEOVER_H
