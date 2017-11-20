#ifndef WALL_H
#define WALL_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <stdbool.h>

#include "../../Physics/Vector.h"

typedef struct Wall wall;
typedef struct Wall *Wall;

struct Wall{
    float x, y, w, h; //x koordin�ta, y koordin�ta, sz�less�g, magass�g
};

wall wall_init(float x, float y, float w, float h);

void wall_drw(SDL_Surface *screen, Wall wall);

bool wall_hover(Wall const wall, SDL_Event ev);

vect wall_closestPointToCircle(Wall const w, vect circle_center);//Visszaadja a legk�zelebbi pontot a k�r k�zep�hez

#endif //WALL_H
