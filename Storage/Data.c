#include "Data.h"

#include "../Constants.h"

Data data_read_in(int level){
    Data this;
    this.activeLevel = -1;


    ///!!!!!!!!Feltétel ellenőrzés: Ugyanannyi level van-e mint legutóbb?
    this.attempts = (int*) malloc(level * sizeof(int));
    this.solved  = (bool*) malloc(level * sizeof(bool));
    int i;
    for (i = 0; i < level; i++){
        this.attempts[i] = 0;
        this.solved[i] = false;
    }

    this.saveButton = button_init(WIDTH-100-20, 20, 100, 40, "Mentés");
    return this;
}

void data_upd(Data *this, SDL_Event ev){
    button_upd(&this->saveButton, ev);
}

void data_changeActiveLevel(Data *this, int newActiveLevel){
    this->activeLevel = newActiveLevel;
}

void data_drw(SDL_Surface *screen, Data this, TTF_Font *font){
    button_drw(screen, &this.saveButton, font);
}

void data_save(Data data){

}

void data_cleanUp(Data *this){
    free(this->attempts);
    free(this->solved);
}

