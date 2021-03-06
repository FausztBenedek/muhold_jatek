#include "LevelBox.h"

#include <string.h>

#include "../../Physics/Vector.h"
#include "../../tools.h"
#include "../../Constants.h"
static float levelBox_getWidth(int numOf_level){
    //Szélesség  -        a lista margója     -         a lista elemei között lévő hely
    return (WIDTH - 2 *MENU_LEVEL_LIST_BORDER - (numOf_level - 1) *MENU_SPACE_BETWEEN_LEVELS)/numOf_level;
}

static  Vect levelBox_getPos(LevelBox *box, int numOf_level){
    return vect_init(
            /*x value: */ mapping(box->index,
                                  0, numOf_level - 1,
                                  0 + MENU_LEVEL_LIST_BORDER, WIDTH - MENU_LEVEL_LIST_BORDER - levelBox_getWidth(numOf_level)
                                  ),
            /*y value: */ MENU_LEVEL_LIST_UPPER_LINE
                    );
}

LevelBox *levelBox_add(LevelBox *list, int i, int numOf_level){ //Minden paraméterét a fájlból olvassa

    //Új elem helyének lefoglalása
    LevelBox *element;
    element = (LevelBox *) malloc(sizeof(struct LevelBox));

    //Új elem inicializálása
    element->next = NULL;
    element->index = i;
    element->pos = levelBox_getPos(element, numOf_level);
    element->width = levelBox_getWidth(numOf_level);
                            //A stringet manipulálni kell, nem bízom rá a button_init függvényre
    element->button = button_init(element->pos.x, element->pos.y, element->width, MENU_LEVEL_HEIGHT, "");

    element->button.subscription = (char*) realloc(element->button.subscription, (strlen(X_LEVEL)+2) *sizeof(char));//+2, hogy biztosan legyen elég hely a több helyiértékkel jelölt szinteknek
    sprintf(element->button.subscription, X_LEVEL, i+1);

    //Új elem hozzáadása a listához
    if (list == NULL){
        list = element;
    }
    else{
        LevelBox *iter;
        for (iter = list; iter->next != NULL; iter = iter->next);
        iter->next = element;
    }
    return list;
}

void levelBox_drw(SDL_Surface *screen, LevelBox *box, TTF_Font *font, Data data){
    button_drw(screen, &box->button, font);

    char str[14+1];

    sprintf(str, "%d sikertelen", data.attempts[box->index]);

    print(screen, str, box->pos.x + box->width/2, box->pos.y + MENU_LEVEL_HEIGHT*1.5, font);

    if (box->index != 0 && !data.solved[box->index-1]){//Számít a sorrend, mert ha index = 0 akkor a tömb -1-dik elemére hivatkozunk
        lineRGBA(screen,
                 box->pos.x, box->pos.y,
                 box->pos.x + box->width, box->pos.y + MENU_LEVEL_HEIGHT,
                 0, 100, 0, 255
                );
        lineRGBA(screen,
                 box->pos.x+ box->width, box->pos.y,
                 box->pos.x, box->pos.y + MENU_LEVEL_HEIGHT,
                 0, 100, 0, 255
                );
    }
}




void levelBox_upd(LevelBox *box, SDL_Event ev){
    button_upd(&box->button, ev);
}


void levelBox_cleanUp(LevelBox *list){
    while (list != NULL){
        free(list->button.subscription);
        LevelBox *temp = list->next;
        free(list);
        list = temp;
    }
}

