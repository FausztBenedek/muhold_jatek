#ifndef HELPING_PLOTS_H
#define HELPING_PLOTS_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include "../../Physics/Vector.h"
#include "../../Constants.h"
#include "../../Sprite/Satellite.h"


///
typedef struct HelpingPlots {
    Vect posarr[NUM_OF_HELPLT];
}HelpingPlots;

HelpingPlots helplt_init();
void helplt_upd(HelpingPlots * plots, Satellite sat, SDL_Event ev);

void helplt_drw(SDL_Surface *screen, HelpingPlots * plots);

#endif // CALCULATE_ORBIT_H
