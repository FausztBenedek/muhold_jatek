#ifndef LEVEL_BOX_H
#define LEVEL_BOX_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>

#include "../../Sprite/Obstacles/Asteroid.h"
#include "../../Sprite/Obstacles/Wall.h"
#include "../Button.h"
#include "../../Storage/Data.h"



typedef struct levelBox levelBox;
typedef struct levelBox *LevelBox;

struct levelBox{
    int index;

    vect pos;
    button button;

    Astr astrarr;
    int numOf_astr;

    Wall wallarr;
    int numOf_wall;

    struct levelBox *next;
};

/*private*/float levelBox_getWidth(int numOf_levelBoxes);


LevelBox levelBox_add(LevelBox list, int i, int numOf_levelBoxes); //Minden paraméterét a fájlból olvassa

void levelBox_drw(SDL_Surface *screen, LevelBox box, int numOf_levelBoxes, TTF_Font *font, Data data);

void levelBox_upd(LevelBox box, SDL_Event ev);

void levelBox_cleanUp(LevelBox list);

#endif // LEVEL_BOX_H
