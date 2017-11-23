#include "Data.h"

#include <stdio.h>

#include "../Constants.h"

static void read_from_file(int *numOf_level, bool *solvedarr, int *attemptsarr);
static void data_saveButtonAction(Data data);


Data data_read_in(){
    Data this;
    this.numOf_level = calculate_words(SETTINGS, LEVEL_IDENTIFIER, 20);;
    this.activeLevel = -1;

    this.attempts = (int*) malloc(this.numOf_level * sizeof(int));
    this.solved  = (bool*) malloc(this.numOf_level * sizeof(bool));
    int check;
    read_from_file(&check, this.solved, this.attempts);
    if (this.numOf_level != check){//A fájl nem helyes
        int i;
        for (i = 0; i < this.numOf_level; i++){
            this.attempts[i] = 0;
            this.solved[i] = false;
        }
    }

    this.saveButton = button_init(WIDTH-100-20, 20, 100, 40, "Mentés");
    return this;
}
static void read_from_file(int *numOf_level, bool *solvedarr, int *attemptsarr){
    FILE *fp;
    fp = fopen("Save.txt", "rt");
    if (fp == NULL){//Csinálunk egy fájlt
        fp = fopen("Save.txt", "wt");
        fclose(fp);
        *numOf_level = -1;
    }
    int i, j;
    char checker[7];

    //fscanf meghívva, és visszatéréri értéke ellenőrizve felesleges deklaráció nélkül
    if (    0 == fscanf(fp, "Szintek szama:\t%d\n\n", numOf_level)  ){
        *numOf_level = -1;
        return;
    }

    for (i = 0; i < *numOf_level; i++){
        fscanf(fp, "%d. Szint:\n", &j);
        if (0 == fscanf(fp, "\tSikertelen probalkozasok szama:\t%d\n", &attemptsarr[i]))    attemptsarr[i] = 0;
        if (0 == fscanf(fp, "\tTeljesitett szint:\t%s", checker))                           strcpy(checker, "Nem");
        fscanf(fp, "\n");

        if (NULL != strstr(checker, "Igen"))    solvedarr[i] = true;
        else                        solvedarr[i] = false;

        if (i != j) {/*baj van*/}

    }
}



void data_upd(Data *this, SDL_Event ev){
    button_upd(&this->saveButton, ev);
    data_saveButtonAction(*this);
}

void data_changeActiveLevel(Data *this, int newActiveLevel){
    this->activeLevel = newActiveLevel;
}

void data_drw(SDL_Surface *screen, Data this, TTF_Font *font){
    button_drw(screen, &this.saveButton, font);
}

void data_save(Data data){
    FILE *fp;
    fp = fopen("Save.txt", "wt");

    int i;
    fprintf(fp, "Szintek szama:\t%d\n\n", data.numOf_level);
    for (i = 0; i < data.numOf_level; i++){
        fprintf(fp, "%d. Szint:\n", i);
        fprintf(fp, "\tSikertelen probalkozasok szama:\t%d\n", data.attempts[i]);
        fprintf(fp, "\tTeljesitett szint:\t%s", data.solved[i] ? "Igen\n" : "Nem\n");
        fprintf(fp, "\n");
    }
    fclose(fp);

}
static void data_saveButtonAction(Data data){
    if (data.saveButton.clicked){
        data_save(data);
    }
}

void data_cleanUp(Data *this){
    free(this->attempts);
    free(this->solved);
}

