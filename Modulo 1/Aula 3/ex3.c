#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int *v, int n);

int main(){
    int tam = 10;
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
    int trocas = 0;

    for (int i = 0; i < n - 1; i++) {      
        int menor = i;

        for (int j = i + 1; j < n; j++){
            if (v[j] < v[menor]){
                menor = j;                       
            }
        }

        if (menor != i){
            int temp = v[menor];
            v[menor] = v[i];
            v[i] = temp;
            trocas++;
        }
    }
    
    printf("\n\nNúmero de trocas: %d", trocas);

}

/*
Resposta 4: 
A principal vantagem é que a quantidade de trocas é menor. Sendo ela menor por conta da troca ser feita apenas uma vez por iteração, 
enquanto no método de seleção tradicional, a troca ocorre toda vez que um elemento menor é encontrado durante a busca pelo menor elemento.
*/