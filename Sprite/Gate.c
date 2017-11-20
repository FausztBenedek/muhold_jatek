#include "Gate.h"

#include "../Constants.h"

gate gate_init(float upper, float lower){
    gate gate;
    gate.upper = upper; gate.lower = lower;
    return gate;
}

void gate_drw(SDL_Surface *screen, Gate gate){
    boxRGBA(screen,
            WIDTH - 10, gate->upper,
            WIDTH     , gate->lower,
            255, 0, 0, 255
            );
}
