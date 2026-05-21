#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define TAM 3000000

int main(){
    int tam = TAM;
    srand(time(NULL));
    int *v = (int*) malloc(tam * sizeof(int));

    for(int i = 0; i < tam; i++){
        v[i] = rand() % TAM;
    }

    clock_t start = clock();
    insertionSort(v, tam);
    clock_t end = clock();
    printf("\nTempo de ordenacao: %lf segundos\n", ((double)(end - start)) / CLOCKS_PER_SEC);

    free(v);
    return 0;
}