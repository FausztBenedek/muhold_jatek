#include "Gate.h"

#include "../Constants.h"

Gate gate_init(float upper, float lower){
    Gate Gate;
    Gate.upper = upper; Gate.lower = lower;
    return Gate;
}

void gate_drw(SDL_Surface *screen, Gate *gate){
    boxRGBA(screen,
            WIDTH - 10, gate->upper,
            WIDTH     , gate->lower,
            255, 0, 0, 255
            );
}
