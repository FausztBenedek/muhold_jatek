#include "GameStatusChangingFunctions.h"

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../Constants.h"
#include "../Sprite/Satellite.h"
#include "MENU/LevelBox.h"
#include "../tools.h"

/*private*/void open_level(int level, Sat sat);
/*private*/bool sat_touched_gate(Sat s);

/*private*/void sat_and_pln_collide (enum gameStatus *gameStatus, Sat s);
/*private*/void sat_and_astr_collide(enum gameStatus *gameStatus, Sat s);
/*private*/void sat_and_wall_collide(enum gameStatus *gameStatus, Sat s);
/*private*/void pln_and_astr_collide(enum gameStatus *gameStatus, Sat s);

void game_status_from_SETTING_to_RUNNING(enum gameStatus *gameStatus, SDL_Event ev, Sat s){
    if ((ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_SPACE) ||
        (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button  == SDL_BUTTON_RIGHT)
        ){
        sat_resetMotion(s);
        s->vel = vect_init(VELOCITY_INIT_X, 0);
        *gameStatus = RUNNING;
    }
}

void game_status_from_RUNNING_to_SETTING(enum gameStatus *gameStatus, SDL_Event ev, Sat s, Data *data){
    if (ev.type == SDL_MOUSEBUTTONDOWN || (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_SPACE)){
        *gameStatus = SETTING;
        sat_resetMotion(s);
        data->attempts[data->activeLevel]++;
        printf("ActiveLevel = %d\tAttempts = %d\n", data->activeLevel, data->attempts[data->activeLevel]);
    }
}
void game_status_from_MENU_to_SETTING(enum gameStatus *gameStatus, SDL_Event ev, Sat s, Menu menu, Data *data){
    if (ev.type == SDL_MOUSEBUTTONDOWN){
        LevelBox iter;
        int i;
        for (i = 0, iter = menu->levelarr; i < menu->numOf_levels; i++, iter = iter->next){
            if (iter->button.clicked){
                open_level(iter->index, s);
                data->activeLevel = iter->index;
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
            sat_resetInitialState(s);
        }

        if (gameOverScreen.newGame.clicked){
            *gameStatus = SETTING;
            sat_resetMotion(s);
        }
    }
}


/*private*/void open_level(int level, Sat sat){
    FILE *settings;
    settings = fopen(SETTINGS, "r");
    if (settings == NULL) return;

    sat_wall_init(sat, level, settings);
    fseek(settings, 0, SEEK_SET);

    sat_gate_init(sat, level, settings);

    fclose(settings);

}


void game_status_from_RUNNING_to_WINNING(enum gameStatus *gameStatus, Sat s){
    if (sat_touched_gate(s)){
        sat_resetMotion(s);
        *gameStatus = WINNING;
    }
}
/*private*/bool sat_touched_gate(Sat s){
    //              nagyon közel van a jobb szélhez
    return s->pos.x >= WIDTH - s->rad - SAT_Y_DISTANCE_FROM_GATE_TO_WIN
    //  és      y irányban is jó helyen
        && (s->pos.y <= s->gate.lower && s->pos.y >= s->gate.upper);
}

void game_status_from_RUNNING_to_GAMEOVER(enum gameStatus *gameStatus, Sat s, Data *data) {
    sat_and_pln_collide (gameStatus, s);
    sat_and_wall_collide(gameStatus, s);
    if (*gameStatus == GAMEOVER){
        data->attempts[data->activeLevel]++;
        printf("ActiveLevel = %d\tAttempts = %d\n", data->activeLevel, data->attempts[data->activeLevel]);
    }
}
/*private*/void sat_and_pln_collide (enum gameStatus *gameStatus, Sat s){
    int i;
    for (i = 0; i < s->numOf_pln; i++){//Műhold & Bolygó
        if (circlesCollide(s->pos, s->rad, s->plnarr[i].pos, pln_getRad(&s->plnarr[i]))){
            *gameStatus = GAMEOVER;
            sat_resetMotion(s);
        }
    }
}
/*private*/void sat_and_wall_collide(enum gameStatus *gameStatus, Sat s){
    int i;
    for (i = 0; i < s->numOf_wall; i++){
      //float dist = a kör közepétől a négyzet legközelebb lévő pontjába mutató vektor hossza
        float dist = magnitudeOf(differenceOf(s->pos, wall_closestPointToCircle(&s->wallarr[i], s->pos)));
        if (dist < s->rad){
            *gameStatus = GAMEOVER;
            sat_resetMotion(s);
        }
    }
}

void game_status_from_WINNING_to_MENU_or_NEXTLEVEL(enum gameStatus *gameStatus, SDL_Event ev, Sat s, WinningScreen winningScreen){
    if (ev.type == SDL_MOUSEBUTTONDOWN){
        if (winningScreen.toMenu.clicked){
            *gameStatus = MENU;
            sat_resetInitialState(s);
        }

        if (winningScreen.nextLevel.clicked){

        }
    }
}

