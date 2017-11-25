#include "Planet.h"

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <stdbool.h>
#include <math.h>

#include "../Constants.h"

static void pln_reinit(Pln *Pln, Vect pos);
static void calculateCoordinatesFor_but_strengthUp(Pln *Pln);
static void calculateCoordinatesFor_but_strengthDw(Pln *Pln);
static void calculateCoordinatesFor_but_del(Pln *Pln);

static void pln_drag(Pln *Pln, SDL_Event ev);


Pln pln_init(float x, float y, int strength){

    //Bolygó infók
    Pln p;
    p.index = -1;
    p.strength = strength;

    p.removeable = true;
    //Menü
    p.menuIsActive = p.pressing = false;

    pln_reinit(&p, vect_init(x, y));

    return p;
}
static void pln_reinit(Pln *this, Vect pos){
    this->pos = vect_init(pos.x, pos.y);
    //Menü
    if (this->pos.x >= WIDTH/2) this->screenSideLeft = false;
    else this->screenSideLeft = true;
    //Gombok
    calculateCoordinatesFor_but_strengthUp(this);
    calculateCoordinatesFor_but_strengthDw(this);
    calculateCoordinatesFor_but_del(this);
}
static void calculateCoordinatesFor_but_strengthUp(Pln *this){
    float x_coordinate, y_coordinate, width, height;
    width = height = sin(M_PI/4) *plnMenu_getRad(this) / 3;
    y_coordinate = plnMenu_getPos(this).y - plnMenu_getRad(this) *sin(M_PI/4);
    if (this->screenSideLeft)
        x_coordinate = plnMenu_getPos(this).x + plnMenu_getRad(this)*sin(M_PI/4) - width;
    else
        x_coordinate = plnMenu_getPos(this).x - plnMenu_getRad(this)*sin(M_PI/4) + 2 *width;
    this->but_strengthUp = button_init(x_coordinate, y_coordinate, width, height, "+");

}
static void calculateCoordinatesFor_but_strengthDw(Pln *this){
    float x_coordinate, y_coordinate, width, height;
    width = height = sin(M_PI/4) *plnMenu_getRad(this) / 3;
    y_coordinate = plnMenu_getPos(this).y - plnMenu_getRad(this) *sin(M_PI/4);
    if (this->screenSideLeft)
        x_coordinate = plnMenu_getPos(this).x + plnMenu_getRad(this)*sin(M_PI/4) - 3 *width;
    else
        x_coordinate = plnMenu_getPos(this).x - plnMenu_getRad(this)*sin(M_PI/4);
    this->but_strengthDw = button_init(x_coordinate, y_coordinate, width, height, "-");
}
static void calculateCoordinatesFor_but_del(Pln *this){
        float x_coordinate, y_coordinate, width, height;
        height = sin(M_PI/4) *plnMenu_getRad(this) / 3;
        width =  sin(M_PI/4) *plnMenu_getRad(this);
        y_coordinate = plnMenu_getPos(this).y - height/2;
        if (this->screenSideLeft)
            x_coordinate = plnMenu_getPos(this).x;
        else
            x_coordinate = plnMenu_getPos(this).x - width;
        this->but_del = button_init(x_coordinate, y_coordinate, width, height, DEL_PLANET);

}

void pln_drw(SDL_Surface *screen, Pln *this) {
    if (this->removeable) {
        filledCircleRGBA(screen,
                         this->pos.x, this->pos.y, //Középpont
                         pln_getRad(this), //Szélesség
                         0, 200, 0, 255//RGBA
                         );
    }
    else {
        filledCircleRGBA(screen,
                         this->pos.x, this->pos.y, //Középpont
                         pln_getRad(this), //Szélesség
                         255, 200, 0, 255//RGBA
                         );
    }
}

void pln_upd(Pln *this, SDL_Event ev){
    if (ev.type == SDL_MOUSEBUTTONDOWN && pln_hover(this, ev))
        this->pressing = true;
    if (ev.type == SDL_MOUSEBUTTONUP)
        this->pressing = false;

    pln_drag(this, ev);
}

