//
// Created by matmark on 15.05.2020.
//

#ifndef INC_4_MY_VECTORS_H
#define INC_4_MY_VECTORS_H

#include <stdlib.h>
#include <time.h>
//2048 = 4*512
//4096 = 4*1024
//8192 = 4*2048
#define table_size 2048
#define MAX 999999.0f
#define MIN 100000.0f

// 4 liczby typu float (32 bit) = wektor 128 bitowy
struct vector {
    float a;
    float b;
    float c;
    float d;
};

struct result {
    struct vector sum[table_size];
    struct vector sub[table_size];
    struct vector mul[table_size];
    struct vector div[table_size];
};

struct times {
    double sum;
    double sub;
    double mul;
    double div;
};

float random_float_num();

void fill_float_vector(struct vector vec[], int size);

#endif //INC_4_MY_VECTORS_H
