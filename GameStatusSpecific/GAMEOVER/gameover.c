#include "gameover.h"

#include "../../Constants.h"

GameOverScreen gameOverScreen_init(){
    GameOverScreen this;
    int buttonWidth = (WIDTH - MENU_LEVEL_LIST_BORDER * 2 - MENU_SPACE_BETWEEN_LEVELS) / 2;
    this.toMenu = button_init(MENU_LEVEL_LIST_BORDER, MENU_LEVEL_LIST_UPPER_LINE, buttonWidth, MENU_LEVEL_HEIGHT, STRMENU);

    this.newGame = button_init(MENU_LEVEL_LIST_BORDER + buttonWidth + MENU_SPACE_BETWEEN_LEVELS,
                               this.toMenu.y, this.toMenu.w, this.toMenu.h, STRNEWGAME);

    return this;
}

void gameOverScreen_drw(SDL_Surface *screen, GameOverScreen this, TTF_Font *font){
    button_drw(screen, &this.toMenu, font);

    button_drw(screen, &this.newGame, font);
}

void gameOverScreen_upd(GameOverScreen *this, SDL_Event ev){
    button_upd(&this->newGame, ev);
    button_upd(&this->toMenu, ev);
}

void gameOverScreen_cleanup(GameOverScreen *this){
    button_cleanup(&this->newGame);
    button_cleanup(&this->toMenu);
}

