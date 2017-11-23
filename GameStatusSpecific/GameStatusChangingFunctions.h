#ifndef GAME_STATUS_CHANGER_H
#define GAME_STATUS_CHANGER_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include "../Sprite/Satellite.h"
#include "MENU/Menu.h"
#include "GAMEOVER/gameover.h"
#include "../Storage/Data.h"
#include "WINNING/winning.h"



void game_status_from_SETTING_to_RUNNING(enum gameStatus *gameStatus, SDL_Event ev, Satellite * s);
/**
*@param &data a data struktúrában tárolt próbálkozások száma nő.
*/
void game_status_from_RUNNING_to_SETTING(enum gameStatus *gameStatus, SDL_Event ev, Satellite * s, Data *data);

/**
*@param *data Beállítja az aktuális szintet
*/
void game_status_from_MENU_to_SETTING(enum gameStatus *gameStatus, SDL_Event ev, Satellite * s, Menu menu, Data *data);
/**
*@param s Viszzállítja az akadályokra mutató pointereket NULL-ba, gyakorlatilag újrainicializálja a műholdat
*/
void game_status_from_GAMEOVER_to_MENU_or_SETTING(enum gameStatus *gameStatus, SDL_Event ev, Satellite * s, GameOverScreen gameOverScreen);
void game_status_from_RUNNING_to_WINNING(enum gameStatus *gameStatus, Satellite * s, Data *data);
/**
*@param *data a data struktúrában tárolt próbálkozások száma nő.
*/
void game_status_from_RUNNING_to_GAMEOVER(enum gameStatus *gameStatus, Satellite * const s, Data *data);

/**A WINNING állapotból lép továb a képernyőn lévő két gomb lenyomásától függően.
*@param winningScreen Ez a függvény kezeli a winningScreen struktúra két gombját.
*@param s Viszzállítja az akadályokra mutató pointereket NULL-ba, gyakorlatilag újrainicializálja a műholdat
*@param *gameStatus Ez a függvény megváltoztatja az állapotot a feltételek kiértékelését követően
*@param ev Az állapotváltás függ az aktuális event-től
*/
void game_status_from_WINNING_to_MENU_or_NEXTLEVEL(enum gameStatus *gameStatus, SDL_Event ev, Satellite * s,
                                                   WinningScreen winningScreen, Data *data, Menu menu);

/**Az állandóan látható menü gomb frissítéséért és a menübe lépésért felelős
*/
void game_status_button_toMenuButton_upd(Button b, SDL_Event ev, Satellite * s, enum gameStatus *gameStatus);


/*private*/ float levelBox_getWidth(int numOf_levelBoxes);


#endif // GAME_STATUS_CHANGER_H
