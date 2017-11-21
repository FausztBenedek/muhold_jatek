#ifndef GAME_STATUS_CHANGER_H
#define GAME_STATUS_CHANGER_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include "../Sprite/Satellite.h"
#include "MENU/Menu.h"
#include "GAMEOVER/gameover.h"

void game_status_from_SETTING_to_RUNNING(enum gameStatus *gameStatus, SDL_Event ev, Sat s);
void game_status_from_RUNNING_to_SETTING(enum gameStatus *gameStatus, SDL_Event ev, Sat s);
void game_status_from_MENU_to_SETTING(enum gameStatus *gameStatus, SDL_Event ev, Sat s, Menu menu);
void game_status_from_GAMEOVER_to_MENU_or_SETTING(enum gameStatus *gameStatus, SDL_Event ev, Sat s, gameOverScreen gameOverScreen);
void game_status_from_RUNNING_to_WINNING(enum gameStatus *gameStatus, Sat s);
void game_status_from_RUNNING_to_GAMEOVER(enum gameStatus *gameStatus, Sat const s);

/*private*/ float levelBox_getWidth(int numOf_levelBoxes);


#endif // GAME_STATUS_CHANGER_H
