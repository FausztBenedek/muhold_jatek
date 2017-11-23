#include "Planet.h"

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <stdbool.h>
#include <math.h>

#include "../Constants.h"

static void pln_reinit(Pln pln, vect pos);
static void calculateCoordinatesFor_but_strengthUp(Pln pln);
static void calculateCoordinatesFor_but_strengthDw(Pln pln);
static void calculateCoordinatesFor_but_del(Pln pln);

static void pln_drag(Pln pln, SDL_Event ev);


pln pln_init(float x, float y, int strength){

    ///Bolygó infók
    pln p;
    p.index = -1;
    p.strength = strength;

    p.removeable = true;
    ///Menü
    p.menuIsActive = p.pressing = false;

    pln_reinit(&p, vect_init(x, y));

    return p;
}
static void pln_reinit(Pln pln, vect pos){
    pln->pos = vect_init(pos.x, pos.y);
    ///Menü
    if (pln->pos.x >= WIDTH/2) pln->screenSideLeft = false;
    else pln->screenSideLeft = true;
    ///Gombok
    calculateCoordinatesFor_but_strengthUp(pln);
    calculateCoordinatesFor_but_strengthDw(pln);
    calculateCoordinatesFor_but_del(pln);
}
static void calculateCoordinatesFor_but_strengthUp(Pln pln){
    float x_coordinate, y_coordinate, width, height;
    width = height = sin(M_PI/4) * plnMenu_getRad(pln) / 3;
    y_coordinate = plnMenu_getPos(pln).y - plnMenu_getRad(pln) * sin(M_PI/4);
    if (pln->screenSideLeft)
        x_coordinate = plnMenu_getPos(pln).x + plnMenu_getRad(pln)*sin(M_PI/4) - width;
    else
        x_coordinate = plnMenu_getPos(pln).x - plnMenu_getRad(pln)*sin(M_PI/4) + 2 * width;
    pln->but_strengthUp = button_init(x_coordinate, y_coordinate, width, height, "+");

}
static void calculateCoordinatesFor_but_strengthDw(Pln pln){
    float x_coordinate, y_coordinate, width, height;
    width = height = sin(M_PI/4) * plnMenu_getRad(pln) / 3;
    y_coordinate = plnMenu_getPos(pln).y - plnMenu_getRad(pln) * sin(M_PI/4);
    if (pln->screenSideLeft)
        x_coordinate = plnMenu_getPos(pln).x + plnMenu_getRad(pln)*sin(M_PI/4) - 3 * width;
    else
        x_coordinate = plnMenu_getPos(pln).x - plnMenu_getRad(pln)*sin(M_PI/4);
    pln->but_strengthDw = button_init(x_coordinate, y_coordinate, width, height, "-");
}
static void calculateCoordinatesFor_but_del(Pln pln){
        float x_coordinate, y_coordinate, width, height;
        height = sin(M_PI/4) * plnMenu_getRad(pln) / 3;
        width =  sin(M_PI/4) * plnMenu_getRad(pln);
        y_coordinate = plnMenu_getPos(pln).y - height/2;
        if (pln->screenSideLeft)
            x_coordinate = plnMenu_getPos(pln).x;
        else
            x_coordinate = plnMenu_getPos(pln).x - width;
        pln->but_del = button_init(x_coordinate, y_coordinate, width, height, DEL_PLANET);

}

void pln_drw(SDL_Surface *screen, Pln const p) {
    if (p->removeable) {
        filledCircleRGBA(screen,
                         p->pos.x, p->pos.y, //Középpont
                         pln_getRad(p), //Szélesség
                         0, 200, 0, 255//RGBA
                         );
    }
    else {
        filledCircleRGBA(screen,
                         p->pos.x, p->pos.y, //Középpont
                         pln_getRad(p), //Szélesség
                         255, 200, 0, 255//RGBA
                         );
    }
}

