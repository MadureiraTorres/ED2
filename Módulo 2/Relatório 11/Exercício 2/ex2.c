#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool biscaBinária(char **v, char *elemento);

int main(){
    //lista com elementos
    char lista[4][20] = {"Edgar Codd", "arvore", "VonNeumann", "George Boole"};
    for(int i = 0; i < 4; i++){
        printf("%s\n", lista[i]);
    }

    //procurar elementos que existem na lista
    bool ret = biscaBinária(&lista, "Edgar Codd");
    printf("Busca por 'Edgar Codd': %s\n", ret ? "Encontrado" : "Não encontrado");

    ret = biscaBinária(&lista, "VonNeumann");
    printf("Busca por 'VonNeumann': %s\n", ret ? "Encontrado" : "Não encontrado");

    //procurar um elemento que não existe na lista
    ret = biscaBinária(&lista, "blablabla");
    printf("Busca por 'blablabla': %s\n", ret ? "Encontrado" : "Não encontrado");

    return 0;
}

bool biscaBinária(char *v[], char *elemento){
    int inicio = 0;
    int fim = sizeof(v) / sizeof(v[0]) - 1;

    while(inicio <= fim){
        int meio = inicio + (fim-inicio) / 2;
        if(strcmp(v[meio], elemento) == 0){
            return true;
        } else if(strcmp(v[meio], elemento) < 0){
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return false;
}

//pedir ajuda pro prof (segmentation fault)