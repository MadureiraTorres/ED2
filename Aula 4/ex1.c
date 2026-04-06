#include <stdio.h>
#include <stdlib.h>

/*
Utilizando a linguagem C, implemente a versão básica do algoritmo Insertion Sort. 
Deve ser mostrado ao final o vetor ordenado e também a contagem do  número 
total de trocas efetuadas. 
*/

void insertionSort(int *v, int n);

int main(){
    int vetor[] = {23, 4, 67, -8, 90, 54, 21};
    
    printf("Vetor desordenado: ");
    
    for(int i = 0; i < 7; i++){
        printf("%d ", vetor[i]);
    }
    
    insertionSort(vetor, 7);
    
    printf("\n\nVetor ordenado: ");
    
    for(int i = 0; i < 7; i++){
        printf("%d ", vetor[i]);
    }
    
    return 0;
}

void insertionSort(int *v, int n){
    int i, j, chosen;
    for(i = 1; i < n; i++){
        chosen = v[i];
        
        while(j >= 0 && chosen < v[j]){
            v[j+1] = v[j];
            j = j - 1;
        }
        
        v[j+1] = chosen;
    }
}