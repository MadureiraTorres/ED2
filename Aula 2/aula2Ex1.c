#include <stdio.h>
#include <stdlib.h>

/* 
Implementar uma busca linear que mostre a posição do elemento 4, considerando que
se repete 3 vezes.

chamar as funções de busca linear, busca ordenada e busca binária passando parâmetros
v, n e elem
v: vetor
n: tamanho do vetor
elem: elemento a se procurar
*/

int *buscaLinearRep(int *v, int n, int elem);
int buscaLinear(int *v, int n, int elem);


int main(){
    int tam = 10;
    int num;

    int random[] = {1, 25, 3, 30, 4, 27, 17, 4, 2, 4};
    
    printf("Digite um valor: ");
    scanf("%d", &num);

    int linear = buscaLinear(random, tam, num);
    if (linear == -1){
        printf("Valor %d nao encontrado por busca linear\n", num);
    }else if(num != 4){
        printf("Valor %d encontrado por busca linear, posicao %d\n", num, linear);
    }
    
    if(num == 4){
        int *posLinear = buscaLinearRep(random, tam, num); 

        for(int i = 0; i < 3; i++){
            printf("Valor %d encontrado por busca linear, posicao %d\n", num, posLinear[i]);
        }
    }


    return 0;
}

int *buscaLinearRep(int *v, int n, int elem){
    int *quantNum = (int*) malloc(3 * sizeof(int));

    int aux;

    for(int k = 0; k < 3; k++){
        quantNum[k] = 99;
    }

    for(int i = 0; i < n; i++){
        if(elem == v[i]){
            aux = i;
            for(int j = 0; j < 3; j++){
                if(quantNum[j] == 99){
                    quantNum[j] = aux;
                    break;
                }
            }
        }
    }

    return quantNum;
}

int buscaLinear(int *v, int n, int elem){
    for(int i = 0; i < n; i++){
        if(elem == v[i]){
            return i;
        }
    }

    return -1;
}