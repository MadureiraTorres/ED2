#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int *v, int n);

int main(){
    int tam = 10;;
    srand(time(NULL));
    int *v = (int*) malloc(tam * sizeof(int));

    for(int i = 0; i < tam; i++){
        v[i] = rand() % 100;
    }

    printf("\nVetor: ");
    for(int i = 0; i < tam; i++){
        printf("%d ", v[i]);
    }

    clock_t start = clock();
    selectionSort(v, tam);
    clock_t end = clock();


    printf("\nVetor ordenado: ");
    for(int i = 0; i < tam; i++){
        printf("%d ", v[i]);
    }
    free(v);

    printf("\nTempo de ordenacao: %lf segundos\n", ((double)(end - start)) / CLOCKS_PER_SEC);

    return 0;
}

void selectionSort(int *v, int n){
    int i, j, max, aux;

    int trocas = 0;

    for(i = 0; i < n-1; i++){
        max = i;

        for(j = i+1; j < n; j++){
            if(v[j] > v[max]){  
                aux = v[max];
                v[max] = v[j];
                v[j] = aux;
                trocas++;
            }
        }
    }

    printf("\n\nNúmero de trocas: %d", trocas);
}