#include <stdio.h>
#include <stdlib.h>

void selectionSort(int *v, int n);

int main(){
    

    return 0;
}

void selectionSort(int *v, int n){
    int i, j, min, aus;

    for(i = 0; i < n-1; i++){
        min = i;

        for(j = i+1; j < n; j++){
            if(v[j] < v[min]){
                int aux = v[min];
                v[min] = v[j];
                v[j] = aux;
            }
        }
    }
}