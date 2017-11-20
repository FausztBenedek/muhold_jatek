#include "tools.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>
#include <string.h>

#include "Physics/Vector.h"

void print(SDL_Surface *screen, char *text, int midx, int midy, TTF_Font *font){
    int x, y, w, h;

    if (TTF_SizeText(font, text, &w, &h) != 0) return;

    x = midx - w/2;
    y = midy - h/2;

    SDL_Color textColor = {0, 0, 0};
    SDL_Surface *subscription = TTF_RenderUTF8_Solid(font, text, textColor);

    SDL_Rect place = {x, y, x + w, y + h};
    SDL_BlitSurface(subscription, NULL, screen, &place);
    SDL_FreeSurface(subscription);
}

float mapping(float num, float rangeInStart, float rangeInEnd, float rangeOutStart, float rangeOutEnd)
{
    //(num - rangeInStart)/(rangeInEnd - rangeInStart) <=> Ennyi százalékot megyünk elõre a num-ig*/
    //(solution - rangeOutStart)/(rangeOutEnd - rangeOutStart) <=> Ennyi százalékot megyünk elõre a megoldásig
    // A két egyenlet egyenlõ
    // solution =
    return       ((num - rangeInStart)*(rangeOutEnd - rangeOutStart))
           / //--------------------------------------------------------   <- törtvonal :)
                           (rangeInEnd - rangeInStart)
           /*And to the fraction*/+ rangeOutStart;
}

bool circlesCollide(vect pos1, float rad1, vect pos2, float rad2){
//    float dx = pos1.x - pos2.x; //mindegy, hogy negatív-e, mert négyzetre lesz emelve
//    float dy = pos1.y - pos2.y; //mindegy, hogy negatív-e, mert négyzetre lesz emelve
//    float dist = sqrt(dx*dx + dy*dy);
//
//    return dist < rad1 + rad2;

//    Összegezve: (CTRL + C)-vel
    return sqrt( (pos1.x - pos2.x)*(pos1.x - pos2.x)     +   (pos1.y - pos2.y)*(pos1.y - pos2.y) )    <    rad1 + rad2;
}

int calculate_words(char *fileName, char *word, int rowMax){
    FILE *file;     char rowString[rowMax];     int howMany = 0;
    file = fopen(fileName, "r");
    if (file == NULL){
        return -1;
    }
    while (fgets(rowString, rowMax, file) != NULL){
        if (strstr(rowString, word)){
            howMany++;
        }
    }

    fclose(file);

    return howMany;
}

void goto_word_in_file(FILE *file, char* word, int rowMax){
    char string[rowMax];
    while(fgets(string, rowMax, file) != NULL  &&  strstr(string, word) == NULL);
}


