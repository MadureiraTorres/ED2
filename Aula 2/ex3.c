#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
Idem ao exercício 2, mas que tenha opção de ordenação Ascendente e descendente. 
A opção de ascendente e descendente deve ser passada por parâmetro.
Também deve-se mostrar o número de trocas executadas até se ter o array ordenado.
*/

void swap(int *a, int *b);
void bubbleSort(int *v, int n, bool ascendente);

int main(){
    int vetor[] ={23, 4, 67, -8, 90, 54, 21, 0, -3, 15};
    int n = sizeof(vetor)/sizeof(vetor[0]);

    printf("Array original: ");
    for(int i = 0; i < n; i++){
        printf("%d ", vetor[i]);
    }
    
    bubbleSort(vetor, n, true);
    
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

void bubbleSort(int *v, int n, bool ascendente){
    bool changed = true;
    int trocas = 0;                        

    while(changed){
        changed = false;
        for(int i = 0; i < n-1; i++){
            if(ascendente ? v[i] > v[i+1] : v[i] < v[i+1]){
                swap(&v[i], &v[i+1]);
                changed = true;
                trocas++;                   
            }
        }
    }

    printf("\n\nNumero de trocas: %d", trocas); 
}