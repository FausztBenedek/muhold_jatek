#ifndef WALL_H
#define WALL_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <stdbool.h>

#include "../../Physics/Vector.h"

///@defgroup wall Falak
///@{


typedef struct Wall{
    float x;
    float y;
    float w;///<Szélesség
    float h;///<Magasság
}Wall;

Wall wall_init(float x, float y, float w, float h);

void wall_drw(SDL_Surface *screen, Wall * wall);

bool wall_hover(Wall * const wall, SDL_Event ev);

/**Megvizsgálja, hogy melyik egy adott falnak a legközelebbi pontja egy körhöz.
*@return Visszaadja a legközelebbi pontot a kör közepéhez.
*/
Vect wall_closestPointToCircle(Wall *w, Vect circle_center);

///@}
#endif //WALL_H
