#ifndef LEVEL_BOX_H
#define LEVEL_BOX_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>

#include "../../Sprite/Obstacles/Asteroid.h"
#include "../../Sprite/Obstacles/Wall.h"
#include "../Button.h"
#include "../../Storage/Data.h"


/**Az egyes szinteket képviselő gombok a menüben
*/
typedef struct LevelBox{
    int index;///<Egyéni azonosító

    vect pos;///<Bal felső sarok
    button button;///<Az interaktív felület, vagyis maga a gomb

    struct LevelBox *next;
}LevelBox;


LevelBox * levelBox_add(LevelBox * list, int i, int numOf_levelBoxes); //Minden paraméterét a fájlból olvassa

void levelBox_drw(SDL_Surface *screen, LevelBox * box, int numOf_levelBoxes, TTF_Font *font, Data data);

void levelBox_upd(LevelBox * box, SDL_Event ev);

void levelBox_cleanUp(LevelBox * list);

#endif // LEVEL_BOX_H
