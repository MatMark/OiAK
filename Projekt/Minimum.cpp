//
// Created by matma on 17.05.2020.
//

#include "Minimum.h"

Minimum::Minimum(int *tab, long long tabSize, int numbers_of_threads) {
    this->tab = tab;
    this->tabSize = tabSize;
    this->numbers_of_threads = numbers_of_threads;
    global_min.store(INT_MAX, std::memory_order_seq_cst);
}

int Minimum::run() {
    return multiCoreMinimum();
}

int Minimum::multiCoreMinimum() {
    if (numbers_of_threads <= 0) {
        std::cout << "Bledna liczba watkow" << std::endl;
        return 0;
    }
    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
    int elements_in_one_thread = (int) ceil((double) tabSize / (double) numbers_of_threads);

    std::vector<std::thread> threads(numbers_of_threads);

    for (int i = 0; i < numbers_of_threads - 1; i++) {
        threads[i] = std::thread(&Minimum::minimum, this, i * elements_in_one_thread, (i + 1) * elements_in_one_thread);
    }

    threads[numbers_of_threads - 1] = std::thread(&Minimum::minimum, this,
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

void Minimum::minimum(int start, int end) {
    for (int i = start; i <= end; i++) {
        if (tab[i] < global_min.load(std::memory_order_seq_cst)) global_min.store(tab[i], std::memory_order_seq_cst);
    }
    std::lock_guard<std::mutex> lock(searching_mutex);
    howManyThreadsDone++;
    condition.notify_one();
}

