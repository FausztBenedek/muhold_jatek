#include "Button.h"

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <string.h>

#include "../tools.h"


button button_init(float x, float y, float w, float h, char *subscription){
    button b;
    b.x = x;    b.y = y;    b.w = w;    b.h = h;
    b.hover = b.clicked = false;
    b.subscription = (char*) malloc ( (strlen(subscription) + 1) * sizeof(char) );
    strcpy(b.subscription, subscription);
    return b;
}

void button_upd(Button b, SDL_Event ev) {
    if (ev.type == SDL_MOUSEBUTTONDOWN || ev.type == SDL_MOUSEMOTION){

        button_hover(b, ev);
        if (b->hover && ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT) {
            b->clicked = true;
        }
        else {
            b->clicked = false;
        }
    }
}
void button_drw(SDL_Surface *screen, Button b, TTF_Font *font){
    if (b->clicked){
        boxRGBA(screen, b->x, b->y, b->x + b->w, b->y + b->h,
               170, 170, 170g, 255
                );
    }
    else if (b->hover) {
        boxRGBA(screen, b->x, b->y, b->x + b->w, b->y + b->h,
               230, 230, 230, 255
                );
    }
    else {
        boxRGBA(screen, b->x, b->y, b->x + b->w, b->y + b->h,
                200, 200, 200, 255
                );
    }
    rectangleRGBA(screen, b->x, b->y, b->x + b->w, b->y + b->h, 0, 100, 0, 255);

    print(screen, b->subscription, b->x + b->w/2, b->y + b->h/2, font);
}

bool button_hover(Button b, SDL_Event ev){
    //bal oldalától jobbra &&   jobb oldalától balra    &&     aljától fenntebb      &&  tetejétõl lentebb
    if (ev.motion.x > b->x && ev.motion.x < b->x + b->w && ev.motion.y < b->y + b->h && ev.motion.y > b->y) {
        b->hover = true;
    }
    else {
        b->hover = false;
    }
    return b->hover;
}

void button_cleanup(Button this){
    free(this->subscription);
}
