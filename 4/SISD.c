//
// Created by matmark on 15.05.2020.
//

#include "SISD.h"

//dodawanie przy pomocy FPU
void SISD_SUM(float a, float b, const float *res) {
    asm(
    "fld %1;"
    "fadd %2;"
    "fstp %0;"

    :"=m" (res)
    :"m" (a),
    "m" (b)
    );
}

//odejmowanie przy pomocy FPU
void SISD_SUB(float a, float b, const float *res) {
    asm(
    "fld %1;"
    "fsub %2;"
    "fstp %0;"

    :"=m" (res)
    :"m" (a),
    "m" (b)
    );
}

//mnozenie przy pomocy FPU
void SISD_MUL(float a, float b, const float *res) {
    asm(
    "fld %1;"
    "fmul %2;"
    "fstp %0;"

    :"=m" (res)
    :"m" (a),
    "m" (b)
    );
}

//dzielenie przy pomocy FPU
void SISD_DIV(float a, float b, const float *res) {
    asm(
    "fld %1;"
    "fdiv %2;"
    "fstp %0;"

    :"=m" (res)
    :"m" (a),
    "m" (b)
    );
}

//wykonanie testow wszystkich operacji
void SISD_run_test(int size, int repeats, struct vector *a, struct vector *b, struct result *result,
                   struct times *sisd_times) {
    clock_t time;
    for (int i = 0; i < repeats; i++) {
        //sum
        time = clock();
        for (int j = 0; j < size; j++) {
            SISD_SUM(a[j].a, b[j].a, &result->sum[j].a);
            SISD_SUM(a[j].b, b[j].b, &result->sum[j].b);
            SISD_SUM(a[j].c, b[j].c, &result->sum[j].c);
            SISD_SUM(a[j].d, b[j].d, &result->sum[j].d);
        }
        sisd_times->sum += ((double) clock() - time) / CLOCKS_PER_SEC;
        //sub
        time = clock();
        for (int j = 0; j < size; j++) {
            SISD_SUB(a[j].a, b[j].a, &result->sub[j].a);
            SISD_SUB(a[j].b, b[j].b, &result->sub[j].b);
            SISD_SUB(a[j].c, b[j].c, &result->sub[j].c);
            SISD_SUB(a[j].d, b[j].d, &result->sub[j].d);
        }
        sisd_times->sub += ((double) clock() - time) / CLOCKS_PER_SEC;
        //mul
        time = clock();
        for (int j = 0; j < size; j++) {
            SISD_MUL(a[j].a, b[j].a, &result->mul[j].a);
            SISD_MUL(a[j].b, b[j].b, &result->mul[j].b);
            SISD_MUL(a[j].c, b[j].c, &result->mul[j].c);
            SISD_MUL(a[j].d, b[j].d, &result->mul[j].d);
        }
        sisd_times->mul += ((double) clock() - time) / CLOCKS_PER_SEC;
        //div
        time = clock();
        for (int j = 0; j < size; j++) {
            SISD_DIV(a[j].a, b[j].a, &result->div[j].a);
            SISD_DIV(a[j].b, b[j].b, &result->div[j].b);
            SISD_DIV(a[j].c, b[j].c, &result->div[j].c);
            SISD_DIV(a[j].d, b[j].d, &result->div[j].d);
        }
        sisd_times->div += ((double) clock() - time) / CLOCKS_PER_SEC;
    }
    //usrednienie czasow obliczen
    sisd_times->sum /= repeats;
    sisd_times->sub /= repeats;
    sisd_times->mul /= repeats;
    sisd_times->div /= repeats;
}