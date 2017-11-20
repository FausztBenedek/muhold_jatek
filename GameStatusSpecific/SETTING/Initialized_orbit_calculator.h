#ifndef CALCULATE_ORBIT_H
#define CALCULATE_ORBIT_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include "../../Physics/Vector.h"
#include "../../Constants.h"
#include "../../Sprite/Satellite.h"

typedef struct initialOrbitCalculator helplt; //(Helping_plots)
typedef struct initialOrbitCalculator *Helplt; //(Helping_plots)
//Ha nagybetûs a deklaráció, akkor pointer lesz


struct initialOrbitCalculator {
    vect posarr[NUM_OF_HELPLT]; //(position array)
};

helplt helplt_init(Sat const s);//Hozzárendeli az összes posarr elemhez a megfelelő értéket
void helplt_upd(Helplt plots, Sat const satellite, SDL_Event ev);//Hozzárendeli az összes posarr elemhez a megfelelő értéket

void helplt_drw(SDL_Surface *screen, Helplt plots);

#endif // CALCULATE_ORBIT_H
