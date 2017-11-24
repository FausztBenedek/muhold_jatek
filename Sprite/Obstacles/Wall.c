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
    //     bal oldal�t�l jobbra  &&     jobb oldal�t�l balra        &&       alj�t�l fenntebb          &&   tetej�t�l lentebb  ;
    return ev.motion.x > wall->x && ev.motion.x < wall->x + wall->w && ev.motion.y < wall->y + wall->w && ev.motion.y > wall->y;
}

Vect wall_closestPointToCircle(Wall * w, Vect circle_center){//Visszaadja a legk�zelebbi pontot a k�r k�zep�hez
    //Ez a f�ggv�ny nem kezeli azt az esetet, amikor a k�r k�zepe benne van a n�gyzetben.

    float x, y;
    //          n�gyzet
    //            k�r
    if (circle_center.x >= w->x && circle_center.x <= w->x+w->w)
        x =  circle_center.x;

    //          n�gyzet
    //    k�r
    else if (circle_center.x < w->x)
        x = w->x;

    //          n�gyzet
    //                      k�r
    else
        x = w->x + w->w;

    //n�gyzet   k�r
    if (circle_center.y >= w->y && circle_center.y <= w->y + w->h)
        y = circle_center.y;
    //n�gyzet
    //          k�r
    else if (circle_center.y > w->y + w->h)
        y = w->y + w->h;
    //          k�r
    //n�gyzet
    else
        y = w->y;

    return vect_init(x, y);
}

