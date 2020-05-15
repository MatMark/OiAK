#include <stdio.h>
#include "SIMD.h"
#include "SISD.h"
#include "result_saver.h"

#define repeats 10

//tablice wektorow liczb używanych w operacjach
struct vector a[table_size];
struct vector b[table_size];

//tablice wektorow z wynikami
struct result SIMD_results;
struct result SISD_results;

//czasy obliczen
struct times SIMD_times;
struct times SISD_times;

int main() {
    srand(time(NULL));
    //wypelnienie tablic wektorow losowymi liczbami
    fill_float_vector(a, table_size);
    fill_float_vector(b, table_size);

    //wykonanie testow obliczen
    SIMD_run_test(table_size, repeats, &*a, &*b, &SIMD_results, &SIMD_times);
    SISD_run_test(table_size, repeats, &*a, &*b, &SISD_results, &SISD_times);

    //printf("%f\n", a[0].a);
    //printf("%f\n", b[0].a);
    //printf("%f\n", SIMD_results.sum[0].a);
    //printf("%f\n", SISD_results.sum[0].a);

    printf("SIMD sum: %fs\n", SIMD_times.sum);
    printf("SIMD sub: %fs\n", SIMD_times.sub);
    printf("SIMD mul: %fs\n", SIMD_times.mul);
    printf("SIMD div: %fs\n", SIMD_times.div);
    printf("___________________\n");
    printf("SISD sum: %fs\n", SISD_times.sum);
    printf("SISD sub: %fs\n", SISD_times.sub);
    printf("SISD mul: %fs\n", SISD_times.mul);
    printf("SISD div: %fs\n", SISD_times.div);

    //zapis wynikow do plikow
    save("SIMD", &SIMD_times);
    save("SISD", &SISD_times);
    return 0;
}
