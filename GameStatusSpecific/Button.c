#include "Button.h"

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <stdbool.h>


button button_init(float x, float y, float w, float h){
    button b;
    b.x = x;    b.y = y;    b.w = w;    b.h = h;
    b.hover = b.clicked = false;
    return b;
}

void button_upd(Button b, SDL_Event ev) {
    button_hover(b, ev);
    if (b->hover && ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT) {
        b->clicked = true;
    }
    else {
        b->clicked = false;
    }
}
void button_drw(SDL_Surface *screen, Button b){
    if (b->hover) {
        boxRGBA(screen, b->x, b->y, b->x + b->w, b->y + b->h,
               200, 200, 255, 255
                );
    }
    else {
        boxRGBA(screen, b->x, b->y, b->x + b->w, b->y + b->h,
                200, 200, 255, 100
                );
    }
    rectangleRGBA(screen, b->x, b->y, b->x + b->w, b->y + b->h, 0, 200, 0, 200);

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
