#include "FuncUpdAndDrw.h"

#include "Constants.h"
#include "tools.h"

void updMENU(Satellite *sat, Menu *menu, Data *data, Button *toMenu, enum gameStatus *gameStatus, SDL_Event ev){
    menu_upd(menu, ev, *data);
    data_upd(data, ev);
    game_status_from_MENU_to_SETTING(gameStatus, ev, sat, menu, data);
    game_status_button_toMenuButton_upd(toMenu, ev, sat, gameStatus);
}

void drwMENU(SDL_Surface *screen, Menu menu, Data data, TTF_Font *smallfont, TTF_Font *bigfont, Button *toMenu){
    boxRGBA(screen, 0, 0, WIDTH, HEIGHT, 255,255,255,255);
    menu_drw(screen, menu, smallfont, data);
    data_drw(screen, data, smallfont);
    print(screen, "Hello!", WIDTH/2, HEIGHT/7, bigfont);
    print(screen, "Válassz egy szintet, és juttasd el a műholdat a kapuba!",WIDTH/2, HEIGHT/7+BIG_FONT_SIZE+10, bigfont);
    button_drw(screen, toMenu, smallfont);
    SDL_Flip(screen);
}

void updGAMEOVER(Satellite *sat, SDL_Event ev, enum gameStatus *gameStatus, GameOverScreen *gameOverScreen, Button *toMenu){
    gameOverScreen_upd(gameOverScreen, ev);
    game_status_from_GAMEOVER_to_MENU_or_SETTING(gameStatus, ev, sat, *gameOverScreen);
    game_status_button_toMenuButton_upd(toMenu, ev, sat, gameStatus);
}

void drwGAMEOVER(SDL_Surface *screen, Button *toMenu, TTF_Font *smallfont, TTF_Font *bigfont, GameOverScreen gameOverScreen){
    boxRGBA(screen, 0, 0, WIDTH, HEIGHT, 255, 255, 255, 255);
    gameOverScreen_drw(screen, gameOverScreen, smallfont);
    button_drw(screen, toMenu, smallfont);
    print(screen, "VESZTETTÉL", WIDTH/2, HEIGHT/7, bigfont);
    print(screen, "Próbáld újra!",WIDTH/2, HEIGHT/7 + BIG_FONT_SIZE + 10, bigfont);
    SDL_Flip(screen);
}

void updWINNING(Satellite *sat, SDL_Event ev, enum gameStatus *gameStatus, Button *toMenu, Data *data, Menu *menu, WinningScreen *winningScreen){
    winningScreen_upd(winningScreen, ev);
    game_status_from_WINNING_to_MENU_or_NEXTLEVEL(gameStatus, ev, sat, *winningScreen, data, menu);
    game_status_button_toMenuButton_upd(toMenu, ev, sat, gameStatus);
}

void drwWINNING(SDL_Surface *screen, Button *toMenu, TTF_Font *smallfont, TTF_Font *bigfont, WinningScreen winningScreen){
    boxRGBA(screen, 0, 0, WIDTH, HEIGHT, 255, 255, 255, 255);
    winningScreen_drw(screen, winningScreen, smallfont);
    button_drw(screen, toMenu, smallfont);
    print(screen, "EZAZ!", WIDTH/2, HEIGHT/7, bigfont);
    print(screen, "Elérhető a következő pálya",WIDTH/2, HEIGHT/7 + BIG_FONT_SIZE + 10, bigfont);
    SDL_Flip(screen);
}

void updSETTING(Satellite *sat, SDL_Event ev, enum gameStatus *gameStatus, Button *toMenu, HelpingPlots *plots){
    int i;
    game_status_from_SETTING_to_RUNNING(gameStatus, ev, sat);
    sat_SETTINGS_upd(sat, ev);
    for (i = 0; i < sat->numOf_pln; i++)    pln_upd(&sat->plnarr[i], ev);
    for (i = 0; i < sat->numOf_pln; i++)    plnMenu_upd(&sat->plnarr[i], ev);
    helplt_upd(plots, *sat, ev);
    game_status_button_toMenuButton_upd(toMenu, ev, sat, gameStatus);
}
