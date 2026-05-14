#include <stdio.h>
#include <stdlib.h>

#define NUM_PESSOAS 4

typedef struct p{
    char nome[30];
    int idade;
    float peso;
} Pessoa;

int main(){
    FILE *arq;
    Pessoa pessoas[NUM_PESSOAS] = {
        {"Rafael", 24, 90},
        {"Joice", 24, 60},
        {"Cristiano", 40, 81.8},
        {"Fallen", 36, 92.7}
    };

    arq = fopen("cadastro.txt", "w");

    if(arq == NULL){
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }

    size_t elementosEscritos = fwrite(pessoas, sizeof(Pessoa), NUM_PESSOAS, arq);
    if (elementosEscritos != NUM_PESSOAS) {
        printf("Erro ao escrever no arquivo! Apenas %zu de %d elementos foram escritos.\n", elementosEscritos, NUM_PESSOAS);
        fclose(arq);
        exit(1);
    }

    fclose(arq);
    
    return 0;
}