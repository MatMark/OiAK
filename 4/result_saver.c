//
// Created by matmark on 15.05.2020.
//

#include "result_saver.h"

void save(char type[], struct times *res_times) {
    FILE *file;
    char file_name[14] = "";
    char numbers[10];

    sprintf(numbers, "_%d.txt", (4 * table_size));
    strcat(file_name, type);
    strcat(file_name, numbers);
    file = fopen(file_name, "w");
    fprintf(file, "Typ obliczen: %s\nLiczba liczb: %d\nSredni czas [s]: \n+ %lf \n- %lf \n* %lf \n/ %lf \n", type,
            (4 * table_size), res_times->sum, res_times->sub, res_times->mul, res_times->div);
}