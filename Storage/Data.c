#ifndef DATA_H
#define DATA_H

#include "../GameStatusSpecific/Button.h"

/**A Data struktúra a játék adatainak tárolására alkalmas
*/
typedef struct Data{
    int attempts;///<A próbálkozások számát tárolja
    button
}Data;

/**Beolvassa a save.txt-ből az elmentett információkat.
*   A fájlt a függvény nyitja meg, és be is zárja.
*   Nincs paramétere, mert mindent a fájlból olvas.
*/
Data data_read_in();

#endif // DATA_H
