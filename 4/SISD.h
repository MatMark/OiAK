//
// Created by matmark on 15.05.2020.
//

#ifndef INC_4_SISD_H
#define INC_4_SISD_H

#include "my_vectors.h"

void SISD_SUM(struct vector a, struct vector b, struct vector *res);

void SISD_SUB(struct vector a, struct vector b, struct vector *res);

void SISD_MUL(struct vector a, struct vector b, struct vector *res);

void SISD_DIV(struct vector a, struct vector b, struct vector *res);

void SISD_run_test(int size, int repeats, struct vector *a, struct vector *b, struct result *result,
                   struct times *sisd_times);

#endif //INC_4_SISD_H
