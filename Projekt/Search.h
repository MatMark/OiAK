//
// Created by matma on 17.05.2020.
//

#ifndef PROJEKT_OIAK_SEARCH_H
#define PROJEKT_OIAK_SEARCH_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <iostream>
#include <cmath>

class Search {
    int howManyThreadsDone = 0;
    int *tab;
    long long tabSize = 0;
    int numbers_of_threads = 1;
    std::mutex searching_mutex;
    std::condition_variable condition;
    std::queue<int> search_result;
public:
    Search(int tab[], long long tabSize, int numbers_of_threads);

    int run(int find);

private:
    int multiCoreSearch(int value);

    void search(int element, int start, int end);
};


#endif //PROJEKT_OIAK_SEARCH_H
