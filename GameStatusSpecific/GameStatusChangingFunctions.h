#ifndef GAME_STATUS_CHANGER_H
#define GAME_STATUS_CHANGER_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include "../Sprite/Satellite.h"
#include "MENU/Menu.h"

void game_status_from_SETTING_to_RUNNING(enum gameStatus *gameStatus, SDL_Event ev, Sat s);
void game_status_from_RUNNING_to_SETTING(enum gameStatus *gameStatus, SDL_Event ev, Sat s);
void geme_status_from_MENU_to_SETTING   (enum gameStatus *gameStatus, SDL_Event ev, Sat s, Menu menu);

/*private*/ float levelBox_getWidth(int numOf_levelBoxes);


#endif // GAME_STATUS_CHANGER_H
