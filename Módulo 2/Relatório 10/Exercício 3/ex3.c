#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 100

FILE* abrirArquivo();
void imprimirArquivo(FILE *arq);
void escreverArquivo(FILE *arq, char *palavra);
void fecharArquivo(FILE *arq);

int main(){
    FILE *arq = abrirArquivo();
    char *palavra = (char*)calloc(TAM, sizeof(char));

    printf("Conteúdo do arquivo:\n");
    imprimirArquivo(arq);

    setbuf(stdin, NULL);
    setbuf(stdout, NULL);

    printf("\nDigite uma palavra para inserir no arquivo: ");
    fgets(palavra, TAM, stdin);
    palavra[strcspn(palavra, "\n")] = 0;
    setbuf(stdin, NULL);

    escreverArquivo(arq, palavra);
    fecharArquivo(arq);

    return 0;
}

FILE* abrirArquivo(){
    FILE *arq = fopen("arqmos.txt", "a+");
    if(arq == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    } else{
        printf("Arquivo aberto com sucesso!\n");
    }

    return arq;
}

void imprimirArquivo(FILE *arq){
    char buffer[TAM];
    size_t lidos;
    rewind(arq);
    while((lidos = fread(buffer, sizeof(char), TAM - 1, arq)) > 0){ 
        buffer[lidos] = '\0'; 
        printf("%s", buffer);
    }
}

void escreverArquivo(FILE *arq, char *palavra){
    size_t len = strlen(palavra);
    fwrite(palavra, sizeof(char), len, arq);
}

void fecharArquivo(FILE *arq){
    if(fclose(arq) == 0){
        printf("\nArquivo fechado com sucesso!\n");
    } else{
        printf("\nErro ao fechar o arquivo!\n");
    }
}