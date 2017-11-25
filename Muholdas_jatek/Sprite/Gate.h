#ifndef GATE_H
#define GATE_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

///@defgroup gate Kapu
///@{

/**A jobb oldalon látható kapu vagy célvonal adatait tároló struktúra
*A sikeres átjutást tesztelő függvény nem ebben a modulban, hanem a gameStatusChangingFunctions modulban található.
*/
typedef struct Gate{
    float upper;///<Felső határ y koordinátája
    float lower;///<Alsó határ y koordinátája
}Gate;

/**Inicializálja a Gate struktúrában lévő értékeket
*/
Gate gate_init(float upper, float lower);

/**Kirajzolja a képernyőre a célvonalat
*/
void gate_drw(SDL_Surface *screen, Gate *gate);

///@}

#endif // GATE_H
