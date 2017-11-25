#ifndef CONST_H
#define CONST_H

///@defgroup constants Konstansok
///@{

///@defgroup stringConstants Sztringek
///@{
//Fájlban felismert kifelyezések:
    /**@defgroup fileStrings Fájlban felismert kifelyezések
    *@{
    */

///A szinteket beállító fájl neve
#define SETTINGS "Settings.txt"

///A fájl vége
#define FILE_END "VEGE_Beallitasok"

///Egy szint információi így kezdődnek: pl.: "2.Szint"
#define X_LEVEL "%d.Szint"

///A szintek számát a következő sztring előfordulásának megszámolásával határozza meg a program.
#define LEVEL_IDENTIFIER "Szint"

///A falakhoz tartozó információhalmaz kezdete
#define WALL_BEGIN "KEZD_Falak"

///A falakhoz tartozó információhalmaz vége
#define WALL_END "VEGE_Falak"

///A kapuhoz tartozó információ kezdete
#define GATE_BEGIN "KEZD_Kapu"

///A kapuhoz tartozó információ vége
#define GATE_END "VEGE_Kapu"
    ///@}


//Egyéb sztringek
    ///@defgroup font A betűtípus elérési útvonala
    /**@ingroup font
*A betűtípus elérési útvonala
*/
#define FONT_LOCATION "/usr/share/fonts/truetype/freefont/FreeSans.ttf"//ENNEK A KARAKTERTÍPUSNAK A SZÉLESSÉGE = MAGASSÁGA/4

//Gomb feliratok
    ///@defgroup buttonSubscription A gombok feliratai
    ///@{
#define STRMENU "Menü"
#define STRNEWGAME "Újra"
#define STRNEXTLEVEL "Következő pálya"
#define DEL_PLANET "Törlés"
    ///@}
///@}


///@defgroup wholeNums Egész számok
///@{
    ///@defgroup screen Képernyő
    ///@{
//Képernyő
enum {
    WIDTH = 1000,
    HEIGHT = 500
};
    ///@}

    ///@defgroup planetConstants Bolygók
    ///@{
//Bolygó
enum {
    ///Maximális elérhető vonzóerő
    PLN_MAX_STRENGTH = 60,
    ///Minimális elérhető vonzóerő
    PLN_MIN_STRENGTH = 15,
    ///A vonzóerőt változtató gombok ennyivel változtatják az értéket
    PLN_STRENGTH_STEP = 3,
    ///A kezdeti vonzóereje egy bolygónak
    PLN_INIT_STRENGTH = 30
};
    ///@}

    ///@defgroup fontSizeConstatns Betűk mérete
    ///@{
enum {
    BIG_FONT_SIZE = 32,
    SMALL_FONT_SIZE = 20,
    TINY_FONT_SIZE = 16,
};
    ///@}

    ///@defgroup menuConstants Menüben használt konstansok
    ///@{

enum {
    ///A szintek sorozatának szélei
    MENU_LEVEL_LIST_BORDER = 50,
    ///A kihagyott köz egyes szintek között
    MENU_SPACE_BETWEEN_LEVELS = 30,
    ///A gombok magassága
    MENU_LEVEL_HEIGHT = 75,
    ///A gombok y koordinátája
    MENU_LEVEL_LIST_UPPER_LINE = HEIGHT/2,
};
    ///@}

    ///@defgroup elseConstats Egyéb konstansok
    ///@{
enum {
    ///Az műhold eredő erejének a kiszámításához kell
    SAT_DIV = 1,
    ///A segítő pontok száma
    NUM_OF_HELPLT = 100,//A segítő pontok száma (number of helping plots)
    ///A segítő pontok egymástól vett távolsága
    HELPLT_MISS = 10,
    ///A kezdeti sebességvektor x komponense (y = 0)
    VELOCITY_INIT_X = 2,
    ///A kapu ekkora távolságból érzékeli a műholdat
    SAT_Y_DISTANCE_FROM_GATE_TO_WIN = 3,
    ///Egy sor olvasásakor ennyi karaktert vizsgálunk meg a fájlban
    MAX_ROW_LENGTH_IN_FILE = 40
};
    ///@}

///@}
///@}


#endif // CONST_H
