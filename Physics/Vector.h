#ifndef VECT_H
#define VECT_H

typedef struct vect vect;
typedef struct vect *Vect;
//Ha nagybetûs a deklaráció, akkor pointer lesz

struct vect
{
    float x, y;
};

vect vect_init(float x, float y);

vect sumOf(vect a, vect b);
vect differenceOf(vect a, vect b);//Visszatérõ vektor az a pontból b-be mutat. (ab vektor)
void add(Vect toThis, vect addThis);
void sub(Vect fromThis, vect substractThis);

void multVect(Vect v, float num);

float magnitudeOf(vect v);

void normalizeVect(Vect v);

#endif // VECT_H
