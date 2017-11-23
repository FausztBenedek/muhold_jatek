#ifndef GATE_H
#define GATE_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

/**A jobb oldalon látható kapu vagy célvonal adatait tároló struktúra
*/
typedef struct Gate{
    float upper;///<Felső határ y koordinátája
    float lower;///<Alsó határ y koordinátája
}Gate;

Gate gate_init(float upper, float lower);

void gate_drw(SDL_Surface *screen, Gate * gate);

#endif // GATE_H
