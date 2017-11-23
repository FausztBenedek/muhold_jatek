#include "Menu.h"

#include "../../tools.h"
#include "../../Constants.h"

Menu menu_init(Data data){//Minden paraméterét a fájlból olvassa
    Menu theMenu;
    theMenu.levelarr = NULL;

    int i;
    for (i = 0; i < data.numOf_level; i++){
        theMenu.levelarr = levelBox_add(theMenu.levelarr, i, data.numOf_level);
    }
    return theMenu;
}

void menu_upd(Menu * theMenu, SDL_Event ev, Data data){
    LevelBox * iter;
    for (iter = theMenu->levelarr; iter != NULL; iter = iter->next){
        if (iter->index == 0){//A 0. szintnek mindig aktívnak kell lennie
            levelBox_upd(iter, ev);
        }
        else if (data.solved[iter->index-1]){//A többinek csak akkor, ha az elötte lévő teljesítve van
            levelBox_upd(iter, ev);
        }
    }

}

void menu_drw(SDL_Surface *screen, Menu theMenu, TTF_Font *font, Data data){
    LevelBox * iter;
    for (iter = theMenu.levelarr; iter != NULL; iter = iter->next){
        levelBox_drw(screen, iter, data.numOf_level, font, data);
    }
}

void menu_cleanup(Menu * theMenu){
    levelBox_cleanUp(theMenu->levelarr);
}
