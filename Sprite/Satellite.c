#include "Satellite.h"

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <string.h>
#include <stdio.h>

#include "../Constants.h"
#include "../tools.h"
#include "../GameStatusSpecific/GameStatus.h"
#include "Obstacles/Wall.h"
#include "Planet.h"

/*private*/void calcResultantForceForSat(Sat s);

void sat_plnarr_button_del_action(Sat s);

sat sat_init(float x, float y, float rad){
    sat s;
    s.pos = vect_init(x, y);
    s.vel = vect_init(0,0);
    s.force = vect_init(0,0);
    s.rad = rad;
    s.numOf_pln = 0;
    s.numOf_wall = 0;
    s.gate = gate_init(0, HEIGHT);
    s.plnarr = NULL;
    s.wallarr = NULL;
    return s;
}

void sat_resetMotion(Sat s){
    s->vel = vect_init(0,0);
    s->force = vect_init(0,0);
    s->pos = vect_init(10, HEIGHT/5);
}

void sat_resetInitialState(sat *this){
    sat_resetMotion(this);

    free(this->wallarr);
    this->wallarr = NULL;
    this->numOf_wall = 0;

    free(this->plnarr);
    this->plnarr = NULL;
    this->numOf_pln = 0;

    this->gate = gate_init(0, HEIGHT);
}


void sat_game_cleanup(Sat s){
    free(s->wallarr);
    free(s->plnarr);
}

void sat_drw(SDL_Surface *screen, Sat const s){
    filledCircleRGBA(screen,
            s->pos.x, s->pos.y,//(x, y)
            s->rad,//Sugár
            150,150,255,255);//Szín

    gate_drw(screen, &s->gate);
    gate_drw(screen, &s->gate);
}

//----------------------------------
//Hatások az objektumoktól
//----------------------------------

void sat_RUNNING_upd(Sat s){

    calcResultantForceForSat(s);//Ezzel kiszámoljuk az ehhez az időpillanathoz tartozó eredő erőt.

    add(    &(s->vel)   , s->force);

    add(    &(s->pos)   , s->vel);

    //Visszapattanás a falról
    if (s->pos.x - s->rad  <  0) {//A képernyõ bal oldalán túl van a műhold
        s->vel.x *= -1; //Megfordítani horizontálisan a sebességet
        s->force.x *= -1; //Megfordítani horizontálisan az erõt
    }
    else if (s->pos.x + s->rad  >  WIDTH) {//A képernyõ jobb oldalán túl van a műhold
        s->vel.x *= -1; //Megfordítani horizontálisan a sebességet
        s->force.x *= -1; //Megfordítani horizontálisan az erõt
    }
    if (s->pos.y - s->rad  <  0) {//A képernyõ tetején túl van a műhold
        s->vel.y *= -1; //Megfordítani horizontálisan a sebességet
        s->force.y *= -1; //Megfordítani horizontálisan az erõt
    }
    else if (s->pos.y + s->rad  >  HEIGHT) {//A képernyõ alján túl van a műhold
        s->vel.y *= -1; //Megfordítani horizontálisan a sebességet
        s->force.y *= -1; //Megfordítani horizontálisan az erõt
    }
}
void sat_SETTINGS_upd(Sat s, SDL_Event ev){
    bool ableToAddPlanet = true;
    int i;
    if (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT) {
        //Nem hozzáadni, ha menüre kattintunk
        for (i = 0; i < s->numOf_pln; i++){
            if (s->plnarr[i].menuIsActive){
                ableToAddPlanet = false;
            }
        }
        //Nem hozzáadni, ha falra klikkelünk
        for (i = 0; i < s->numOf_wall; i++)
            if (wall_hover(&s->wallarr[i], ev))
                ableToAddPlanet = false;

        //Hozzáadni a bolygót, ha nem bolygóra klikkeltünk
        if (ableToAddPlanet) {
            pln onlyPlanet = pln_init(ev.motion.x, ev.motion.y, 30);
            sat_addPln(s, &onlyPlanet);
        }
    }

    //Törölni a bolygót, ha a törlés gombra klikkelünk
    sat_plnarr_button_del_action(s);
}
/*private*/ void calcResultantForceForSat(Sat s) {//Ezt a függvényt az sat_upd() függvényben hívjuk meg, és az eredő erőt számoljuk ki vele
    /*
    Gravitáció törvénye: F = G * m1 * m2 /d^2
    A G * m1 * m2 szorzatot összevonjuk:
          1. Egy nagy konstans a kísérlet alapján JELE: C, Kiszámítása: (1/(float)SAT_DIV)
          2. A bolygó vonzereje: pln.stength változóban tárolva.

    Ebből a képlet:
          F = C * bolygó_vonzereje / távolság^2
    */
    //Először nullázzuk a jelenlegi erővektort
    multVect(   &(s->force)     ,0);

    ////Majd a bolygókon végigmenve kiszámoljuk az eredő erőt:
    int i;
    for (i = 0; i < s->numOf_pln; i++){
        //Távolság kiszámítása és hozzárendelése a dir vektorhoz
        vect dir = differenceOf(s->pos,   s->plnarr[i].pos);
        if (magnitudeOf(dir) < 1){
            normalizeVect(&dir);//Ha nagyon kicsi a távolság, akkor nagyon nagy a vonzóerő. Ezt kerüljük el.
        }
        //Erő kiszámítása és hozzárendelése a dir vektorhoz
                  //F   = (          konstans         *     bolygó_vonzereje    ) /                 távolság^2           ;
        float magnitude = (  (1/(float)SAT_DIV) * s->plnarr[i].strength   ) / (magnitudeOf(dir) * magnitudeOf(dir));//Érték
        normalizeVect(&dir);//Irány
        multVect(&dir, magnitude);//Irány * Érték
        //Eredő erőt tároló változóhoz hozzáadjuk
        add(    &(s->force)     , dir);
    }
    //A játék élvezhetősége végett növeljük vagy csökkentjük a műholdra ható eredő erőt
    multVect(   &(s->force)     , 8);
}

