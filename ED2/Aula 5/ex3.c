#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//implementar com um vetor de 100 elementos aleatórios e contar o tempo

void mergeSort(int *v, int inicio, int fim);
void merge(int *v, int inicio, int meio, int fim);

int main(){
    int vetor[100];
    int n = sizeof(vetor) / sizeof(vetor[0]);

    srand(time(NULL));
    for(int i = 0; i < n; i++){
        vetor[i] = rand() % 1000; //gerar números aleatórios entre 0 e 999
    }

    printf("Vetor original: ");
    for(int i = 0; i < n; i++){
        printf("%d ", vetor[i]);
    }

    printf("\n\n");

    clock_t start = clock();
    mergeSort(vetor, 0, n - 1);
    clock_t end = clock();

    printf("Vetor ordenado: ");
    for(int i = 0; i < n; i++){
        printf("%d ", vetor[i]);
    }

    printf("\n\nTempo de execução: %f segundos\n", ((double)(end - start)) / CLOCKS_PER_SEC);

    return 0;
}

void mergeSort(int *v, int inicio, int fim){
    int meio;

    if(inicio < fim){
        meio = floor((inicio + fim) / 2);
        mergeSort(v, inicio, meio);
        mergeSort(v, meio + 1, fim);
        merge(v, inicio, meio, fim);
    }
}

void merge(int *v, int inicio, int meio, int fim){
    int *temp, p1, p2, tamanho, i, j, k;
    int fim1 = 0, fim2 = 0;
    tamanho = fim - inicio + 1;
    p1 = inicio;
    p2 = meio + 1;
    temp = (int *) malloc(tamanho * sizeof(int));

    if(temp != NULL){
        for(i = 0; i < tamanho; i++){
            if(!fim1 && !fim2){
                if(v[p1] < v[p2])
                    temp[i] = v[p1++];
                else
                    temp[i] = v[p2++];

                if(p1 > meio) fim1 = 1;
                if(p2 > fim) fim2 = 1;
            } else{
                if(!fim1)
                    temp[i] = v[p1++];
                else
                    temp[i] = v[p2++];    
            }    
        }

        for(j = 0, k = inicio; j < tamanho; j++, k++){
                v[k] = temp[j];
        }
    }   

    free(temp);
}

//resposta ex 4: MergeSort é um algoritmo de ordenação estável, preservando a ordem relativa de elementos iguais.

//resposta ex 5: Errado.