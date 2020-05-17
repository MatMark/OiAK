//
// Created by matma on 17.05.2020.
//

#include "TestingModule.h"

void TestingModule::RunTest(Algorithms algorithm, int numOfIterations, int arraySize) {

    std::map<int, unsigned long long> results;

    for (int threads : numOfThreads) {
        unsigned long long sumOfTimes = 0;

        switch (algorithm) {
            case e_Search: {
                int *tab = genTab(arraySize);
                int find = rand() % INT_MAX;
                for (int i = 0; i < numOfIterations; i++) {
                    auto *testSearch = new Search(tab, arraySize, threads);
                    sumOfTimes += testSearch->run(find);
                    delete testSearch;
                }
                break;
            }
            case e_Minimum: {
                int *tab = genTab(arraySize);
                for (int i = 0; i < numOfIterations; i++) {
                    auto *testMinimum = new Minimum(tab, arraySize, threads);
                    sumOfTimes += testMinimum->run();
                    delete testMinimum;
                }
                break;
            }
            case e_Eratostenes: {
                auto *testEratostenes = new Eratostenes(arraySize, threads);
                for (int i = 0; i < numOfIterations; i++) {
                    sumOfTimes += testEratostenes->run();
                }
                delete testEratostenes;
                break;
            }
        }

        unsigned long long averageTime = sumOfTimes / numOfIterations;

        results[threads] = averageTime;
    }
    TestingModule::SaveFile(results, GenerateRandomFileName(algorithm, arraySize));
}

void TestingModule::SaveFile(const std::map<int, unsigned long long> &results, const std::string &name) {
    std::string savePath = "./results/";
    std::ofstream file;
    file.open(savePath + name);
    std::cout << savePath + name << std::endl;
    for (auto const &result : results) {
        file << "("
             << result.first
             << ", "
             << result.second
             << ")"
             << std::endl;
    }
    file.close();
}


std::string TestingModule::GenerateRandomFileName(Algorithms algorithm, int tabSize) {
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string s(30, '\0');
    std::strftime(&s[0], s.size(), "_%Y-%m-%d %H.%M.%S.txt", std::localtime(&now));
    std::string name = s;

    switch (algorithm) {
        case e_Search:
            return "search_" + std::to_string(tabSize) + name;
        case e_Minimum:
            return "minimum_" + std::to_string(tabSize) + name;
        case e_Eratostenes:
            return "eratostenes_" + std::to_string(tabSize) + name;
        default:
            return "";
    }
}

void TestingModule::RunAllTests(int numOfIterations) {
    for (int iter : amountOfElements) {
        this->RunTest(e_Search, numOfIterations, iter);
        this->RunTest(e_Minimum, numOfIterations, iter);
        this->RunTest(e_Eratostenes, numOfIterations, iter);
    }
}

int *TestingModule::genTab(long long amountToGeneration) {
    int *x = (int *) malloc(amountToGeneration * sizeof(int));
    for (long long i = 0; i < amountToGeneration; i++) {
        x[i] = rand() % INT_MAX;
    }
    return x;
}

