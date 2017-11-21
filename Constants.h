#ifndef CONST_H
#define CONST_H
///Fájlban felismert kifelyezések:
#define SETTINGS "Settings.txt"
#define FILE_END "VEGE_Beallitasok"

#define X_LEVEL "%d.Szint"
#define LEVEL_IDENTIFIER "Szint"

#define WALL_BEGIN "KEZD_Falak:"
#define WALL_END "VEGE_Falak"
#define GATE_BEGIN "KEZD_Kapu"
#define GATE_END "VEGE_Kapu"

///Egyéb sztringek
#define FONT_LOCATION "/usr/share/fonts/truetype/freefont/FreeSans.ttf"///ENNEK A KARAKTERTÍPUSNAK A SZÉLESSÉGE = MAGASSÁGA/4

//Gomb feliratok
#define STRMENU "Menü"
#define STRNEWGAME "Újra"
#define DEL_PLANET "Törlés"

enum {
    WIDTH = 1000,
    HEIGHT = 500,
    PLN_MAX_STRENGTH = 60,
    PLN_MIN_STRENGTH = 15,
    PLN_STRENGTH_STEP= 3,
    SAT_DIV = 1, //Minél nagyobb annál gyengébb az erõ
    ASTR_DIV = 50,
    NUM_OF_HELPLT = 200,//A segítő pontok száma (number of helping plots)
    HELPLT_MISS = 5,
    VELOCITY_INIT_X = 2,

    BIG_FONT_SIZE = 32,
    SMALL_FONT_SIZE = 20,
    TINY_FONT_SIZE = 16,
    MAX_ROW_LENGTH_IN_FILE = 200
};

enum {
    MENU_LEVEL_LIST_BORDER = 100,
    MENU_SPACE_BETWEEN_LEVELS = 50,
    MENU_LEVEL_HEIGHT = 75,
    MENU_LEVEL_LIST_UPPER_LINE = HEIGHT/2,
};



#endif // CONST_H
