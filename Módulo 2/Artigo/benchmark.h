#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stdio.h>

void salvarResultado(int tam, const char *algoritmo, double tempo){
    FILE *f = fopen("resultados.csv", "a");
    if (!f){
        printf("Erro ao abrir o arquivo CSV!\n");
        return;
    }

    // Cria cabeçalho se o arquivo estiver vazio
    fseek(f, 0, SEEK_END);
    if (ftell(f) == 0) {
        fprintf(f, "tamanho|algoritmo|tempo(s)\n");
    }

    fprintf(f, "%d|%s|%.6f\n", tam, algoritmo, tempo);
    fclose(f);
}

#endif