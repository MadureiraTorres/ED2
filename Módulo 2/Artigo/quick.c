#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "benchmark.h"
#define TAM 3000000

void quickSort(int *v, int inicio, int fim);
int particiona (int* v, int inicio, int final);

int main(){
    int tam = TAM;
    srand(time(NULL));
    int *v = (int*) malloc(tam * sizeof(int));

    if(v == NULL) {
        fprintf(stderr, "Erro ao alocar memoria\n");
        return 1;
    }

    for(int i = 0; i < tam; i++){
        v[i] = rand() % TAM;
    }

    clock_t start = clock();
    quickSort(v, 0, tam - 1);
    clock_t end = clock();
    double tempo = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTempo de ordenacao: %lf segundos\n", tempo);
    salvarResultado(tam, "Quick Sort", tempo);

    free(v);
    return 0;
}

void quickSort(int *v, int inicio, int fim){
    int pivo;

    if(fim > inicio){
        pivo = particiona(v, inicio, fim);
        quickSort(v, inicio, pivo - 1);
        quickSort(v, pivo + 1, fim);
    }
}

int particiona (int* v, int inicio, int final){
    int esq, dir, pivo, aux;
    esq = inicio;
    dir = final;
    pivo = v[inicio];

    while(esq < dir){
        while(esq <= final && v[esq] <= pivo){
            esq++;
        }

        while(dir >= 0 && v[dir] > pivo){
            dir--;
        }

        if(esq < dir){
            aux = v[esq];
            v[esq] = v[dir];
            v[dir] = aux;
        }
    }

    v[inicio] = v[dir];
    v[dir] = pivo;
    return dir;
}