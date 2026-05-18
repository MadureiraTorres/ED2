#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool buscaBinaria(char *v[], int tamanho, char *elemento);

int main(){
    char *lista[] = {"Edgar Codd", "George Boole", "VonNeumann", "arvore"};
    int tamanho = sizeof(lista) / sizeof(lista[0]); 

    for(int i = 0; i < tamanho; i++){
        printf("%s\n", lista[i]);
    }

    bool ret = buscaBinaria(lista, tamanho, "Edgar Codd");
    printf("Busca por 'Edgar Codd': %s\n", ret ? "Encontrado" : "Não encontrado");

    ret = buscaBinaria(lista, tamanho, "VonNeumann");
    printf("Busca por 'VonNeumann': %s\n", ret ? "Encontrado" : "Não encontrado");

    ret = buscaBinaria(lista, tamanho, "blablabla");
    printf("Busca por 'blablabla': %s\n", ret ? "Encontrado" : "Não encontrado");

    return 0;
}

bool buscaBinaria(char *v[], int tamanho, char *elemento){
    int inicio = 0;
    int fim = tamanho - 1; 

    while(inicio <= fim){
        int meio = inicio + (fim - inicio) / 2;
        int cmp = strcmp(v[meio], elemento);
        if(cmp == 0){
            return true;
        } else if(cmp < 0){
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return false;
}
