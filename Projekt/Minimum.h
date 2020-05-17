//
// Created by matma on 17.05.2020.
//

#ifndef PROJEKT_OIAK_MINIMUM_H
#define PROJEKT_OIAK_MINIMUM_H

#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <cmath>
#include <atomic>
#include <vector>

class Minimum {
    int howManyThreadsDone = 0;
    int *tab;
    long long tabSize = 0;
    int numbers_of_threads = 1;
    std::mutex searching_mutex;
    std::condition_variable condition;
    std::atomic<int> global_min;
public:
    Minimum(int tab[], long long tabSize, int numbers_of_threads);

    int run();

private:
    int multiCoreMinimum();

    void minimum(int start, int end);
};


#endif //PROJEKT_OIAK_MINIMUM_H
