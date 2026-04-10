#include <stdio.h>
#include <stdlib.h>

//implementação do heap sort

void heapSort(int *v, int n);
void criaHeap(int *v, int i, int f);

int main(){
    int vetor[] = {23, 4, 67, -8, 90, 54, 21};
    int n = sizeof(vetor) / sizeof(vetor[0]);

    printf("Vetor original: ");
    for(int i = 0; i < n; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n\n");

    heapSort(vetor, n);

    printf("Vetor ordenado: ");
    for(int i = 0; i < n; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n\n");

    return 0;
}

void heapSort(int *v, int n){
    int i, aux;

    for(i = (n - 1)/2; i >= 1; i--){
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