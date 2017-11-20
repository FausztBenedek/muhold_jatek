#include "gameover.h"

#include "../../Constants.h"

gameOverScreen gameOverScreen_init(){
    gameOverScreen this;
    int buttonWidth = (WIDTH - MENU_LEVEL_LIST_BORDER * 2 - MENU_SPACE_BETWEEN_LEVELS) / 2;
    this.toMenu = button_init(MENU_LEVEL_LIST_BORDER, MENU_LEVEL_LIST_UPPER_LINE, buttonWidth, MENU_LEVEL_HEIGHT);

    this.newGame = this.toMenu;
    this.newGame.x = MENU_LEVEL_LIST_BORDER + buttonWidth + MENU_SPACE_BETWEEN_LEVELS;
    return this;
}

void gameOverScreen_drw(SDL_Surface *screen, gameOverScreen this){
    button_drw(screen, &this.toMenu);
    button_drw(screen, &this.newGame);
}

void gameOverScreen_upd(gameOverScreen *this, SDL_Event ev){
    if (ev.type == SDL_MOUSEBUTTONDOWN || ev.type == SDL_MOUSEMOTION){
        button_upd(&this->newGame, ev);
        button_upd(&this->toMenu, ev);
    }
}
