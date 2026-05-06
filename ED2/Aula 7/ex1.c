#include <stdio.h>
#include <stdlib.h>

/*
quicksort simples
*/

void quickSort(int *v, int inicio, int fim);
int particiona (int* v, int inicio, int final);

int main(){
    int vetor[] = {23, 4, 67, -8, 90, 54, 21};

    printf("Vetor antes da ordenação:\n");
    for(int i = 0; i < 7; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n\n");

    quickSort(vetor, 0, 6);

    printf("Vetor após a ordenação:\n");
    for(int i = 0; i < 7; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");

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