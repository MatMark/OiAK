//
// Created by matmark on 15.05.2020.
//

#ifndef INC_4_SIMD_H
#define INC_4_SIMD_H

#include "my_vectors.h"

//dodawanie przy uzyciu SSE
void SIMD_SUM(struct vector a, struct vector b, struct vector *res);

//odejmowanie przy uzyciu SSE
void SIMD_SUB(struct vector a, struct vector b, struct vector *res);

//mnozenie przy uzyciu SSE
void SIMD_MUL(struct vector a, struct vector b, struct vector *res);

//dzielenie przy uzyciu SSE
void SIMD_DIV(struct vector a, struct vector b, struct vector *res);

//wykonanie testow wszystkich operacji
void SIMD_run_test(int size, int repeats, struct vector *a, struct vector *b, struct result *result,
                   struct times *simd_times);

#endif //INC_4_SIMD_H
