#ifndef DATA_H
#define DATA_H

#include "../GameStatusSpecific/Button.h"

/**A Data struktúra a játék adatainak tárolására alkalmas
*/
typedef struct Data{

    int numOf_level;///<A szintek számát tárolja

    int activeLevel;///<Az éppen aktuális szintet tároló változó. -1-el inicializálódik.
    int *attempts;///<A próbálkozások számát tárolja egy tömbben. A tömb akkora, ahány szint van.
    bool *solved;///<Minden szinthez hozzárendeljük, hogy megoldott-e vagy sem. Ha igen akkor a solved tömb megfelelő indexű tagja true értékű (pl.: solved[3] = true; <=> a 3. szint megoldva)
    Button saveButton;///<A mentéshez kell megnyomni
}Data;

/**Beolvassa a save.txt-ből az elmentett információkat.
*  A fájlt a függvény nyitja meg, és be is zárja.
*  Mindenképpen a menü inicializálása után kell meghívni
*/
Data data_read_in();


/**Beállítja az új aktuális szintet, amit a data struktúra tárol.
*/
void data_changeActiveLevel(Data *this, int newActiveLevel);


/**Mivel a data struktúrába a menüből, és más helyekről futás idő alatt gomb benyomására kell változtatni,
*ezért szükség van update-elő és rajzoló függvényre
*/
void data_upd(Data *this, SDL_Event ev);


/**Mivel a data struktúrába a menüből, és más helyekről futás idő alatt gomb benyomására kell változtatni,
*ezért szükség van update-elő és rajzoló függvényre
*/
void data_drw(SDL_Surface *screen, Data this, TTF_Font *font);


/**Az új fájlokat beírja a fájlba, amit megnyit, majd be is zár.
*  A Data struktúrához tartozó gomb funkciója is ez a függvény.
*/
void data_save(Data data);


///Felszabadítja a data struktúra által lefoglalt memóriát.
void data_cleanUp(Data *this);


#endif // DATA_H
