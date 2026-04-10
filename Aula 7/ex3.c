#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*
criar um vetor de 1000 posições, preencher com números aleatórios e ordenar usando o quicksort, mostrar o tempo de ordenação
*/

void quickSort(int *v, int inicio, int fim);
int particiona (int* v, int inicio, int final);

int main(){
    int vetor[1000];
    srand(time(NULL));
    clock_t start, end;
    double cpu_time_used;


    for(int i = 0; i < 1000; i++){
        vetor[i] = rand() % 1000;
    }

    start = clock();
    quickSort(vetor, 0, 999);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Vetor após a ordenação:\n");    
    for(int i = 0; i < 1000; i++){
        printf("%d ", vetor[i]);
    }

    printf("\n\n\n");
    printf("Tempo de ordenação: %f segundos\n", cpu_time_used);
    printf("\n\n");

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

//Resposta exercício 4:
// 5, 1, 2, 4, 3