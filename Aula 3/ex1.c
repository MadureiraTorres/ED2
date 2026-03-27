#include <stdio.h>
#include <stdlib.h>

void selectionSort(int *v, int n);

int main(){
    int tam = 10;
    int *v = (int*) malloc(tam * sizeof(int));

    for(int i = 0; i < tam; i++){
        v[i] = rand() % 100;
    }

    selectionSort(v, tam);

    for(int i = 0; i < tam; i++){
        printf("%d ", v[i]);
    }

    selectionSort(v, tam);

    free(v);

    return 0;
}

void selectionSort(int *v, int n){
    int i, j, min, aux;

    for(i = 0; i < n-1; i++){
        min = i;

        for(j = i+1; j < n; j++){
            if(v[j] < v[min]){
                aux = v[min];
                v[min] = v[j];
                v[j] = aux;
            }
        }
    }
}