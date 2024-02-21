#ifndef FILTROS_H
#define FILTROS_H

#include "bmp.h"

typedef struct tagFILTRO {

	float RR, RG, RB;
	float GR, GG, GB;
	float BR, BG, BB;
} FILTRO;

FILTRO SEPIA;

void filtro (BMPDATA*, FILTRO);
void blancoYNegro (BMPDATA*);
void aclarar(BMPDATA*, long);
void medianFilter(BMPDATA*);
void negativo(BMPDATA*);
void blend(BMPDATA*, BMPDATA*);
void blendASM(BMPDATA*, BMPDATA*);
int cantPixels (BMPDATA*);
unsigned char mediana (unsigned char*, int);



#endif
