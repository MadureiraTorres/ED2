#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "benchmark.h"
#define TAM 3000000

void insertionSort(int *v, int n);

int main(){
    int tam = 2 * TAM;
    srand(time(NULL));
    int *v = (int*) malloc(tam * sizeof(int));

    if(v == NULL) {
        fprintf(stderr, "Erro ao alocar memoria\n");
        return 1;
    }

    printf("Gerando vetor de %d elementos...\n", tam);

    for(int i = 0; i < tam; i++){
        v[i] = rand() % TAM;
    }

    printf("\nVetor Gerado! Iniciando ordenacao...\n");

    clock_t start = clock();
    insertionSort(v, tam);
    clock_t end = clock();
    double tempo = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTempo de ordenacao: %lf segundos\n", tempo);
    salvarResultado(tam, "Insertion Sort", tempo);

    free(v);
    return 0;
}

void insertionSort(int *v, int n){
    int i, j, chosen;

    for(i = 1; i < n; i++){
        chosen = v[i];
        j = i - 1;
        
        while(j >= 0 && chosen < v[j]){
            v[j+1] = v[j];
            j = j - 1;
        }
        
        v[j + 1] = chosen;
    }
}