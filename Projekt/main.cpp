#include <thread>
#include <iostream>
#include <atomic>
#include <cmath>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>


void menu();//menu
void genTab(long long amountToGeneration);//generowanie tablicy
void search(int element, int start, int end);//szukanie zadanego elementu
void minimum(int start, int end);//szukanie najmniejszego elementu
void erato(int start, int end);

void showTab(int amountOfElements);//wyswietlenie wszystkich elementow
void multiCoreSearch(int value);

void multiCoreMin();

void multiCoreErato();

void genEratoTable();

int howManyThreadsDone = 0;
int *x;
int *g_eratoTable;
int g_size;
long long amountOfElements = 0;
int find;
int numbers_of_threads = 1;
std::atomic<int> global_min;
std::mutex searching_mutex;
std::condition_variable condition;
std::queue<int> search_result;

int main() {
    srand(time(NULL));
    menu();
    return 0;
}

//-------------------------------------------------wybieranko
void menu() {
    bool end = 0;
    while (!end) {
        int pointer;
        printf("Wybierz akcje: "
               "\n1- Generowanie tablicy"
               "\n2- Szukanie wartosci"
               "\n3- Szukanie wartosci minimalnej"
               "\n4- Sito Eratostenesa"
               "\n5- Wyswietlenie tablicy"
               "\n6- Wyjdz\n");
        scanf("%d", &pointer);

        switch (pointer) {
            case 1: {
                int amountToGeneration = 0;
                printf("Podaj ile elementow chcesz wygenerowac: ");
                scanf("%d", &amountToGeneration);
                genTab(amountToGeneration);
                break;
            }
            case 2: {
                printf("Podaj liczbe watkow: ");
                scanf("%d", &numbers_of_threads);
                printf("\nPodaj szukana wartosc: ");
                scanf("%d", &find);
                multiCoreSearch(find);
                break;
            }
            case 3: {
                printf("Podaj liczbe watkow: ");
                scanf("%d", &numbers_of_threads);
                multiCoreMin();
                break;
            }
            case 4: {
                printf("Liczbe elementow tablicy: ");
                scanf("%d", &g_size);
                genEratoTable();
                printf("\nPodaj liczbe watkow: ");
                scanf("%d", &numbers_of_threads);
                multiCoreErato();
                break;
            }
            case 5: {
                int amountToDisplay = 0;
                printf("Podaj ile chcesz wyswietlic elementow: ");
                scanf("%d", &amountToDisplay);
                showTab(amountToDisplay);
                break;
            }
            case 6: {
                end = 1;
                break;
            }
            default: {
                printf("Wybierz prawidlowa akcje!\n");
                break;
            }
        }
    }
}

//-------------------------------------------------losowanko
void genTab(long long amountToGeneration) {
    x = (int *) malloc(amountToGeneration * sizeof(int));
//    printf("Zaalokowano! %lld", amountToGeneration);
    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

    for (long long i = 0; i < amountToGeneration; i++) {
        x[i] = rand() % INT_MAX;
    }
    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << " ns"
              << std::endl;
//    printf("Wygenerowano: %lld elementow", amountToGeneration);
//    printf("Czas wykonywania: generowanie tablicy : %fs\n", time_taken);
    amountOfElements = amountToGeneration;
}

