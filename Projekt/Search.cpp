//
// Created by matma on 17.05.2020.
//

#include "Search.h"

void Search::search(int value, int start, int end) {
    for (int i = start; i <= end; i++) {
        if (tab[i] == value) {
            {
                std::lock_guard<std::mutex> lock(searching_mutex);
                search_result.push(i);
            }
        }
    }
    {
        std::lock_guard<std::mutex> lock(searching_mutex);
        howManyThreadsDone++;
    }
    condition.notify_one();
}

int Search::multiCoreSearch(int value) {
    if (numbers_of_threads <= 0) {
        std::cout << "Bledna liczba watkow" << std::endl;
        return 0;
    }
    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
    int elements_in_one_thread = (int) ceil((double) tabSize / (double) numbers_of_threads);

    std::vector<std::thread> threads(numbers_of_threads);

    for (int i = 0; i < numbers_of_threads - 1; i++) {
        threads[i] = std::thread(&Search::search, this, value, i * elements_in_one_thread,
                                 (i + 1) * elements_in_one_thread);
    }

    threads[numbers_of_threads - 1] = std::thread(&Search::search, this, value,
                                                  (numbers_of_threads - 1) * elements_in_one_thread,
                                                  tabSize - 1);

    std::unique_lock<std::mutex> lock(searching_mutex);
    condition.wait(lock, [this] { return (howManyThreadsDone == numbers_of_threads); });
    lock.unlock();

    if (howManyThreadsDone == numbers_of_threads) {
        for (int i = 0; i < numbers_of_threads; i++) {
            threads[i].join();
        }
        std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
    }
    return 0;
}

int Search::run(int find) {
    return multiCoreSearch(find);
}

Search::Search(int tab[], long long tabSize, int numbers_of_threads) {
    this->tab = tab;
    this->tabSize = tabSize;
    this->numbers_of_threads = numbers_of_threads;
}
