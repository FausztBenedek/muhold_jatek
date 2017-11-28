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
