# include <stdio.h>
# define TAM 9
# define TAM_NOME 20

void menu();

void imprimirMatriz(const char tab[TAM][TAM]);

int prepararTabuleiro(char tab[TAM][TAM], FILE *arq);

int daPraMexer(char m[TAM][TAM], int x1, int y1, int x2, int y2);

int deuErrado(int m[TAM][TAM]);