//----------------------------------
//Bolygókhoz tartozó függvények
//----------------------------------

void sat_addPln(Sat s, Pln p) {
    if (s->numOf_pln == 0){
        s->plnarr = (Pln) malloc(sizeof(struct planet));
    }
    else {
        s->plnarr = (Pln) realloc(s->plnarr, (s->numOf_pln + 1) * sizeof(struct planet));
    }
    s->plnarr[s->numOf_pln] = *p;
    s->numOf_pln++;
}

bool sat_remPln(Sat s, int index) {
    if (!s->plnarr[index].removeable){
        return false;
    }
    int i;
    for(i = index; i < s->numOf_pln - 1; i++){//Léptet
        s->plnarr[i] = s->plnarr[i+1];
    }
    --s->numOf_pln;
    s->plnarr = realloc(s->plnarr, (s->numOf_pln) * sizeof(struct planet));
    return true;
}
void sat_plnarr_button_del_action(Sat s){
    int i;
    for (i = 0; i < s->numOf_pln; i++){
        if (s->plnarr[i].but_del.clicked){
            sat_remPln(s, i);
        }
    }
}


void sat_wall_init(Sat s, int level, FILE *settings){
    //A keresett infókig vaóló eljutás
    char row[MAX_ROW_LENGTH_IN_FILE]; // "X.Szint'0'" = 8 karakter
    sprintf(row, X_LEVEL, level);
    goto_word_in_file(settings, row, MAX_ROW_LENGTH_IN_FILE);

    //Megszámoljuk hány fal van
    fflush(settings);
    unsigned long file_pos = ftell(settings);
    goto_word_in_file(settings, WALL_BEGIN, MAX_ROW_LENGTH_IN_FILE);

    int i;

    for (i = 0;
         !strstr(
                fgets(row, MAX_ROW_LENGTH_IN_FILE, settings),
                WALL_END
                );
         i++);


    s->numOf_wall = i;
    fseek(settings, file_pos, SEEK_SET);

    goto_word_in_file(settings, WALL_BEGIN, MAX_ROW_LENGTH_IN_FILE);
    s->wallarr = (Wall) malloc(s->numOf_wall * sizeof(struct Wall));
    if (s->wallarr == NULL) return;
    for (i = 0; i < s->numOf_wall; i++){
        fgets(row, MAX_ROW_LENGTH_IN_FILE, settings);
        int x, y, w, h;
        sscanf(row, "%d, %d, %d, %d", &x, &y, &w, &h);
        s->wallarr[i] = wall_init(x, y, w, h);
    }

}

void sat_gate_init(Sat this, int level, FILE *settings){
    //A keresett infókig vaóló eljutás
    char row[MAX_ROW_LENGTH_IN_FILE]; // "X.Szint'0'" = 8 karakter
    sprintf(row, X_LEVEL, level);
    goto_word_in_file(settings, row, MAX_ROW_LENGTH_IN_FILE);

    goto_word_in_file(settings, GATE_BEGIN, MAX_ROW_LENGTH_IN_FILE);
    fgets(row, MAX_ROW_LENGTH_IN_FILE, settings);
    int y, h;
    sscanf(row, "%d, %d", &y, &h);
    this->gate = gate_init(y, y+h);
}



