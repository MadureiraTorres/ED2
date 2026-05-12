#include <stdio.h>
#include <stdlib.h>

typedef struct p{
    char nome[30];
    int idade;
    float peso;
} Pessoa;

int main(){
    FILE *arq;
    Pessoa pessoas[4] = {
        {"Rafael", 24, 90},
        {"Joice", 24, 60},
        {"Cristiano", 40, 81.8},
        {"Fallen", 36, 92.7}
    };

    arq = fopen("cadastro.txt", "wb");

    if(arq == NULL){
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }

    arq = fwrite(pessoas, sizeof(Pessoa), 4, arq);

    fclose(arq);
    
    return 0;
}