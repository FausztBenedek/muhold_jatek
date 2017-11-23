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
    enum gameStatus gameStatus = MENU;

    int i;

    Data data = data_read_in();
    Menu menu = menu_init(data);

    GameOverScreen gameOverScreen = gameOverScreen_init();
    WinningScreen winningScreen = winningScreen_init();

    button toMenu = button_init(20, 20, 100, 40, STRMENU);

    Satellite sat = sat_init(10, HEIGHT/5, 10);

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
            menu_upd(&menu, ev, data);
            data_upd(&data, ev);
            game_status_from_MENU_to_SETTING(&gameStatus, ev, &sat, &menu, &data);
            game_status_button_toMenuButton_upd(&toMenu, ev, &sat, &gameStatus);



            ///......
            ///Draw
            ///......
            boxRGBA(screen, 0, 0, WIDTH, HEIGHT, 255,255,255,255);
            menu_drw(screen, menu, smallfont, data);
            data_drw(screen, data, smallfont);

            print(screen, "ISTEN HOZOTT!", WIDTH/2, HEIGHT/7, bigfont);
            print(screen, "Válassz egy szintet, és juttasd el a műholdat a kapuba!",WIDTH/2, HEIGHT/7+BIG_FONT_SIZE+10, bigfont);

            button_drw(screen, &toMenu, smallfont);

            SDL_Flip(screen);
        } //VÉGE: gameStatus == MENU

    ///*****************************
    ///  MEGY A MŰHOLD LOOP
    ///*****************************
        while (gameStatus == RUNNING){

            SDL_WaitEvent(&ev);
            game_status_from_RUNNING_to_SETTING(&gameStatus, ev, &sat, &data);
            game_status_from_RUNNING_to_WINNING(&gameStatus, &sat, &data);
            game_status_from_RUNNING_to_GAMEOVER(&gameStatus, &sat, &data);


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
                    for (i = 0; i < sat.numOf_wall; i++)    wall_drw(screen, &sat.wallarr[i]);
                    for (i = 0; i < sat.numOf_pln; i++)     pln_drw(screen, &sat.plnarr[i] );
                    button_drw(screen, &toMenu, smallfont);

            ///......
            ///Update
            ///......
                    sat_RUNNING_upd(&sat);
                    break;

                case SDL_MOUSEMOTION:
                    /*FALL THROUGH*/

                case SDL_MOUSEBUTTONDOWN:
                    game_status_button_toMenuButton_upd(&toMenu, ev, &sat, &gameStatus);
                    break;
                default: break;
            }

            SDL_Flip(screen);



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
            game_status_button_toMenuButton_upd(&toMenu, ev, &sat, &gameStatus);


            ///......
            ///Draw
            ///......

            boxRGBA(screen, 0, 0, WIDTH, HEIGHT, 255, 255, 255, 255);
            gameOverScreen_drw(screen, gameOverScreen, smallfont);
            button_drw(screen, &toMenu, smallfont);

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
            game_status_from_WINNING_to_MENU_or_NEXTLEVEL(&gameStatus, ev, &sat, winningScreen, &data, &menu);
            game_status_button_toMenuButton_upd(&toMenu, ev, &sat, &gameStatus);


            ///......
            ///Draw
            ///......

            boxRGBA(screen, 0, 0, WIDTH, HEIGHT, 255, 255, 255, 255);
            winningScreen_drw(screen, winningScreen, smallfont);
            button_drw(screen, &toMenu, smallfont);

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

            if (ev.type == SDL_QUIT) gameStatus = QUITTING;

            ///......
            ///Update
            ///......
            sat_SETTINGS_upd(&sat, ev);
            for (i = 0; i < sat.numOf_pln; i++)    pln_upd(&sat.plnarr[i], ev);
            for (i = 0; i < sat.numOf_pln; i++)    plnMenu_upd(&sat.plnarr[i], ev);
            helplt_upd(&plots, &sat, ev);
            game_status_button_toMenuButton_upd(&toMenu, ev, &sat, &gameStatus);

            ///......
            ///Draw
            ///......
            //Háttér rajzolása
            boxRGBA(screen, 0, 0, WIDTH, HEIGHT, 255, 255, 255, 255);

            //Objektumok rajzolása
            helplt_drw(screen, &plots);
            sat_drw(screen, &sat);
            for (i = 0; i < sat.numOf_wall; i++)   wall_drw(   screen, &sat.wallarr[i]);
            for (i = 0; i < sat.numOf_pln; i++)    pln_drw(    screen, &sat.plnarr[i]);
            for (i = 0; i < sat.numOf_pln; i++)    plnMenu_drw(screen, &sat.plnarr[i], ev, tinyfont);
            button_drw(screen, &toMenu, smallfont);

            SDL_Flip(screen);
        }//VÉGE: gameStatus == SETTING

    }//VÉGE: gameStatus != QUIT
///  ---------------------------------------------
///  TAKARÍTÁS
///  ---------------------------------------------
    menu_cleanup(&menu);
    winningScreen_cleanup(&winningScreen);
    gameOverScreen_cleanup(&gameOverScreen);
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
