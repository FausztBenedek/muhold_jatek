#ifndef DATA_H
#define DATA_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>

#include "../GameStatusSpecific/Button.h"

/**A Data struktúra a játék adatainak tárolására alkalmas
*/
typedef struct Data{
    int *attempts;///<A próbálkozások számát tárolja egy tömbben, amely akkora, ahány szint van. Ezt a számot menu struktúrától kéri el.
    button saveButton;///<A mentéshez kell megnyomni
}Data;

/**Beolvassa a save.txt-ből az elmentett információkat.
*   A fájlt a függvény nyitja meg, és be is zárja.
*   Mindenképpen a menü inicializálása után kell meghívni
*   @param level A próbálkozások számát tároló tömb hosszát határozza meg. Annyinak kell lennie, ahány szint van.
*/
Data data_read_in(int level);

/**Mivel a data struktúrába a menüből, és más helyekről futás idő alatt gomb benyomására kell változtatni,
*ezért szükség van update-elő és rajzoló függvényre
*/
void data_upd(Data *this, SDL_Event ev);

/**Mivel a data struktúrába a menüből, és más helyekről futás idő alatt gomb benyomására kell változtatni,
*ezért szükség van update-elő és rajzoló függvényre
*/
void data_drw(SDL_Surface *screen, Data this, TTF_Font *font);


/**Az új fájlokat beírja a fájlba, amit megnyit, majd be is zár.
*   A Data struktúrához tartozó gomb funkciója is ez a függvény.
*/
void data_save();

///Felszabadítja a data struktúra által lefoglalt memóriát.
void data_cleanUp(Data *this);


#endif // DATA_H
