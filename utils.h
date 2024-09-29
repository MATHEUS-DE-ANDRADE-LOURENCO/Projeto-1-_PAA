# include <stdio.h>
# define TAM 9
# define TAM_NOME 20
#define MAX_JOGADAS 31
#define MAX_FILENAME 256

void menu();

void imprimirMatriz(const char tab[TAM][TAM]);

int prepararTabuleiro(char tab[TAM][TAM], FILE *arq);

int daPraMexer(const char m[TAM][TAM], int x1, int y1, int x2, int y2);

void mexer(char m[TAM][TAM], int x1, int y1, int x2, int y2, char jogadas[MAX_JOGADAS][TAM][TAM], int cont_jogadas);

void desfazerMovimento(char m[TAM][TAM], int x1, int y1, int x2, int y2);

int deuCerto(char m[TAM][TAM], int cont_jogadas, int cont_pecas);

int restaUm(char m[TAM][TAM], int cont_jogadas, int cont_pecas, char jogadas[MAX_JOGADAS][TAM][TAM]);

void mostrarJogadas(char jogadas[MAX_JOGADAS][TAM][TAM], int cont_jogadas);