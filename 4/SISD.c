//
// Created by matmark on 15.05.2020.
//

#include "SISD.h"

void SISD_SUM(struct vector a, struct vector b, struct vector *res) {
    asm(
    "fld %4\n\t"
    "fadd %8\n\t"
    "fstp %0\n\t"

    "fld %5\n\t"
    "fadd %7\n\t"
    "fstp %1\n\t"

    "fld %6\n\t"
    "fadd %10\n\t"
    "fstp %2\n\t"

    "fld %7\n\t"
    "fadd %11\n\t"
    "fstp %3\n\t"

    :    "=m" (res->a), //0
    "=m" (res->b),      //1
    "=m" (res->c),      //2
    "=m" (res->d)       //3
    :    "m" (a.a),     //4
    "m" (a.b),          //5
    "m" (a.c),          //6
    "m" (a.d),          //7
    "m" (b.a),          //8
    "m" (b.b),          //9
    "m" (b.c),          //10
    "m" (b.d)           //11
    );
}

void SISD_SUB(struct vector a, struct vector b, struct vector *res) {
    asm(
    "fld %4\n\t"
    "fsub %8\n\t"
    "fstp %0\n\t"

    "fld %5\n\t"
    "fsub %7\n\t"
    "fstp %1\n\t"

    "fld %6\n\t"
    "fsub %10\n\t"
    "fstp %2\n\t"

    "fld %7\n\t"
    "fsub %11\n\t"
    "fstp %3\n\t"

    :    "=m" (res->a), //0
    "=m" (res->b),      //1
    "=m" (res->c),      //2
    "=m" (res->d)       //3
    :    "m" (a.a),     //4
    "m" (a.b),          //5
    "m" (a.c),          //6
    "m" (a.d),          //7
    "m" (b.a),          //8
    "m" (b.b),          //9
    "m" (b.c),          //10
    "m" (b.d)           //11
    );
}

void SISD_MUL(struct vector a, struct vector b, struct vector *res) {
    asm(
    "fld %4\n\t"
    "fmul %8\n\t"
    "fstp %0\n\t"

    "fld %5\n\t"
    "fmul %7\n\t"
    "fstp %1\n\t"

    "fld %6\n\t"
    "fmul %10\n\t"
    "fstp %2\n\t"

    "fld %7\n\t"
    "fmul %11\n\t"
    "fstp %3\n\t"

    :    "=m" (res->a), //0
    "=m" (res->b),      //1
    "=m" (res->c),      //2
    "=m" (res->d)       //3
    :    "m" (a.a),     //4
    "m" (a.b),          //5
    "m" (a.c),          //6
    "m" (a.d),          //7
    "m" (b.a),          //8
    "m" (b.b),          //9
    "m" (b.c),          //10
    "m" (b.d)           //11
    );
}

void SISD_DIV(struct vector a, struct vector b, struct vector *res) {
    asm(
    "fld %4\n\t"
    "fdiv %8\n\t"
    "fstp %0\n\t"

    "fld %5\n\t"
    "fdiv %7\n\t"
    "fstp %1\n\t"

    "fld %6\n\t"
    "fdiv %10\n\t"
    "fstp %2\n\t"

    "fld %7\n\t"
    "fdiv %11\n\t"
    "fstp %3\n\t"

    :    "=m" (res->a), //0
    "=m" (res->b),      //1
    "=m" (res->c),      //2
    "=m" (res->d)       //3
    :    "m" (a.a),     //4
    "m" (a.b),          //5
    "m" (a.c),          //6
    "m" (a.d),          //7
    "m" (b.a),          //8
    "m" (b.b),          //9
    "m" (b.c),          //10
    "m" (b.d)           //11
    );
}

void SISD_run_test(int size, int repeats, struct vector *a, struct vector *b, struct result *result,
                   struct times *sisd_times) {
    clock_t time;
    for (int i = 0; i < repeats; i++) {
        //sum
        time = clock();
        for (int j = 0; j < size; j++) {
            SISD_SUM(a[j], b[j], &result->sum[j]);
        }
        sisd_times->sum += ((double) clock() - time) / CLOCKS_PER_SEC;
        //sub
        time = clock();
        for (int j = 0; j < size; j++) {
            SISD_SUB(a[j], b[j], &result->sub[j]);
        }
        sisd_times->sub += ((double) clock() - time) / CLOCKS_PER_SEC;
        //mul
        time = clock();
        for (int j = 0; j < size; j++) {
            SISD_MUL(a[j], b[j], &result->mul[j]);
        }
        sisd_times->mul += ((double) clock() - time) / CLOCKS_PER_SEC;
        //div
        time = clock();
        for (int j = 0; j < size; j++) {
            SISD_DIV(a[j], b[j], &result->div[j]);
        }
        sisd_times->div += ((double) clock() - time) / CLOCKS_PER_SEC;
    }
    sisd_times->sum /= repeats;
    sisd_times->sub /= repeats;
    sisd_times->mul /= repeats;
    sisd_times->div /= repeats;
}