static void pln_drag(Pln *this, SDL_Event ev){
    if (this->pressing && ev.type == SDL_MOUSEMOTION && this->removeable){
        pln_reinit(this, vect_init(ev.motion.x, ev.motion.y));
    }
}

bool pln_hover(Pln *const p, SDL_Event ev) { //Egér benne van a bolygóban
    //(x-u)^2 + (y-v)^2 = r^2
    /*OLVASS!! ->              (x-u)^2                       +                     (y-v)^2                        =              r^2           ;*/
    return (ev.motion.x - p->pos.x)*(ev.motion.x - p->pos.x) + (ev.motion.y - p->pos.y)*(ev.motion.y - p->pos.y) <= pln_getRad(p) *pln_getRad(p);
}

float pln_getRad(Pln *const p){
    return p->strength *0.75;
}

//---------------------------------------------------
//Menüvel kapcsolatos függvények
//---------------------------------------------------

float plnMenu_getRad(Pln *this){
    return PLN_MAX_STRENGTH*2*0.75 + PLN_MIN_STRENGTH;
}
Vect plnMenu_getPos(Pln *this){
    Vect pos = this->pos;
    if (this->screenSideLeft) {//Ha a bolygó a képernyő közepétől jobbra van, akkor a menü középpontja tőle balra  helyezkedjen el
        pos.x += plnMenu_getRad(this)/2;
    }
    else{//Ha a bolygó a képernyő közepétől balra  van, akkor a menü középpontja tőle jobbra helyezkedjen el
        pos.x -= plnMenu_getRad(this)/2;
    }
    return pos;
}


void plnMenu_upd(Pln *this, SDL_Event ev){
    if (ev.type == SDL_MOUSEMOTION || (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT)){
        if (!plnMenu_hover(this, ev)){
            this->menuIsActive = false;
        }
        if (pln_hover(this, ev)){
            this->menuIsActive = true;
        }

        button_upd(&this->but_strengthUp, ev);
        button_upd(&this->but_strengthDw, ev);
        button_upd(&this->but_del,        ev);

        pln_button_strengthDw_action(this);
        pln_button_strengthUp_action(this);
    }
}

void plnMenu_drw(SDL_Surface *screen, Pln *const this, SDL_Event ev, TTF_Font *font){
    if (this->removeable && this->menuIsActive){
        filledCircleRGBA(screen,
                         plnMenu_getPos(this).x, plnMenu_getPos(this).y,
                         plnMenu_getRad(this),
                         0, 0, 0, 100
                         );
        button_drw(screen, &this->but_strengthUp, font);
        button_drw(screen, &this->but_strengthDw, font);
        button_drw(screen, &this->but_del,        font);
    }
}

bool plnMenu_hover(Pln *const this, SDL_Event ev){//Az egér éppen benne van a bolygóban menüjében
    //(x-u)^2 + (y-v)^2 = r^2
    Vect pos = plnMenu_getPos(this);
    /*OLVASS!! ->            (x-u)^2                   +                   (y-v)^2                  */
    return (pos.x - ev.motion.x)*(pos.x - ev.motion.x) + (pos.y - ev.motion.y)*(pos.y - ev.motion.y)
            //=                        r^2
            <= plnMenu_getRad(this) *plnMenu_getRad(this);
}

//---------------------------------------------------
//Gombokkal kapcsolatos függvények
//---------------------------------------------------
void pln_button_strengthUp_action(Pln *this){
    if (this->but_strengthUp.clicked)
        if (this->strength < PLN_MAX_STRENGTH)
            this->strength += PLN_STRENGTH_STEP;
}
void pln_button_strengthDw_action(Pln *this){
    if (this->but_strengthDw.clicked)
        if (this->strength > PLN_MIN_STRENGTH)
            this->strength -= PLN_STRENGTH_STEP;
}





