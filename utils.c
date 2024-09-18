# include "utils.h"

void menu() {
    printf("\n\n=====RESTA UM=====");
    printf("\n1. Carregar tabuleiro");
    printf("\n2. Resolver");
    printf("\n3. Encerrar");
    printf("\n==================");
}

void imprimirMariz(char tab[TAM][TAM]) {
    for(int i = 0; i < TAM; i++) {
        printf("\n");
        for(int j = 0; j < TAM; j++) {
            printf("%c", tab[i][j]);
        }
    }
}

void prepararTabuleiro(char tab[TAM][TAM], FILE *arq) {
    for(int i = 0; i < TAM; i++) {
        fgets(tab[i], 20, arq);
    }
}