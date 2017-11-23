#ifndef VECT_H
#define VECT_H


/**A vektorokat illetve pontokat tartalmazó struktúra
*/
typedef struct Vect{
    float x, y;
}Vect;

///Inicializál egy vektort.
Vect vect_init(float x, float y);

///Összead két vektort, visszatér az összeggel.
Vect sumOf(Vect a, Vect b);

///Kivonja b vektort a-ból.
Vect differenceOf(Vect a, Vect b);

///Hozzáadja az első paraméterhez a másodikat.
void add(Vect *toThis, Vect addThis);

///Kivonja az első parméterből a másodikat.
void sub(Vect *fromThis, Vect substractThis);

///Megszorozza a vektort egy számmal.
void multVect(Vect *v, float num);

///@return A vektor hossza
float magnitudeOf(Vect v);

///Egységnyire változtatja a vektort. (Irány nem változik)
void normalizeVect(Vect *v);

#endif // VECT_H
