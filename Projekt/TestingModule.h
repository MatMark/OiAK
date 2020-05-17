//
// Created by matma on 17.05.2020.
//

#ifndef PROJEKT_OIAK_TESTINGMODULE_H
#define PROJEKT_OIAK_TESTINGMODULE_H

#include <iostream>
#include <map>
#include <ctime>
#include <fstream>
#include "Search.h"
#include "Minimum.h"
#include "Eratostenes.h"

class TestingModule {
public:
//    int numOfThreads[11] = {1, 2, 3, 4, 5, 6, 7, 8, 16, 32, 64};
//    int amountOfElements[9] = {10000, 50000, 100000, 500000, 1000000, 5000000, 10000000, 50000000, 100000000};
    int numOfThreads[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int amountOfElements[2] = {5000000, 10000000};
    enum Algorithms {
        e_Search,
        e_Minimum,
        e_Eratostenes
    };

    void RunTest(Algorithms algorithm, int numOfIterations, int arraySize);

    static void SaveFile(const std::map<int, unsigned long long> &results, const std::string &name);

    static std::string GenerateRandomFileName(Algorithms algorithm, int tabSize);

    void RunAllTests(int numOfIterations);

    static int *genTab(long long amountToGeneration);
};


#endif //PROJEKT_OIAK_TESTINGMODULE_H
