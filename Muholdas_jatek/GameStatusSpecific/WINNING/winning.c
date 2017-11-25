#include "winning.h"

#include "../../Constants.h"

WinningScreen winningScreen_init(){
    WinningScreen this;
    int buttonWidth = (WIDTH - MENU_LEVEL_LIST_BORDER *2 - MENU_SPACE_BETWEEN_LEVELS) / 2;
    this.toMenu = button_init(MENU_LEVEL_LIST_BORDER, MENU_LEVEL_LIST_UPPER_LINE, buttonWidth, MENU_LEVEL_HEIGHT, STRMENU);

    this.nextLevel = button_init(MENU_LEVEL_LIST_BORDER + buttonWidth + MENU_SPACE_BETWEEN_LEVELS,
                               this.toMenu.y, this.toMenu.w, this.toMenu.h, STRNEXTLEVEL);
    return this;
}

void winningScreen_drw(SDL_Surface *screen, WinningScreen this, TTF_Font *font){
    button_drw(screen, &this.toMenu, font);
    button_drw(screen, &this.nextLevel, font);
}

void winningScreen_upd(WinningScreen *this, SDL_Event ev){
    button_upd(&this->nextLevel, ev);
    button_upd(&this->toMenu, ev);
}

void winningScreen_cleanup(WinningScreen *this){
    button_cleanup(&this->toMenu);
    button_cleanup(&this->nextLevel);
}
