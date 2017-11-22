#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <SDL_ttf.h>
#include <time.h>
#include <stdlib.h>


#include "Constants.h"
#include "GameStatusSpecific/GameStatus.h"
#include "GameStatusSpecific/GameStatusChangingFunctions.h"
#include "GameStatusSpecific/SETTING/Initialized_orbit_calculator.h"
#include "GameStatusSpecific/MENU/Menu.h"
#include "tools.h"
#include "GameStatusSpecific/GAMEOVER/gameover.h"
#include "GameStatusSpecific/WINNING/winning.h"
#include "Storage/Data.h"


Uint32 time_func(Uint32 sec, void *pointer);

int game() {
///  ---------------------------------------------
///  SDL INICIALIZÁLÁS
///  ---------------------------------------------
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    SDL_Surface *screen = SDL_SetVideoMode(WIDTH, HEIGHT, 0, SDL_ANYFORMAT);
    SDL_TimerID mainTime = SDL_AddTimer(10, time_func, NULL);
    SDL_Event ev;

    TTF_Init();
    TTF_Font *bigfont = TTF_OpenFont(FONT_LOCATION, BIG_FONT_SIZE);
    if (bigfont == NULL) return 1;

    TTF_Font *smallfont = TTF_OpenFont(FONT_LOCATION, SMALL_FONT_SIZE);
    if (smallfont == NULL) return 1;

    TTF_Font *tinyfont  = TTF_OpenFont(FONT_LOCATION, TINY_FONT_SIZE);
    if (tinyfont == NULL) return 1;

///  ---------------------------------------------
///  INICIALIZÁLÁSA A JÁTÉKBAN HASZNÁLT ÉRTÉKEKNEK
///  ---------------------------------------------
    enum gameStatus gameStatus = WINNING;

    int i;

    menu menu = menu_init();
    Data data = data_read_in(menu.numOf_levels);
    gameOverScreen gameOverScreen = gameOverScreen_init();
    WinningScreen winningScreen = winningScreen_init();


    sat sat = sat_init(10, HEIGHT/5, 10);

    helplt plots = helplt_init(&sat);//helping plots = helplt

///  ---------------------------------------------
///  JÁTÉK LOOP
///  ---------------------------------------------
    while (gameStatus != QUITTING){
    ///*****************************
    ///  MENÜ LOOP
    ///*****************************
        while (gameStatus == MENU){
            SDL_WaitEvent(&ev);
            if (ev.type == SDL_QUIT) gameStatus = QUITTING;

            ///......
            ///Update
            ///......
            menu_upd(&menu, ev);
            data_upd(&data, ev);
            game_status_from_MENU_to_SETTING(&gameStatus, ev, &sat, &menu, &data);

            ///......
            ///Draw
            ///......
            boxRGBA(screen, 0, 0, WIDTH, HEIGHT, 255,255,255,255);
            menu_drw(screen, menu, smallfont);
            data_drw(screen, data, smallfont);

            print(screen, "ISTEN HOZOTT!", WIDTH/2, HEIGHT/7, bigfont);
            print(screen, "Válassz egy szintet!",WIDTH/2, HEIGHT/7+BIG_FONT_SIZE+10, bigfont);

            SDL_Flip(screen);
        } //VÉGE: gameStatus == MENU

    ///*****************************
    ///  MEGY A MŰHOLD LOOP
    ///*****************************
        while (gameStatus == RUNNING){

            SDL_WaitEvent(&ev);
            game_status_from_RUNNING_to_SETTING(&gameStatus, ev, &sat, &data);
            game_status_from_RUNNING_to_WINNING(&gameStatus, &sat);

            switch (ev.type){
                case SDL_QUIT:
                    gameStatus = QUITTING;
                    break;

                case SDL_USEREVENT:
            ///......
            ///Draw
            ///......
                    //Háttér rajzolása
                    boxRGBA(screen, 0, 0, WIDTH, HEIGHT, 255, 255, 255, 255);

                    //Objektumok rajzolása
                    sat_drw(screen, &sat);
                    for (i = 0; i < sat.numOf_pln; i++)     pln_drw(screen, &sat.plnarr[i] );
                    for (i = 0; i < sat.numOf_wall; i++)    wall_drw(screen, &sat.wallarr[i]);

            ///......
            ///Update
            ///......
                    sat_RUNNING_upd(&sat);
                    game_status_from_RUNNING_to_GAMEOVER(&gameStatus, &sat, &data);
                    SDL_Flip(screen);
                    break;
                default: break;
            }
        } //VÉGE: gameStatus == RUNNING
    ///*****************************
    ///  GAMEOVER
    ///*****************************
        while (gameStatus == GAMEOVER){
            SDL_WaitEvent(&ev);

            if (ev.type == SDL_QUIT) gameStatus = QUITTING;

            ///......
            ///Update
            ///......

            gameOverScreen_upd(&gameOverScreen, ev);
            game_status_from_GAMEOVER_to_MENU_or_SETTING(&gameStatus, ev, &sat, gameOverScreen);

            ///......
            ///Draw
            ///......

            boxRGBA(screen, 0, 0, WIDTH, HEIGHT, 255, 255, 255, 255);
            gameOverScreen_drw(screen, gameOverScreen, smallfont);

            print(screen, "VESZTETTÉL", WIDTH/2, HEIGHT/7, bigfont);
            print(screen, "Próbáld újra!",WIDTH/2, HEIGHT/7 + BIG_FONT_SIZE + 10, bigfont);

            SDL_Flip(screen);
        }//VÉGE: gameStatus == GAMEOVER
    ///*****************************
    ///  WINNING
    ///*****************************
        while (gameStatus == WINNING){
            SDL_WaitEvent(&ev);
            if (ev.type == SDL_QUIT) gameStatus = QUITTING;

            ///......
            ///Update
            ///......

            winningScreen_upd(&winningScreen, ev);
            game_status_from_WINNING_to_MENU_or_NEXTLEVEL(&gameStatus, ev, &sat, winningScreen);

            ///......
            ///Draw
            ///......

            boxRGBA(screen, 0, 0, WIDTH, HEIGHT, 255, 255, 255, 255);
            winningScreen_drw(screen, winningScreen, smallfont);

            print(screen, "EZAZ!", WIDTH/2, HEIGHT/7, bigfont);
            print(screen, "Elérhető a következő pálya",WIDTH/2, HEIGHT/7 + BIG_FONT_SIZE + 10, bigfont);

            SDL_Flip(screen);
        }
    ///*****************************
    ///  BOLYGÓK BEÁLLÍTÁSA LOOP
    ///*****************************
        while (gameStatus == SETTING) {
            SDL_WaitEvent(&ev);
            game_status_from_SETTING_to_RUNNING(&gameStatus, ev, &sat);

            switch (ev.type) {
                case SDL_QUIT:
                    gameStatus = QUITTING;
                    break;
            ///......
            ///Update
            ///......
                case SDL_USEREVENT:
                    break;
            }
            sat_SETTINGS_upd(&sat, ev);
            for (i = 0; i < sat.numOf_pln; i++)    pln_upd(&sat.plnarr[i], ev);
            for (i = 0; i < sat.numOf_pln; i++)    plnMenu_upd(&sat.plnarr[i], ev);
            helplt_upd(&plots, &sat, ev);
            ///......
            ///Draw
            ///......
            //Háttér rajzolása
            boxRGBA(screen, 0, 0, WIDTH, HEIGHT, 255, 255, 255, 255);

            //Objektumok rajzolása
            helplt_drw(screen, &plots);
            sat_drw(screen, &sat);
            for (i = 0; i < sat.numOf_pln; i++)    pln_drw(    screen, &sat.plnarr[i]);
            for (i = 0; i < sat.numOf_wall; i++)   wall_drw(   screen, &sat.wallarr[i]);
            for (i = 0; i < sat.numOf_pln; i++)    plnMenu_drw(screen, &sat.plnarr[i], ev, tinyfont);

            SDL_Flip(screen);
        }//VÉGE: gameStatus == SETTING

    }//VÉGE: gameStatus != QUIT
///  ---------------------------------------------
///  TAKARÍTÁS
///  ---------------------------------------------
    menu_cleanup(&menu);
    data_cleanUp(&data);
    sat_game_cleanup(&sat);
    TTF_CloseFont(bigfont);
    TTF_CloseFont(smallfont);
    SDL_RemoveTimer(mainTime);
    SDL_Quit();
    return 0;
}

int main(int argc, char *argv[]) {
    #ifdef __WIN32__
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);
    #endif
    srand(time(NULL));
    game();

    return 0;
}

Uint32 time_func(Uint32 sec, void *pointer) {
    SDL_Event event;
    event.type = SDL_USEREVENT;
    SDL_PushEvent(&event);
    return sec;
}
