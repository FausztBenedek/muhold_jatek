#ifndef VECT_H
#define VECT_H

typedef struct Vect{
    float x, y;
}Vect;

Vect vect_init(float x, float y);

Vect sumOf(Vect a, Vect b);
Vect differenceOf(Vect a, Vect b);//Visszatérõ vektor az a pontból b-be mutat. (ab vektor)
void add(Vect * toThis, Vect addThis);
void sub(Vect * fromThis, Vect substractThis);

void multVect(Vect * v, float num);

float magnitudeOf(Vect v);

void normalizeVect(Vect * v);

#endif // VECT_H
