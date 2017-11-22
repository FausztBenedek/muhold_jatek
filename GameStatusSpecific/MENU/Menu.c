#include "Menu.h"

#include "../../tools.h"
#include "../../Constants.h"

menu menu_init(){//Minden paraméterét a fájlból olvassa
    menu theMenu;
    theMenu.numOf_levels = calculate_words(SETTINGS, LEVEL_IDENTIFIER, 20);
    theMenu.activeLevel = -1;
    theMenu.levelarr = NULL;

    int i;
    for (i = 0; i < theMenu.numOf_levels; i++){
        theMenu.levelarr = levelBox_add(theMenu.levelarr, i, theMenu.numOf_levels);
    }
    return theMenu;
}

void menu_LevelChangeReinit(menu *this, int newActiveLevel){
    this->activeLevel = newActiveLevel;
}



void menu_upd(Menu theMenu, SDL_Event ev){
    LevelBox iter;
    for (iter = theMenu->levelarr; iter != NULL; iter = iter->next){
        levelBox_upd(iter, ev);
    }

}

void menu_drw(SDL_Surface *screen, menu theMenu, TTF_Font *font){
    LevelBox iter;
    for (iter = theMenu.levelarr; iter != NULL; iter = iter->next){
        levelBox_drw(screen, iter, theMenu.numOf_levels, font);
    }
}

void menu_cleanup(Menu theMenu){
    levelBox_cleanUp(theMenu->levelarr);
}
