#ifndef TOOLS_H
#define TOOLE_H

#include <stdbool.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>

#include "Physics/Vector.h"

void print(SDL_Surface *screen, char *text, int midx, int midy, TTF_Font *font);
float mapping(float num, float rangeInStart, float rangeInEnd, float rangeOutStart, float rangeOutEnd);
bool circlesCollide(Vect pos1, float rad1, Vect pos2, float rad2);
int calculate_words(char *fileName, char *word, int rowMax);
void goto_word_in_file(FILE *file, char* word, int rowMax);


#endif // TOOLS_H
