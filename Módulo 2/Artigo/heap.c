#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "benchmark.h"
#define TAM 3000

void heapSort(int *v, int n);
void criaHeap(int *v, int i, int f);

int main(){
    int tam = TAM;
    srand(time(NULL));
    int *v = (int*) malloc(tam * sizeof(int));

    for(int i = 0; i < tam; i++){
        v[i] = rand() % TAM;
    }

    clock_t start = clock();
    heapSort(v, tam);
    clock_t end = clock();
    double tempo = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTempo de ordenacao: %lf segundos\n", tempo);
    salvarResultado(tam, "Heap Sort", tempo);

    free(v);
    return 0;
}

void heapSort(int *v, int n){
    int i, aux;

    for(i = (n - 1)/2; i >= 0; i--){
        criaHeap(v, i, n - 1);
    }

    for(i = n - 1; i >= 1; i--){
        aux = v[0];
        v[0] = v[i];
        v[i] = aux;
        criaHeap(v, 0, i - 1);
    }
}

void criaHeap(int *v, int i, int f){
    int aux = v[i];
    int j = i * 2 + 1;

    while(j <= f){
        if(j < f){
            if(v[j] < v[j + 1]){
                j = j + 1;
            }
        }

        if(aux < v[j]){
            v[i] = v[j];
            i = j;
            j = 2 * i + 1;
        } else{
            j = f + 1;
        }
    }

    v[i] = aux;
}