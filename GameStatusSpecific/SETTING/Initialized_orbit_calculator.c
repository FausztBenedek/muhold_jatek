#include "Initialized_orbit_calculator.h"

#include "../../tools.h"
#include "../../Constants.h"

helplt helplt_init(Sat const satellite){
    helplt h; int i;
    for (i = 0; i < NUM_OF_HELPLT; i++) h.posarr[i] = vect_init(0, 0);
    return h;
}

void helplt_upd(Helplt plots, Sat const satellite, SDL_Event ev) {
    if (ev.type == SDL_MOUSEBUTTONDOWN || ev.type == SDL_MOUSEMOTION){
        sat s = *satellite;
        sat_resetMotion(&s);
        s.vel = vect_init(VELOCITY_INIT_X, 0);
        int i, j;
        for (i = 0; i < NUM_OF_HELPLT; i++){
            for (j = 0; j < HELPLT_MISS ; j++){//Csak egy számláló, kihagy HELPLT_MISS értéket
                sat_RUNNING_upd(&s);
            }
            plots->posarr[i] = s.pos;
        }
    }
}
void helplt_drw(SDL_Surface *screen, Helplt const plots) {
    int i;
    int alpha = 150;
    for (i = 0; i < NUM_OF_HELPLT; i++){
        filledCircleRGBA(screen,
                     plots->posarr[i].x, plots->posarr[i].y,
                     1,
                     100, 100, 100, alpha
                     );
        alpha = 150 - mapping(i, 0, NUM_OF_HELPLT, 0, 150);
    }
}
