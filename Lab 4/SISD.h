//
// Created by matmark on 15.05.2020.
//

#ifndef INC_4_SISD_H
#define INC_4_SISD_H

#include "my_vectors.h"

//dodawanie przy pomocy FPU
void SISD_SUM(float a, float b, const float *res);

//odejmowanie przy pomocy FPU
void SISD_SUB(float a, float b, const float *res);

//mnożenie przy pomocy FPU
void SISD_MUL(float a, float b, const float *res);

//dzieleni przy pomocy FPU
void SISD_DIV(float a, float b, const float *res);

//wykonanie testow wszystkich operacji
void SISD_run_test(int size, int repeats, struct vector *a, struct vector *b, struct result *result,
                   struct times *sisd_times);

#endif //INC_4_SISD_H
