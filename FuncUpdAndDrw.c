#include "FuncUpdAndDrw.h"

void updMENU(Satellite *sat, Menu *menu, Data *data, Button *toMenu, enum gameStatus *gameStatus, SDL_Event ev){
    menu_upd(menu, ev, *data);
    data_upd(data, ev);
    game_status_from_MENU_to_SETTING(gameStatus, ev, sat, menu, data);
    game_status_button_toMenuButton_upd(toMenu, ev, sat, gameStatus);
}
