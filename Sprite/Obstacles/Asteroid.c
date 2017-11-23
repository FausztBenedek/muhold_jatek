#include "Asteroid.h"

#include <stdio.h>

#include "../../Physics/Vector.h"
#include "../../Constants.h"
#include "../../tools.h"

static  void calcForceForAstr(Astr a);

astr astr_init(float centerX, float centerY, float posX, float posY, float rad, float velX, float velY) {
    astr a;
    a.pos = vect_init(posX, posY);
    a.vel = vect_init(velX, velY);
    a.force = vect_init(0,0);
    a.center = vect_init(centerX, centerY);
    a.rad = rad;
    return a;
}

void astr_drw(SDL_Surface *screen, Astr const a){
    filledCircleRGBA(screen,
                     a->pos.x, a->pos.y, //Középpont
                     a->rad, //Szélesség
                     0, 0, 0, 255//RGBA
                     );
}

void astr_upd(Astr a){
    calcForceForAstr(a);//Ezzel kiszámoljuk az ehhez az idõpillanathoz tartozó eredõ erõt.
    add(    &(a->vel)   , a->force);
    add(    &(a->pos)   , a->vel);
}

static  void calcForceForAstr(Astr a){//Ezt a függvényt az astr_upd() függvényben hívjuk meg, és az eredõ erõt számoljuk ki vele
    /*
    Gravitáció törvénye: F = G * m1 * m2 /d^2
    A G * m1 * m2 szorzatot összevonjuk: Egy nagy konstans kísérlet alapján, JELE: C, Kiszámítása: (1/(float)ASTR_DIV)

    Ebbõl a képlet:
          F = C/ távolság^2
    */
    //Elõször nullázzuk a jelenlegi erõvektort
    multVect(   &(a->force)     ,0);

    //Majd kiszámoljuk a jelenlegi erőt
    //1. Irány kiszámítása és hozzárendelése a dir vektorhoz
    Vect dir = differenceOf(a->pos,   a->center);
    if (magnitudeOf(dir) < 1) normalizeVect(&dir);//Ha nagyon kicsi a távolság, akkor nagyon nagy a vonzóerõ. Ezt kerüljük el.

    //Erõ kiszámítása és hozzárendelése a dir vektorhoz
    float dist = magnitudeOf(dir);
              //F   =      konstans      / távolság^2 ;
    float magnitude = (1/(float)ASTR_DIV) / (dist*dist);//Érték
    normalizeVect(&dir);//Irány
    multVect(&dir, magnitude);//Irány * Érték

    add(    &(a->force)     , dir);
    //A játék élvezhetõsége végett növeljük vagy csökkentjük a mûholdra ható eredõ erõt
    multVect(   &(a->force)     , 5000);
}
