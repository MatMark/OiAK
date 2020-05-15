//
// Created by matmark on 15.05.2020.
//

#ifndef INC_4_SISD_H
#define INC_4_SISD_H

#include "my_vectors.h"

void SISD_SUM(float a, float b, const float *res);

void SISD_SUB(float a, float b, const float *res);

void SISD_MUL(float a, float b, const float *res);

void SISD_DIV(float a, float b, const float *res);

void SISD_run_test(int size, int repeats, struct vector *a, struct vector *b, struct result *result,
                   struct times *sisd_times);

#endif //INC_4_SISD_H
