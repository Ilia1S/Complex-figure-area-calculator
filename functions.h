#ifndef functions_h
#define functions_h

#include <stdio.h>

int commandLineProceeding(int , char **, short *, short *);
void inputFunction(float *, float *, float *, unsigned *);
float root(float (*)(float), float (*)(float), float, float, float, unsigned*);
float integral(float , float , unsigned , float (*)(float));
float functionOne(float );
float functionTwo(float );
float functionThree(float );
void printAbscissa(float , float , float );
void helpFunc(void);

#endif /* functions_h */
