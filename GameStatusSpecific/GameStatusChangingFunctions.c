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

static void open_level(int level, Satellite * Satellite);
static bool sat_touched_gate(Satellite * s);

static void sat_and_pln_collide (enum gameStatus *gameStatus, Satellite * s);
static void sat_and_wall_collide(enum gameStatus *gameStatus, Satellite * s);

void game_status_from_SETTING_to_RUNNING(enum gameStatus *gameStatus, SDL_Event ev, Satellite * s){
    if ((ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_SPACE) ||
        (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button  == SDL_BUTTON_RIGHT)
        ){
        sat_resetMotion(s);
        s->vel = vect_init(VELOCITY_INIT_X, 0);
        *gameStatus = RUNNING;
    }
}

void game_status_from_RUNNING_to_SETTING(enum gameStatus *gameStatus, SDL_Event ev, Satellite * s, Data *data){
    if (ev.type == SDL_MOUSEBUTTONDOWN || (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_SPACE)){
        *gameStatus = SETTING;
        sat_resetMotion(s);
        data->attempts[data->activeLevel]++;
    }
}
void game_status_from_MENU_to_SETTING(enum gameStatus *gameStatus, SDL_Event ev, Satellite * s, Menu * Menu, Data *data){
    if (ev.type == SDL_MOUSEBUTTONDOWN){
        LevelBox * iter;
        int i;
        for (i = 0, iter = Menu->levelarr; i < Menu->numOf_levels; i++, iter = iter->next){
            if (iter->button.clicked){
                open_level(iter->index, s);
                data_changeActiveLevel(data, iter->index);
                *gameStatus = SETTING;
                break;
            }
        }
    }
}
static void open_level(int level, Satellite * Satellite){
    FILE *settings;
    settings = fopen(SETTINGS, "r");
    if (settings == NULL) return;

    sat_wall_init(Satellite, level, settings);
    fseek(settings, 0, SEEK_SET);

    sat_gate_init(Satellite, level, settings);

    fclose(settings);
}


void game_status_from_GAMEOVER_to_MENU_or_SETTING(enum gameStatus *gameStatus, SDL_Event ev, Satellite * s, GameOverScreen gameOverScreen){
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




void game_status_from_RUNNING_to_WINNING(enum gameStatus *gameStatus, Satellite * s, Data *data){
    if (sat_touched_gate(s)){
        sat_resetMotion(s);
        *gameStatus = WINNING;
        data->solved[data->activeLevel] = true;
    }
}
static bool sat_touched_gate(Satellite * s){
    //              nagyon közel van a jobb szélhez
    return s->pos.x >= WIDTH - s->rad - SAT_Y_DISTANCE_FROM_GATE_TO_WIN
    //  és      y irányban is jó helyen
        && (s->pos.y <= s->gate.lower && s->pos.y >= s->gate.upper);
}

void game_status_from_RUNNING_to_GAMEOVER(enum gameStatus *gameStatus, Satellite * s, Data *data) {
    sat_and_pln_collide (gameStatus, s);
    sat_and_wall_collide(gameStatus, s);
    if (*gameStatus == GAMEOVER){
        data->attempts[data->activeLevel]++;
    }
}
static void sat_and_pln_collide (enum gameStatus *gameStatus, Satellite * s){
    int i;
    for (i = 0; i < s->numOf_pln; i++){//Műhold & Bolygó
        if (circlesCollide(s->pos, s->rad, s->plnarr[i].pos, pln_getRad(&s->plnarr[i]))){
            *gameStatus = GAMEOVER;
            sat_resetMotion(s);
        }
    }
}
static void sat_and_wall_collide(enum gameStatus *gameStatus, Satellite * s){
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

void game_status_from_WINNING_to_MENU_or_NEXTLEVEL(enum gameStatus *gameStatus, SDL_Event ev, Satellite * s,
                                                   WinningScreen winningScreen, Data *data, Menu * Menu){
    if (ev.type == SDL_MOUSEBUTTONDOWN){
        if (winningScreen.toMenu.clicked){
            *gameStatus = MENU;
            sat_resetInitialState(s);
        }

        if (winningScreen.nextLevel.clicked){
            LevelBox * iter;
            int i;
            for (i = 0, iter = Menu->levelarr; i < Menu->numOf_levels; i++, iter = iter->next){
                if (i == Menu->numOf_levels -1){//Ha az utolsó pályán nyertél és megnyomod a következő gombot, akkor irány a menü
                    *gameStatus = MENU;
                    sat_resetInitialState(s);
                }
                if (!data->solved[i]){//Amint megtalálta az első olyat, amelyik még nincs megoldva, akkor...
                    sat_resetInitialState(s);
                    open_level(i, s);
                    data_changeActiveLevel(data, i);
                    *gameStatus = SETTING;
                    break;
                }
            }
        }
    }
}

void game_status_button_toMenuButton_upd(Button b, SDL_Event ev, Satellite * s, enum gameStatus *gameStatus){
    button_upd(b, ev);
    if (b->clicked){
        *gameStatus = MENU;
        sat_resetInitialState(s);
    }
}

