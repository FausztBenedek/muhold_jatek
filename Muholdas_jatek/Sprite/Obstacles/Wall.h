#ifndef WALL_H
#define WALL_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <stdbool.h>

#include "../../Physics/Vector.h"

///@defgroup wall Falak
///@{

/**A fal struktúra az egyetlen akadály ebben a verzióban.
*/
typedef struct Wall{
    float x;
    float y;
    float w;///<Szélesség
    float h;///<Magasság
}Wall;

/**Inicializálja a falat (nem a fájlból, hanem a paraméterlistáról)
*/
Wall wall_init(float x, float y, float w, float h);

/**Kirajzolja a falat a képernyőre
*/
void wall_drw(SDL_Surface *screen, Wall * wall);

/**Megállapítja, hogy az egér a fal felett van-e.
*@return true, ha benne van az egér a falban és false, ha nem.
*/
bool wall_hover(Wall * const wall, SDL_Event ev);

/**Megvizsgálja, hogy melyik egy adott falnak a legközelebbi pontja egy körhöz.
*@return Visszaadja a legközelebbi pontot a kör közepéhez.
*/
Vect wall_closestPointToCircle(Wall *w, Vect circle_center);

///@}
#endif //WALL_H