void pln_upd(Pln pln, SDL_Event ev){
    if (ev.type == SDL_MOUSEBUTTONDOWN && pln_hover(pln, ev))
        pln->pressing = true;
    if (ev.type == SDL_MOUSEBUTTONUP)
        pln->pressing = false;

    pln_drag(pln, ev);

}

static void pln_drag(Pln pln, SDL_Event ev){
    if (pln->pressing && ev.type == SDL_MOUSEMOTION && pln->removeable){
        pln_reinit(pln, vect_init(ev.motion.x, ev.motion.y));
    }
}

bool pln_hover(Pln const p, SDL_Event ev) { //Egér benne van a bolygóban
    //(x-u)^2 + (y-v)^2 = r^2
    /*OLVASS!! ->              (x-u)^2                       +                     (y-v)^2                        =              r^2           ;*/
    return (ev.motion.x - p->pos.x)*(ev.motion.x - p->pos.x) + (ev.motion.y - p->pos.y)*(ev.motion.y - p->pos.y) <= pln_getRad(p) * pln_getRad(p);
}

float pln_getRad(Pln const p){
    return p->strength * 0.75;
}

///---------------------------------------------------
///Menüvel kapcsolatos függvények
///---------------------------------------------------

float plnMenu_getRad(Pln pln){
    return PLN_MAX_STRENGTH*2*0.75 + PLN_MIN_STRENGTH;
}
vect plnMenu_getPos(Pln pln){
    vect pos = pln->pos;
    if (pln->screenSideLeft) {//Ha a bolygó a képernyő közepétől jobbra van, akkor a menü középpontja tőle balra  helyezkedjen el
        pos.x += plnMenu_getRad(pln)/2;
    }
    else{//Ha a bolygó a képernyő közepétől balra  van, akkor a menü középpontja tőle jobbra helyezkedjen el
        pos.x -= plnMenu_getRad(pln)/2;
    }
    return pos;
}


void plnMenu_upd(Pln pln, SDL_Event ev){
    if (ev.type == SDL_MOUSEMOTION || (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT)){
        if (!plnMenu_hover(pln, ev)){
            pln->menuIsActive = false;
        }
        if (pln_hover(pln, ev)){
            pln->menuIsActive = true;
        }

        button_upd(&pln->but_strengthUp, ev);
        button_upd(&pln->but_strengthDw, ev);
        button_upd(&pln->but_del,        ev);

        button_strengthDw_action(pln);
        button_strengthUp_action(pln);
    }
}

void plnMenu_drw(SDL_Surface *screen, Pln const pln, SDL_Event ev, TTF_Font *font){
    if (pln->removeable && pln->menuIsActive){
        filledCircleRGBA(screen,
                         plnMenu_getPos(pln).x, plnMenu_getPos(pln).y,
                         plnMenu_getRad(pln),
                         0, 0, 0, 100
                         );
        button_drw(screen, &pln->but_strengthUp, font);
        button_drw(screen, &pln->but_strengthDw, font);
        button_drw(screen, &pln->but_del,        font);
    }
}

bool plnMenu_hover(Pln const pln, SDL_Event ev){//Az egér éppen benne van a bolygóban menüjében
    //(x-u)^2 + (y-v)^2 = r^2
    vect pos = plnMenu_getPos(pln);
    /*OLVASS!! ->            (x-u)^2                   +                   (y-v)^2                  */
    return (pos.x - ev.motion.x)*(pos.x - ev.motion.x) + (pos.y - ev.motion.y)*(pos.y - ev.motion.y)
            //=                        r^2
            <= plnMenu_getRad(pln) * plnMenu_getRad(pln);
}

///---------------------------------------------------
///Gombokkal kapcsolatos függvények
///---------------------------------------------------
void button_strengthUp_action(Pln pln){
    if (pln->but_strengthUp.clicked)
        if (pln->strength < PLN_MAX_STRENGTH)
            pln->strength += PLN_STRENGTH_STEP;
}
void button_strengthDw_action(Pln pln){
    if (pln->but_strengthDw.clicked)
        if (pln->strength > PLN_MIN_STRENGTH)
            pln->strength -= PLN_STRENGTH_STEP;
}





