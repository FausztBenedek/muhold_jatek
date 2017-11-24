#include "Wall.h"

#include "../../tools.h"
#include "../../Constants.h"

Wall wall_init(float x, float y, float w, float h){
    Wall Wall;
    Wall.x = x;    Wall.y = y;    Wall.w = w;   Wall.h = h;
    return Wall;
}

void wall_drw(SDL_Surface *screen, Wall * wall){
    boxRGBA(screen, wall->x, wall->y, wall->x + wall->w, wall->y + wall->h,
            0, 0, 0, 255
            );
}

bool wall_hover(Wall * wall, SDL_Event ev){
    //     bal oldalától jobbra  &&     jobb oldalától balra        &&       aljától fenntebb          &&   tetejétõl lentebb  ;
    return ev.motion.x > wall->x && ev.motion.x < wall->x + wall->w && ev.motion.y < wall->y + wall->w && ev.motion.y > wall->y;
}

Vect wall_closestPointToCircle(Wall * w, Vect circle_center){//Visszaadja a legközelebbi pontot a kör közepéhez
    //Ez a függvény nem kezeli azt az esetet, amikor a kör közepe benne van a négyzetben.

    float x, y;
    //          négyzet
    //            kör
    if (circle_center.x >= w->x && circle_center.x <= w->x+w->w)
        x =  circle_center.x;

    //          négyzet
    //    kör
    else if (circle_center.x < w->x)
        x = w->x;

    //          négyzet
    //                      kör
    else
        x = w->x + w->w;

    //négyzet   kör
    if (circle_center.y >= w->y && circle_center.y <= w->y + w->h)
        y = circle_center.y;
    //négyzet
    //          kör
    else if (circle_center.y > w->y + w->h)
        y = w->y + w->h;
    //          kör
    //négyzet
    else
        y = w->y;

    return vect_init(x, y);
}

