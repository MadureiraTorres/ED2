#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//cabeçalho de funções
FILE* abrirArquivo();
void imprimirArquivo(FILE *arq);
void escreverArquivo(FILE *arq, char *palavra);
void fecharArquivo(FILE *arq);

int main(){
    FILE *arq = abrirArquivo();
    char *palavra = (char*)calloc(100, sizeof(char));

    printf("Conteúdo do arquivo:\n");
    imprimirArquivo(arq);

    setbuf(stdin, NULL);

    printf("\nDigite uma palavra para inserir no arquivo: ");
    fgets(palavra, sizeof(palavra), stdin);
    palavra[strcspn(palavra, "\n")] = 0;
    setbuf(stdin, NULL);
    escreverArquivo(arq, palavra);

    printf("Conteúdo do arquivo:\n");
    imprimirArquivo(arq);

    fecharArquivo(arq);

    return 0;
}

FILE* abrirArquivo(){
    FILE *arq = fopen("arqmos.txt", "r");
    if(arq == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    } else{
        printf("Arquivo aberto com sucesso!\n");
    }

    return arq;
}

void imprimirArquivo(FILE *arq){
    char ch;
    while((ch = fgetc(arq)) != EOF){
        putchar(ch);
    }
    rewind(arq);
}

void escreverArquivo(FILE *arq, char *palavra){
    for(int i = 0; palavra[i] != '\0'; i++){
        fputc(palavra[i], arq);
    }
}

void fecharArquivo(FILE *arq){
    if(fclose(arq) == 0){
        printf("\nArquivo fechado com sucesso!\n");
    } else{
        printf("\nErro ao fechar o arquivo!\n");
    }
}