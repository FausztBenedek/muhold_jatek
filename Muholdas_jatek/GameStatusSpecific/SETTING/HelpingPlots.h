#ifndef HELPING_PLOTS_H
#define HELPING_PLOTS_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include "../../Physics/Vector.h"
#include "../../Constants.h"
#include "../../Sprite/Satellite.h"

///@defgroup helpingPlots Segítő pontok
///@{

/**A tervezés fázisban a pályát kirajzoló pontok tömbjét tárolja ez a struktúra.
*/
typedef struct HelpingPlots {
    Vect posarr[NUM_OF_HELPLT];///<A pontok tömbje
}HelpingPlots;

/**Inicializálja a tömböt (0, 0) értékkel.
*/
HelpingPlots helplt_init();

/**Kiszámolja a tömb minden elemének a pozícióját, egy lokális segéd-műholddal.
*@param sat Lemásolja a műhold értékeit, mert az úgy egyszerűbb, mint egy lokálisat inicializálni.
*/
void helplt_upd(HelpingPlots * plots, Satellite sat, SDL_Event ev);

/**Kirajzolja a pontokat a képernyőre.
*/
void helplt_drw(SDL_Surface *screen, HelpingPlots * plots);

///@}
#endif // CALCULATE_ORBIT_H
