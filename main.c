/**@mainpage
*A program grafikus megjelenítéshez az SDL 1.2 könyvtárat használja. A külső függvények mindegyikét ebből használom fel, kivétel egyet: tools.c/print()/TTF_TextSize(), amelyet az SDL 2-ből.
*A játék a pályákat egy Settings.txt nevű fájlból olvassa be. Ehhez a fájlhoz a program dinamikusan alkalmazkodik, így könnyen lehet új pályákat hozzáadni a játékhoz.
*Csak az eddigi mintát kell kiegészíteni, és a játék be fogja tudni olvasni.
*A mentett játék adatait a program a Save.txt-be írja. Ezt a fájlt létre is hozza, ha szükséges, de üresen hagyja, ha nem kattintunk a mentés gombra.
*Új játékot a legkönnyebben úgy lehet kezdeni, hogy kitöröljük a Save.txt-t.
*FONTOS! A programban használt betűtípust a Constants.h-ban definiáltam, és ezen lehet, hogy állítani kell, hogy másik gépen is működjön.
*Linkelt listából csak egy van a programban, és az a menüben lévő szintek sorozata. (LevelBox.h)
*/

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <SDL_ttf.h>
#include <time.h>
#include <stdlib.h>


#include "Constants.h"
#include "GameStatusSpecific/GameStatus.h"
#include "GameStatusSpecific/GameStatusChangingFunctions.h"
#include "GameStatusSpecific/SETTING/HelpingPlots.h"
#include "GameStatusSpecific/MENU/Menu.h"
#include "tools.h"
#include "GameStatusSpecific/GAMEOVER/gameover.h"
#include "GameStatusSpecific/WINNING/winning.h"
#include "Storage/Data.h"
#include "FuncUpdAndDrw.h"


Uint32 time_func(Uint32 sec, void *pointer);

int game() {
//  ---------------------------------------------
//  SDL INICIALIZÁLÁS
//  ---------------------------------------------
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

//  ---------------------------------------------
//  INICIALIZÁLÁSA A JÁTÉKBAN HASZNÁLT ÉRTÉKEKNEK
//  ---------------------------------------------
    enum gameStatus gameStatus = MENU;

    Data data = data_read_in();
    Menu menu = menu_init(data);

    GameOverScreen gameOverScreen = gameOverScreen_init();
    WinningScreen winningScreen = winningScreen_init();

    Button toMenu = button_init(20, 20, 100, 40, STRMENU);

    Satellite sat = sat_init(10, HEIGHT/5, 10);

    HelpingPlots plots = helplt_init();

//  ---------------------------------------------
//  JÁTÉK LOOP
//  ---------------------------------------------
    while (gameStatus != QUITTING){
        SDL_WaitEvent(&ev);
        if (ev.type == SDL_QUIT) gameStatus = QUITTING;

        switch (gameStatus){
        case QUITTING:
            //while loop feltétel nem teljesül => kilépés
            break;
        case MENU:
            updMENU(&sat, &menu, &data, &toMenu, &gameStatus, ev);
            drwMENU(screen, menu, data, smallfont, bigfont, &toMenu);
            break;
        case RUNNING:
            updRUNNING(&sat, &gameStatus, &data, &toMenu, ev);
            drwRUNNING(screen, &sat, smallfont, &toMenu, ev);
            break;
        case GAMEOVER:
            updGAMEOVER(&sat, ev, &gameStatus, &gameOverScreen, &toMenu);
            drwGAMEOVER(screen, &toMenu, smallfont, bigfont, gameOverScreen);
            break;
        case WINNING:
            updWINNING(&sat, ev, &gameStatus, &toMenu, &data, &menu, &winningScreen);
            drwWINNING(screen, &toMenu, smallfont, bigfont, winningScreen);
            break;
        case SETTING:
            updSETTING(&sat, ev, &gameStatus, &toMenu, &plots);
            drwSETTING(screen, &sat, ev, tinyfont, smallfont, &toMenu, &plots);
            break;
        default:
            break;
        }
        SDL_Flip(screen);
    }//VÉGE: gameStatus != QUIT
//  ---------------------------------------------
//  TAKARÍTÁS
//  ---------------------------------------------
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
    int a = game();

    return a;
}

Uint32 time_func(Uint32 sec, void *pointer) {
    SDL_Event event;
    event.type = SDL_USEREVENT;
    SDL_PushEvent(&event);
    return sec;
}
