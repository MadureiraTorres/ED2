#include <stdio.h>
#include <stdlib.h>
#define NUM_PESSOAS 4

//struct
typedef struct p{
    char nome[30];
    int idade;
    float peso;
} Pessoa;

//cabeçalho de função
void escritaArq(Pessoa pessoas[]);
Pessoa leituraBusca();

int main(){
    Pessoa pessoas[NUM_PESSOAS] = {
        {"Rafael", 24, 90},
        {"Joice", 24, 60},
        {"Cristiano", 40, 81.8},
        {"Fallen", 36, 92.7}
    };
    
    escritaArq(pessoas);
    Pessoa pessoaEncontrada = leituraBusca();
    printf("Pessoa encontrada: %s\n", pessoaEncontrada.nome);
    
    return 0;
}

void escritaArq(Pessoa pessoas[]){
    FILE *arq = fopen("cadastro.bin", "wb");

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
}

Pessoa leituraBusca(){
    FILE *arq = fopen("cadastro.bin", "rb"); 
    Pessoa pessoasArq[NUM_PESSOAS];
    Pessoa pessoaBuscada;

    //leitura
    if(arq == NULL){
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }

    size_t elementosLidos = fread(pessoasArq, sizeof(Pessoa), NUM_PESSOAS, arq);

    if (elementosLidos != NUM_PESSOAS){
        printf("Erro ao ler do arquivo! Apenas %zu de %d elementos foram lidos.\n", elementosLidos, NUM_PESSOAS);
        fclose(arq);
        exit(1);
    }

    fclose(arq);

    //exibição
    for(int i = 0; i < NUM_PESSOAS; i++) {
        printf("Nome: %s | Idade: %d | Peso: %.2f\n", pessoasArq[i].nome, pessoasArq[i].idade, pessoasArq[i].peso);
    }

    //buscar a segunda pessoa do arquivo
    for(int i = 0; i < NUM_PESSOAS; i++) {
        pessoaBuscada = pessoasArq[1];
    }
    
    return pessoaBuscada;
}