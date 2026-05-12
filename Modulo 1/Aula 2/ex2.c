#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
Utilizando a linguagem C, implementar um algoritmo de ordenação Buble sort, 
para ordenação ascendente de um array de 10 elementos,  
conforme slide Aula 2 disponível no moodle.
*/

void swap(int *a, int *b);
void bubbleSort(int *v, int n);

int main(){
    int vetor[] ={23, 4, 67, -8, 90, 54, 21, 0, -3, 15};
    int n = sizeof(vetor)/sizeof(vetor[0]);

    printf("Array original: ");
    for(int i = 0; i < n; i++){
        printf("%d ", vetor[i]);
    }
    
    bubbleSort(vetor, n);
    
    printf("\n\nArray ordenado: ");

    for(int i = 0; i < n; i++){
        printf("%d ", vetor[i]);
    }

    printf("\n");
    
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
