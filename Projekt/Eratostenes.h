//
// Created by matma on 17.05.2020.
//

#ifndef PROJEKT_OIAK_ERATOSTENES_H
#define PROJEKT_OIAK_ERATOSTENES_H

#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <cmath>
#include <atomic>
#include <vector>

class Eratostenes {
    int howManyThreadsDone = 0;
    int *tab;
    int tabSize = 0;
    int numbers_of_threads = 1;
    std::mutex searching_mutex;
    std::condition_variable condition;

public:
    Eratostenes(int tabSize, int numbers_of_threads);

    int run();

private:
    void genEratoTable();

    int multiCoreErato();

    void erato(int start, int end);
};


#endif //PROJEKT_OIAK_ERATOSTENES_H
