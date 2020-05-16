//
// Created by matmark on 15.05.2020.
//

#include "SIMD.h"

//dodawanie przy uzyciu SSE
void SIMD_SUM(struct vector a, struct vector b, struct vector *res) {
    asm(
    "movaps %1, %%xmm0;"
    "movaps %2, %%xmm1;"
    "addps %%xmm1, %%xmm0;"
    "movaps %%xmm0, %0;"
    :"=m" (*res)
    :"m" (a), "m" (b)
    );
}

//odejmowanie przy uzyciu SSE
void SIMD_SUB(struct vector a, struct vector b, struct vector *res) {
    asm(
    "movaps %1, %%xmm0;"
    "movaps %2, %%xmm1;"
    "subps %%xmm1, %%xmm0;"
    "movaps %%xmm0, %0;"
    :"=m" (*res)
    :"m" (a), "m" (b)
    );
}

//mnozenie przy uzyciu SSE
void SIMD_MUL(struct vector a, struct vector b, struct vector *res) {
    asm(
    "movaps %1, %%xmm0;"
    "movaps %2, %%xmm1;"
    "mulps %%xmm1, %%xmm0;"
    "movaps %%xmm0, %0;"
    :"=m" (*res)
    :"m" (a), "m" (b)
    );
}

//dzielenie przy uzyciu SSE
void SIMD_DIV(struct vector a, struct vector b, struct vector *res) {
    asm(
    "movaps %1, %%xmm0;"
    "movaps %2, %%xmm1;"
    "divps %%xmm1, %%xmm0;"
    "movaps %%xmm0, %0;"
    :"=m" (*res)
    :"m" (a), "m" (b)
    );
}

//wykonanie testow wszystkich operacji
void SIMD_run_test(int size, int repeats, struct vector *a, struct vector *b, struct result *result,
                   struct times *simd_times) {
    clock_t time;
    for (int i = 0; i < repeats; i++) {
        //sum
        time = clock();
        for (int j = 0; j < size; j++) {
            SIMD_SUM(a[j], b[j], &result->sum[j]);
        }
        simd_times->sum += ((double) clock() - time) / CLOCKS_PER_SEC;
        //sub
        time = clock();
        for (int j = 0; j < size; j++) {
            SIMD_SUB(a[j], b[j], &result->sub[j]);
        }
        simd_times->sub += ((double) clock() - time) / CLOCKS_PER_SEC;
        //mul
        time = clock();
        for (int j = 0; j < size; j++) {
            SIMD_MUL(a[j], b[j], &result->mul[j]);
        }
        simd_times->mul += ((double) clock() - time) / CLOCKS_PER_SEC;
        //div
        time = clock();
        for (int j = 0; j < size; j++) {
            SIMD_DIV(a[j], b[j], &result->div[j]);
        }
        simd_times->div += ((double) clock() - time) / CLOCKS_PER_SEC;
    }
    //usrednienie czasow obliczen
    simd_times->sum /= repeats;
    simd_times->sub /= repeats;
    simd_times->mul /= repeats;
    simd_times->div /= repeats;
}