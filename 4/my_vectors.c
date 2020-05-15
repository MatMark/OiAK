//
// Created by matmark on 15.05.2020.
//

#include "my_vectors.h"

float random_float_num() {
    float num = (MIN + 1) + (((float) rand()) / (float) RAND_MAX) * (MAX - (MIN + 1));
    int sign = rand() % 2;
    if (sign) num = -num;
    return num;
}

void fill_float_vector(struct vector vec[], int size) {
    for (int i = 0; i < size; i++) {
        vec[i].a = random_float_num();
        vec[i].b = random_float_num();
        vec[i].c = random_float_num();
        vec[i].d = random_float_num();
    }
}