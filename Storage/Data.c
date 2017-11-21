#include "Data.h"

#include "../Constants.h"

Data data_read_in(){
    Data this;
    this.attempts = 0;
    this.saveButton = button_init(WIDTH-100-20, 20, 100, 40, "Mentés");
    return this;
}

void data_upd(Data *this, SDL_Event ev){
    button_upd(&this->saveButton, ev);
}

void data_drw(SDL_Surface *screen, Data this, TTF_Font *font){
    button_drw(screen, &this.saveButton, font);
}

void data_save(Data data){

}