//--------------------------------------------------szukanko
void search(int value, int start, int end) {
    for (int i = start; i <= end; i++) {
        if (x[i] == value) {
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

//-------------------------------------------------szukanko minimum
void minimum(int start, int end) {
    for (int i = start; i <= end; i++) {
        if (x[i] < global_min.load(std::memory_order_seq_cst)) global_min.store(x[i], std::memory_order_seq_cst);
    }
    std::lock_guard<std::mutex> lock(searching_mutex);
    howManyThreadsDone++;
    condition.notify_one();
}

//300827500 1wat
//162907300 2wat
//100941800 4wat
//76944800 8wat
//63964000 16wat
//72465500 32wat
//60967500 64wat

void multiCoreSearch(int value) {
    if (numbers_of_threads <= 0) {
        std::cout << "Bledna liczba watkow" << std::endl;
        return;
    }
    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

    int elements_in_one_thread = (int) ceil((double) amountOfElements / (double) numbers_of_threads);

    std::vector<std::thread> threads(numbers_of_threads);

    for (int i = 0; i < numbers_of_threads - 1; i++) {
        threads[i] = std::thread(&search, value, i * elements_in_one_thread, (i + 1) * elements_in_one_thread);
    }

    threads[numbers_of_threads - 1] = std::thread(&search, value, (numbers_of_threads - 1) * elements_in_one_thread,
                                                  amountOfElements - 1);

    std::unique_lock<std::mutex> lock(searching_mutex);
    condition.wait(lock, [] { return (howManyThreadsDone == numbers_of_threads); });
    lock.unlock();

    if (howManyThreadsDone == numbers_of_threads) {

        for (int i = 0; i < numbers_of_threads; i++) {
            threads[i].join();
        }
        while (!search_result.empty()) {
//                std::cout << search_result.front() << std::endl;
            search_result.pop();
        }
        std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << " ns"
                  << std::endl;
        return;
    }
}

//413761800 1wat
//230866700 2wat
//164899100 4wat
//154912000 8wat
//139918400 16wat
//149922900 32wat
//129926800 64wat


void multiCoreMin() {
    if (numbers_of_threads <= 0) {
        std::cout << "Bledna liczba watkow" << std::endl;
        return;
    }
    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
    global_min.store(INT_MAX, std::memory_order_seq_cst);
    int elements_in_one_thread = (int) ceil((double) amountOfElements / (double) numbers_of_threads);

    std::vector<std::thread> threads(numbers_of_threads);

    for (int i = 0; i < numbers_of_threads - 1; i++) {
        threads[i] = std::thread(&minimum, i * elements_in_one_thread, (i + 1) * elements_in_one_thread);
    }

    threads[numbers_of_threads - 1] = std::thread(&minimum, (numbers_of_threads - 1) * elements_in_one_thread,
                                                  amountOfElements - 1);

    std::unique_lock<std::mutex> lock(searching_mutex);
    condition.wait(lock, [] { return (howManyThreadsDone == numbers_of_threads); });
    lock.unlock();

    if (howManyThreadsDone == numbers_of_threads) {

        for (int i = 0; i < numbers_of_threads; i++) {
            threads[i].join();
        }
//        std::cout << global_min << std::endl;
        std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << " ns"
                  << std::endl;
        return;
    }
}

void genEratoTable() {
    g_eratoTable = (int *) malloc((g_size - 1) * sizeof(int));

    for (int i = 2; i <= g_size; i++) {
        //table starts from 2
        g_eratoTable[i - 2] = i;
    }
    amountOfElements = g_size;
}

void erato(int start, int end) {
    int last_element = (int) sqrt(g_size + 2);
    int number = 2;
    while (number < last_element) {
        int start_number = start - (start % number);
        for (int i = start_number; i <= end; i += number) {
            //table elements offset 2
            if (i <= end && g_eratoTable[i - 2] != number) {
                g_eratoTable[i - 2] = -1;
            }
        }
        number++;
    }
    std::lock_guard<std::mutex> lock(searching_mutex);
    howManyThreadsDone++;
    condition.notify_one();
}
// 82953500 1wat
// 35991400 2wat
// 22992500 4wat
// 15991700 8wat
// 12991400 16wat
// 8995300 32wat
// 9993900 64wat

void multiCoreErato() {
    if (numbers_of_threads <= 0) {
        std::cout << "Bledna liczba watkow" << std::endl;
        return;
    }
    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
    int elements_in_one_thread = (int) ceil((double) g_size / (double) numbers_of_threads);

        std::vector<std::thread> threads(numbers_of_threads);
        for (int i = 0; i < numbers_of_threads - 1; i++) {
            threads[i] = std::thread(&erato, i * elements_in_one_thread, (i + 1) * elements_in_one_thread);
        }

        threads[numbers_of_threads - 1] = std::thread(&erato, (numbers_of_threads - 1) * elements_in_one_thread,
                                                      g_size);

        std::unique_lock<std::mutex> lock(searching_mutex);
        condition.wait(lock, [] { return (howManyThreadsDone == numbers_of_threads); });
        lock.unlock();

        if (howManyThreadsDone == numbers_of_threads) {
            for (int i = 0; i < numbers_of_threads; i++) {
                threads[i].join();
            }
            howManyThreadsDone = 0;
        }
//    for (int j = 0; j < g_size - 1; j++) {
//        if (g_eratoTable[j] != -1) {
//            std::cout << g_eratoTable[j] << std::endl;
//        }
//    }
    //        std::cout << global_min << std::endl;
    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << " ns"
              << std::endl;
}

//------------------------------------------------wyswietlanko
void showTab(int amountToDisplay) {
    clock_t time;
    time = clock();
    for (int i = 0; i < amountToDisplay; i++) {
        printf("tab[%d] = %d\n", i, x[i]);
    }
    time = clock() - time;
    double time_taken = ((double) time) / CLOCKS_PER_SEC;
    printf("Wyswietlono: %d elementow", amountToDisplay);
    printf("Czas wykonywania: wyswietlenie tablicy : %fs\n", time_taken);
}
