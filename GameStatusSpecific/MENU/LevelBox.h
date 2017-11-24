#ifndef LEVEL_BOX_H
#define LEVEL_BOX_H


#include "../Button.h"
#include "../../Storage/Data.h"
#include "../../Physics/Vector.h"

///@ingroup menuinfos
///@{

/**Az egyes szinteket képviselő gombok a menüben. (Láncolt lista)
*/
typedef struct LevelBox{
    int index;///<Egyéni azonosító

    Vect pos;///<Bal felső sarok
    float width;///<A levelBox-ok szélessége
    Button button;///<Az interaktív felület, vagyis maga a gomb

    struct LevelBox *next;///<Egyirányú láncolt listában helyezkednek el.

}LevelBox;


/**Ezzel a függvénnyel lehet hozzáadni a láncolta végéhez.
*@param index Az egyéni azonosítót inicializálja. Azért került a paraméterlistára, mert így nem kell static változót deklarálni.
*@param numOf_level A pozíció kiszámításához szükséges. Azt tárolja, hány szint van.
*/
LevelBox *levelBox_add(LevelBox *list, int index, int numOf_level); //Minden paraméterét a fájlból olvassa

/**Kirajzolja a szintet képviselő gombot:
*  1. Magát a gombot
*  2. A sikertelen próbálkozások számát kiírja
*  3. Áthúzza a gombot, ha nem elérhető
*@param numOf_level Szükség van a szintek számára a számításokhoz.
*@param data Ez alapján tudja, hogy melyik szintek vannak már lejesítve, és melyikeket kell áthúzni.
*/
void levelBox_drw(SDL_Surface *screen, LevelBox *box, TTF_Font *font, Data data);

/**A gombot frissíti.
*/
void levelBox_upd(LevelBox *box, SDL_Event ev);

/**Feltakarítja a láncolt listét és a gomb felirata által lefoglalt területet.
*/
void levelBox_cleanUp(LevelBox *list);

///@}

#endif // LEVEL_BOX_H
