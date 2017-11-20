#ifndef GATE_H
#define GATE_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

typedef struct gate gate;
typedef struct gate *Gate;

struct gate{
    float upper, lower;
};

gate gate_init(float upper, float lower);

void gate_drw(SDL_Surface *screen, Gate gate);

#endif // GATE_H
