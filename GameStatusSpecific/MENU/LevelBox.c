#include "LevelBox.h"

#include <string.h>

#include "../../Physics/Vector.h"
#include "../../tools.h"
#include "../../Constants.h"

/*private*/ vect levelBox_getPos(levelBox * box, int numOf_levelBoxes){
    return vect_init(
            /*x value: */ mapping(box->index,
                                  0, numOf_levelBoxes - 1,
                                  0 + MENU_LEVEL_LIST_BORDER, WIDTH - MENU_LEVEL_LIST_BORDER - levelBox_getWidth(numOf_levelBoxes)
                                  ),
            /*y value: */ MENU_LEVEL_LIST_UPPER_LINE
                    );
}

/*private*/float levelBox_getWidth(int numOf_levelBoxes){
    //Szélesség  -        a lista margója     -         a lista elemei között lévő hely
    return (WIDTH - 2 * MENU_LEVEL_LIST_BORDER - (numOf_levelBoxes - 1) * MENU_SPACE_BETWEEN_LEVELS)/numOf_levelBoxes;
}

levelBox * levelBox_add(levelBox * list, int i, int numOf_levelBoxes){ //Minden paraméterét a fájlból olvassa

    //Új elem helyének lefoglalása
    levelBox * element;
    element = (levelBox *) malloc(sizeof(struct levelBox));

    //Új elem inicializálása
    element->next = NULL;
    element->index = i;
    element->pos = levelBox_getPos(element, numOf_levelBoxes);
    element->button = button_init(element->pos.x, element->pos.y, levelBox_getWidth(numOf_levelBoxes), MENU_LEVEL_HEIGHT, "");//A stringet manipulálni kell, nem bízom rá a button_init függvényre

    element->button.subscription = (char*) realloc(element->button.subscription, (strlen(X_LEVEL)+2) * sizeof(char));//+2, hogy biztosan legyen elég hely a több helyiértékkel jelölt szinteknek
    sprintf(element->button.subscription, X_LEVEL, i+1);

    element->astrarr = NULL;
    element->numOf_astr = 0;

    element->wallarr = NULL;
    element->numOf_wall = 0;



    //Új elem hozzáadása a listához
    if (list == NULL){
        list = element;
    }
    else{
        levelBox * iter;
        for (iter = list; iter->next != NULL; iter = iter->next);
        iter->next = element;
    }
    return list;
}



void levelBox_drw(SDL_Surface *screen, levelBox * box, int numOf_levels, TTF_Font *font, Data data){
    button_drw(screen, &box->button, font);

    char str[14+1];

    sprintf(str, "%d sikertelen", data.attempts[box->index]);

    print(screen, str, box->pos.x + levelBox_getWidth(numOf_levels)/2, box->pos.y + MENU_LEVEL_HEIGHT*1.5, font);

    if (box->index != 0 && !data.solved[box->index-1]){//Számít a sorrend, mert ha index = 0 akkor a tömb -1-dik elemére hivatkozunk
        lineRGBA(screen,
                 box->pos.x, box->pos.y,
                 box->pos.x + levelBox_getWidth(numOf_levels), box->pos.y + MENU_LEVEL_HEIGHT,
                 0, 100, 0, 255
                );
        lineRGBA(screen,
                 box->pos.x+ levelBox_getWidth(numOf_levels), box->pos.y,
                 box->pos.x, box->pos.y + MENU_LEVEL_HEIGHT,
                 0, 100, 0, 255
                );
    }
}




void levelBox_upd(levelBox * box, SDL_Event ev){
    button_upd(&box->button, ev);
}


void levelBox_cleanUp(levelBox * list){
    while (list != NULL){
        levelBox * temp = list->next;
        free(list);
        list = temp;
    }
}

