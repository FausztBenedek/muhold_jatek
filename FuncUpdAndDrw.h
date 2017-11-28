#ifndef FUNC_UPD_AND_DRW_H
#define FUNC_UPD_AND_DRW_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>

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

/**A winning képernyőt megrajzoló függvény
*/
void drwWINNING(SDL_Surface *screen, Button *toMenu, TTF_Font *smallfont, TTF_Font *bigfont, WinningScreen winningScreen);

/**A beállítási játékállapotot frissítő függvény
*/
void updSETTING(Satellite *sat, SDL_Event ev, enum gameStatus *gameStatus, Button *toMenu, HelpingPlots *plots);

/**A beállítási játékállapotot megrajzoló függvény
*/
void drwSETTING(SDL_Surface *screen, Satellite *sat, SDL_Event ev, TTF_Font *tinyfont, TTF_Font *smallfont, Button *toMenu, HelpingPlots *plots);


#endif //FUNC_UPD_AND_DRW_H
