#include <stdio.h>
#include "SIMD.h"
#include "SISD.h"

#define repeats 10

struct vector a[sizeTable];
struct vector b[sizeTable];

struct result SIMD_results;
struct result SISD_results;

struct times SIMD_times;
struct times SISD_times;

int main() {
    srand(time(NULL));
    fill_float_vector(a, sizeTable);
    fill_float_vector(b, sizeTable);

    SIMD_run_test(sizeTable, repeats, &*a, &*b, &SIMD_results, &SIMD_times);
    SISD_run_test(sizeTable, repeats, &*a, &*b, &SISD_results, &SISD_times);

    //printf("%f\n", a[0].a);
    //printf("%f\n", b[0].a);
    //printf("%f\n", SIMD_results.sum[0].a);
    //printf("%f\n", SISD_results.sum[0].a);

    printf("SIMD sum: %fs\n", SIMD_times.sum);
    printf("SIMD sub: %fs\n", SIMD_times.sub);
    printf("SIMD mul: %fs\n", SIMD_times.mul);
    printf("SIMD div: %fs\n", SIMD_times.div);
    printf("________________________\n");
    printf("SISD sum: %fs\n", SISD_times.sum);
    printf("SISD sub: %fs\n", SISD_times.sub);
    printf("SISD mul: %fs\n", SISD_times.mul);
    printf("SISD div: %fs\n", SISD_times.div);

    return 0;
}
