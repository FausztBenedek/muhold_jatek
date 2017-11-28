#ifndef FUNC_UPD_AND_DRW_H
#define FUNC_UPD_AND_DRW_H

#include "GameStatusSpecific/GameStatus.h"
#include "GameStatusSpecific/GameStatusChangingFunctions.h"
#include "GameStatusSpecific/SETTING/HelpingPlots.h"
#include "GameStatusSpecific/MENU/Menu.h"
#include "GameStatusSpecific/GAMEOVER/gameover.h"
#include "GameStatusSpecific/WINNING/winning.h"
#include "GameStatusSpecific/Button.h"
#include "Storage/Data.h"


/**A menüt frissítő függvény
*/
void updMENU(Satellite *sat, Menu *menu, Data *data, Button *toMenu, enum gameStatus *gameStatus, SDL_Event ev);

/**A menüt megrajzoló függvény
*/
void drwMENU(SDL_Surface *screen, Menu menu, Data data, TTF_Font *smallfont, TTF_Font *bigfont, Button *toMenu);


/**A gameover képernyőt frissítő függvény
*/
void updGAMEOVER(Satellite *sat, SDL_Event ev, enum gameStatus *gameStatus, GameOverScreen *gameOverScreen, Button *toMenu);

/**A gemover képernyőt megrajzoló függvény
*/
void drwGAMEOVER(SDL_Surface *screen, Button *toMenu, TTF_Font *smallfont, TTF_Font *bigfont, GameOverScreen gameOverScreen);

/**A winning képernyőt frissítő függvény
*/
void updWINNING(Satellite *sat, SDL_Event ev, enum gameStatus *gameStatus, Button *toMenu, Data *data, Menu *menu, WinningScreen *winningScreen);

#endif //FUNC_UPD_AND_DRW_H
