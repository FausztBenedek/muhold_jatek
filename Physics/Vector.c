#include "Vector.h"
#include <math.h>

vect vect_init(float x, float y) {
    vect v;
    v.x = x;
    v.y = y;
    return v;
}

vect sumOf(vect a, vect b) {
    return vect_init(a.x + b.x, a.y + b.y);
}
vect differenceOf(vect a, vect b){//Visszatérõ vektor az a pontból b-be mutat. (ab vektor)
    return vect_init(b.x-a.x, b.y-a.y);
}
void add(Vect toThis, vect addThis) {
    *toThis = sumOf(*toThis, addThis);
}
void sub(Vect fromThis, vect substractThis) {
    *fromThis = sumOf(*fromThis,
                      vect_init(-1*substractThis.x, -1*substractThis.y)
                      );
}

void multVect(Vect v, float num) {
    v->x *= num;
    v->y *= num;
}

float magnitudeOf(vect v) {
    return (float)(sqrt(v.x*v.x + v.y*v.y));
}

void normalizeVect(Vect v) {
    float mag = magnitudeOf(*v);
    v->x = (v->x)/mag;
    v->y = (v->y)/mag;
}
