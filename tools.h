#ifndef TOOLS_H
#define TOOLE_H

#include <stdbool.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>

#include "Physics/Vector.h"
/**A képernyőre ír ki szöveget
*@param *text A sztring
*@param midx A szöveg középpontjának x koordinátája
*@param midí A szöveg középpontjának y koordinátája
*@param *font A kiíráshoz felhasznált font.
*/
void print(SDL_Surface *screen, char *text, int midx, int midy, TTF_Font *font);

/**Arányszámításhoz használt függvény. Egy adott intervallumot megváltoztatunk és a num paraméter az új intervallumban arányosan helyezkedik el.
*@param num Az eredeti intervallumban lévő szám
*@param rangeInStart Az eredeti intervallum kezdete
*@param rangeInEnd Az eredeti intervallum vége
*@param rangeOutStart Az új intervallum kezdete
*@param rangeOutEnd Au új intervallum vége
*@return Az új intervallumban lévő szám, ami arányos a num helyzetéhez az eredeti intervallumon.
*/
float mapping(float num, float rangeInStart, float rangeInEnd, float rangeOutStart, float rangeOutEnd);

/**Két kör összeütközését vizsgálja.
*@param pos A kör középpontja
*@param rad A kör sugara
*@return true, ha éppen össze vannak ütközve, false, ha nem.
*/
bool circlesCollide(Vect pos1, float rad1, Vect pos2, float rad2);

/**Megszámolja, hogy hány darab szó van egy fájlban
*@param *fileName A fájlra mutató pointer, ami a fájl elejére kell, hogy mutasson.
*@param *word A keresett sztring
*@param rowMax Ennyi karaktert vizsgál meg soronként.
*@return A szavak száma a fájlban
*/
int calculate_words(char *fileName, char *word, int rowMax);

/**Átálítja a fájlra mutató pointert egy adott szó első előfordulási helyére
*@param *file Az átálítandó fájlra mutató pointer
*@param *word A keresett sztring
*@param rowMax Ennyi karaktert vizsgál meg soronként.
*/
void goto_word_in_file(FILE *file, char *word, int rowMax);


#endif // TOOLS_H
