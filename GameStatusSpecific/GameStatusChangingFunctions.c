#include "GameStatusChangingFunctions.h"

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include "../Constants.h"
#include "../Sprite/Satellite.h"
#include "MENU/LevelBox.h"

/*private*/void open_level(int level, Sat sat);
/*private*/void open_level(int level, Sat sat);

void game_status_from_SETTING_to_RUNNING(enum gameStatus *gameStatus, SDL_Event ev, Sat s){
    if ((ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_SPACE) ||
        (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button  == SDL_BUTTON_RIGHT)
        ){
        sat_resetMotion(s);
        s->vel = vect_init(VELOCITY_INIT_X, 0);
        *gameStatus = RUNNING;
    }
}

void game_status_from_RUNNING_to_GAMEOVER(enum gameStatus *gameStatus, SDL_Event ev, Sat s){
    if (ev.type == SDL_MOUSEBUTTONDOWN || (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_SPACE)){
        *gameStatus = SETTING;
        sat_resetMotion(s);
    }
}
void game_status_from_MENU_to_SETTING(enum gameStatus *gameStatus, SDL_Event ev, Sat s, Menu menu){
    if (ev.type == SDL_MOUSEBUTTONDOWN){
        LevelBox iter;
        int i;
        for (i = 0, iter = menu->levelarr; i < menu->numOf_levels; i++, iter = iter->next){
            if (iter->button.clicked){
                open_level(iter->index, s);
                *gameStatus = SETTING;
                break;
            }
        }
    }
}

void game_status_from_GAMEOVER_to_MENU_or_SETTING(enum gameStatus *gameStatus, SDL_Event ev, Sat s, gameOverScreen gameOverScreen){
    if (ev.type == SDL_MOUSEBUTTONDOWN){
        if (gameOverScreen.toMenu.clicked){
            *gameStatus = MENU;
        }

        if (gameOverScreen.newGame.clicked){
            *gameStatus = SETTING;
            sat_resetMotion(s);
        }
    }
}


/*private*/void open_level(int level, Sat sat){
    sat_wall_init(sat, level);
    //sat_astr_init(Sat s, level);
}



