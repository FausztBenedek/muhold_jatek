#ifndef ASTEROID_H
#define ASTEROID_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include "../../Physics/Vector.h"


typedef struct asteroid_obsticle astr;
typedef struct asteroid_obsticle *Astr;

struct asteroid_obsticle{
	Vect pos;
	Vect vel;
	Vect force;
	float rad;
	Vect center;
};

astr astr_init(float centerX, float centerY, float posX, float posY, float rad, float velX, float velY);

void astr_drw(SDL_Surface *screen, Astr const a);

void astr_upd(Astr a);

#endif // ASTEROID_H
