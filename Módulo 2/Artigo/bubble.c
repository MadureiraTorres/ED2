#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "benchmark.h"
#define TAM 3000000

void swap(int *a, int *b);
void bubbleSort(int *v, int n);

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
    bubbleSort(v, tam);
    clock_t end = clock();
    double tempo = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTempo de ordenacao: %lf segundos\n", tempo);
    salvarResultado(tam, "Bubble Sort", tempo);

    free(v);
    return 0;
}

void swap(int *a, int *b){ 
    int tmp = *a; 
    *a = *b; 
    *b = tmp;  
} 

void bubbleSort(int *v, int n){ 
    bool changed = true; 

    while(changed){ 
        changed = false;

        for(int i = 0; i < n-1; i++){ 
            if(v[i] > v[i+1]){ 
                swap(&v[i], &v[i+1]); 
                changed = true; 
            } 
        }  
    } 

}
