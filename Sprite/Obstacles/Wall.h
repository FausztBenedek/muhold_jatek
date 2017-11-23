#ifndef WALL_H
#define WALL_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <stdbool.h>

#include "../../Physics/Vector.h"


typedef struct Wall{
    float x;
    float y;
    float w;
    float h;
}Wall;

Wall wall_init(float x, float y, float w, float h);

void wall_drw(SDL_Surface *screen, Wall * wall);

bool wall_hover(Wall * const wall, SDL_Event ev);

Vect wall_closestPointToCircle(Wall * const w, Vect circle_center);//Visszaadja a legközelebbi pontot a kör közepéhez

#endif //WALL_H
