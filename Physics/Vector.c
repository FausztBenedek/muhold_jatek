#include "Vector.h"
#include <math.h>

Vect vect_init(float x, float y) {
    Vect v;
    v.x = x;
    v.y = y;
    return v;
}

Vect sumOf(Vect a, Vect b) {
    return vect_init(a.x + b.x, a.y + b.y);
}
Vect differenceOf(Vect a, Vect b){//Visszatérõ vektor az a pontból b-be mutat. (ab vektor)
    return vect_init(b.x-a.x, b.y-a.y);
}
void add(Vect * toThis, Vect addThis) {
    *toThis = sumOf(*toThis, addThis);
}
void sub(Vect * fromThis, Vect substractThis) {
    *fromThis = sumOf(*fromThis,
                      vect_init(-1*substractThis.x, -1*substractThis.y)
                      );
}

void multVect(Vect * v, float num) {
    v->x *= num;
    v->y *= num;
}

float magnitudeOf(Vect v) {
    return (float)(sqrt(v.x*v.x + v.y*v.y));
}

void normalizeVect(Vect * v) {
    float mag = magnitudeOf(*v);
    v->x = (v->x)/mag;
    v->y = (v->y)/mag;
}
