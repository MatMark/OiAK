#include "Search.h"
#include "Minimum.h"
#include "Eratostenes.h"
#include "TestingModule.h"

void menu();//menu
void genTab(long long amountToGeneration);//generowanie tablicy
void showTab(int amountToDisplay);//wyswietlenie elementow

int *tab;
long long amountOfElements = 0;

int main() {
    srand(time(nullptr));
    menu();
    return 0;
}

void menu() {
    bool end = 0;
    int numbers_of_threads = 1;
    int find;
    while (!end) {
        int pointer;
        printf("Wybierz akcje: "
               "\n1- Generowanie tablicy"
               "\n2- Szukanie wartosci"
               "\n3- Szukanie wartosci minimalnej"
               "\n4- Sito Eratostenesa"
               "\n5- Wyswietlenie tablicy"
               "\n6- Wykonaj testy"
               "\n7- Wyjdz\n");
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
                auto *search = new Search(tab, amountOfElements, numbers_of_threads);
                int ns = search->run(find);
                printf("%d ns\n", ns);
                delete search;
                break;
            }
            case 3: {
                printf("Podaj liczbe watkow: ");
                scanf("%d", &numbers_of_threads);
                auto *minimum = new Minimum(tab, amountOfElements, numbers_of_threads);
                int ns = minimum->run();
                printf("%d ns\n", ns);
                delete minimum;
                break;
            }
            case 4: {
                printf("Liczbe elementow tablicy: ");
                int eratoTableSize = 0;
                scanf("%d", &eratoTableSize);
                printf("\nPodaj liczbe watkow: ");
                scanf("%d", &numbers_of_threads);
                auto *eratostenes = new Eratostenes(eratoTableSize, numbers_of_threads);
                int ns = eratostenes->run();
                printf("%d ns\n", ns);
                delete eratostenes;
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
                int numOfIterations = 0;
                printf("Podaj ile wykonac iteracji: ");
                scanf("%d", &numOfIterations);
                auto *testModule = new TestingModule();
                testModule->RunAllTests(numOfIterations);
                break;
            }
            case 7: {
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

void genTab(long long amountToGeneration) {
    tab = (int *) malloc(amountToGeneration * sizeof(int));
    for (long long i = 0; i < amountToGeneration; i++) {
        tab[i] = rand() % INT_MAX;
    }
    amountOfElements = amountToGeneration;
}

void showTab(int amountToDisplay) {
    for (int i = 0; i < amountToDisplay; i++) {
        printf("tab[%d] = %d\n", i, tab[i]);
    }
}
