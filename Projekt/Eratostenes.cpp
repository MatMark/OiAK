//
// Created by matma on 17.05.2020.
//

#include "Eratostenes.h"

Eratostenes::Eratostenes(int tabSize, int numbers_of_threads) {
    this->tabSize = tabSize;
    this->numbers_of_threads = numbers_of_threads;
    genEratoTable();
}

void Eratostenes::genEratoTable() {
    tab = (int *) malloc((tabSize - 1) * sizeof(int));

    for (int i = 2; i <= tabSize; i++) {
        //table starts from 2
        tab[i - 2] = i;
    }
}

void Eratostenes::erato(int start, int end) {
    int last_element = (int) sqrt(tabSize + 2);
    int number = 2;
    while (number < last_element) {
        int start_number = start - (start % number);
        for (int i = start_number; i <= end; i += number) {
            //table elements offset 2
            if (i <= end && tab[i - 2] != number) {
                tab[i - 2] = -1;
            }
        }
        number++;
    }
    std::lock_guard<std::mutex> lock(searching_mutex);
    howManyThreadsDone++;
    condition.notify_one();
}

int Eratostenes::multiCoreErato() {
    if (numbers_of_threads <= 0) {
        std::cout << "Bledna liczba watkow" << std::endl;
        return 0;
    }
    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
    int elements_in_one_thread = (int) ceil((double) tabSize / (double) numbers_of_threads);

    std::vector<std::thread> threads(numbers_of_threads);
    for (int i = 0; i < numbers_of_threads - 1; i++) {
        threads[i] = std::thread(&Eratostenes::erato, this, i * elements_in_one_thread,
                                 (i + 1) * elements_in_one_thread);
    }

    threads[numbers_of_threads - 1] = std::thread(&Eratostenes::erato, this,
                                                  (numbers_of_threads - 1) * elements_in_one_thread,
                                                  tabSize);

    std::unique_lock<std::mutex> lock(searching_mutex);
    condition.wait(lock, [this] { return (howManyThreadsDone == numbers_of_threads); });
    lock.unlock();

    if (howManyThreadsDone == numbers_of_threads) {
        for (int i = 0; i < numbers_of_threads; i++) {
            threads[i].join();
        }
        howManyThreadsDone = 0;
    }
    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
}

int Eratostenes::run() {
    return multiCoreErato();
}
