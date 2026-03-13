#include <stdio.h>
#include <stdlib.h>

/*
implementar:
a) Busca Linear
b) Busca Ordenada 
c) Busca Binária
*/

//cabeçalho de funções
int buscaLinear(int *v, int n, int elem);
int buscaOrdenada(int *v, int n, int elem);
int buscaBinaria(int *v, int n, int elem);

int main(){
    int tam = 10;
    int num;
    int linear;
    int ord;
    int bin;

    //Vetor desordenado
    int random[] = {1, 25, 3, 30, 41, 27, 17, 4, 2, 5};

    // Vetor Ordenado
    int sorted[] = {1, 2, 4, 5, 17, 25, 27, 30, 31, 41};

    printf("\nDigite um valor: ");
    scanf("%d",&num);
    setbuf(stdin, NULL);

    printf("\n\n");

    //busca no vetor desordenado
    linear = buscaLinear(random, tam, num);
    printf("Valor %d encontrado por busca linear, posicao %d\n", num, linear);

    ord = buscaOrdenada(sorted, tam, num);
    printf("Valor %d encontrado por busca ordenada, posicao %d\n", num, ord);

    bin = buscaBinaria(sorted, tam, num);
    printf("Valor %d encontrado por busca binaria, posicao %d\n", num, bin);
    
    return 0;
}

//busca linear
int buscaLinear(int *v, int n, int elem){
    for(int i = 0; i < n; i++){
        if(elem == v[i]){
            return i;
        }
    }

    return -1;
}

//busca ordenada
int buscaOrdenada(int *v, int n, int elem){
    for(int i = 0; i < n; i++){
        if(elem == v[i]){
            return i;
        }

        if(v[i] > elem){
            return -1;
        }
    }

    return -1;
}

//busca binária
int buscaBinaria(int *v, int n, int elem){
    int inicio = 0;
    int fim = n - 1;
    int meio;

    while(inicio <= fim){
        meio = (inicio + fim) / 2;

        if(v[meio] == elem){
            return meio;
        } else if(elem < v[meio]){
            fim = meio - 1;
        } else{
            inicio = meio + 1;
        }
    }

    return -1;
}
