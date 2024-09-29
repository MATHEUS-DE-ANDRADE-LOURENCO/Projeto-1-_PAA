#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // Para abs()

#define MAX_LINE_LENGTH 20


void menu(void) {
    static const char *menu_text[] = {
        "\n\n",
        "╔══════════════════════════════╗",
        "║         ♜ RESTA UM ♜         ║",
        "╠══════════════════════════════╣",
        "║                              ║",
        "║   1. ▶ Carregar tabuleiro    ║",
        "║                              ║",
        "║   2. ▶ Resolver              ║",
        "║                              ║",
        "║   3. ▶ Encerrar              ║",
        "║                              ║",
        "╚══════════════════════════════╝"
    };

    for (size_t i = 0; i < sizeof(menu_text) / sizeof(menu_text[0]); i++) {
        puts(menu_text[i]);
    }
}

void imprimirMatriz(const char tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        putchar('\n');
        for (int j = 0; j < TAM; j++) {
            printf("%c ", tab[i][j]);
        }
    }
    putchar('\n');
}

int prepararTabuleiro(char tab[TAM][TAM], FILE *arq) {
    if (arq == NULL) {
        return 0;  // Falha: arquivo inválido
    }

    char linha[MAX_LINE_LENGTH];
    for (int i = 0; i < TAM; i++) {

        if (fgets(linha, sizeof(linha), arq) == NULL) {
            return 0;  // Falha: EOF ou erro de leitura
        }
        
        // Remover o caractere de nova linha, se presente
        size_t len = strlen(linha);
        if (len > 0 && linha[len-1] == '\n') {
            linha[len-1] = '\0';
            len--;
        }

        // Garantir que a linha tenha pelo menos TAM caracteres para copiar
        if (len < TAM && len > 0) {
            // Se a linha for menor que TAM, completa com espaços
            for (size_t j = len; j < TAM; j++) {
                linha[j] = ' ';  // Completa com espaços
            }
            linha[TAM] = '\0';
        }

        // Copiar TAM caracteres para o tabuleiro
        strncpy(tab[i], linha, TAM);
    }

    return 1;  // Sucesso
}

int daPraMexer(const char m[TAM][TAM], int x1, int y1, int x2, int y2) {
    // Verificar se as coordenadas estão dentro dos limites
    if (x2 < 0 || x2 >= TAM || y2 < 0 || y2 >= TAM) return 0;

    // Verificar se o movimento é válido
    if (m[x2][y2] != ' ') return 0;

    // Calcular a posição média
    int medX = (x1 + x2) / 2;
    int medY = (y1 + y2) / 2;

    // Verificar se há uma peça na posição média
    if (m[medX][medY] != 'o') return 0;

    // Sucesso
    return 1;
    
}

void mexer(char m[TAM][TAM], int x1, int y1, int x2, int y2, char jogadas[MAX_JOGADAS][TAM][TAM], int cont_jogadas) {
    int mediaX = (x1 + x2)/2;
    int mediaY = (y1 + y2)/2;
    
    m[x1][y1] = ' ';
    m[mediaX][mediaY] = ' ';
    m[x2][y2] = 'o';

    // Armazenar a jogada atual no histórico de jogadas
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            jogadas[cont_jogadas][i][j] = m[i][j];
        }
    }
}

void desfazerMovimento(char m[TAM][TAM], int x1, int y1, int x2, int y2) {
    int mediaX = (x1 + x2)/2;
    int mediaY = (y1 + y2)/2;
    
    m[x1][y1] = 'o';
    m[mediaX][mediaY] = 'o';
    m[x2][y2] = ' ';
}

int deuCerto(char m[TAM][TAM], int cont_jogadas, int cont_pecas) {
    return cont_pecas == 1 && cont_jogadas == 31 && m[4][4] == 'o';    
}

int restaUm(char m[TAM][TAM], int cont_jogadas, int cont_pecas, char jogadas[MAX_JOGADAS][TAM][TAM]) {
    if (deuCerto(m, cont_jogadas, cont_pecas)) {
        mostrarJogadas(jogadas, cont_jogadas);  // Mostra todas as jogadas
        return 1;
    } else {
        for(int i = 0; i < TAM; i++) {
            for(int j = 0; j < TAM; j++) {
                if(m[i][j] == 'o') {
                // Direita
                    if(daPraMexer(m, i, j, i + 2, j)) {
                        mexer(m, i, j, i + 2, j, jogadas, cont_jogadas);
                        if(restaUm(m, cont_jogadas + 1, cont_pecas - 1, jogadas)) return 1;
                        else desfazerMovimento(m, i, j, i + 2, j);
                    }
                    
                // Esquerda
                    if(daPraMexer(m, i, j, i - 2, j)) {
                        mexer(m, i, j, i - 2, j, jogadas, cont_jogadas);
                        if(restaUm(m, cont_jogadas + 1, cont_pecas - 1, jogadas)) return 1;
                        else desfazerMovimento(m, i, j, i - 2, j);
                    }
                    
                // Cima
                    if(daPraMexer(m, i, j, i, j + 2)) {
                        mexer(m, i, j, i, j + 2, jogadas, cont_jogadas);
                        if(restaUm(m, cont_jogadas + 1, cont_pecas - 1, jogadas)) return 1;
                        else desfazerMovimento(m, i, j, i, j + 2);
                    }
                // Baixo
                    if(daPraMexer(m, i, j, i, j - 2)) {
                        mexer(m, i, j, i, j - 2, jogadas, cont_jogadas);
                        if (restaUm(m, cont_jogadas + 1, cont_pecas - 1, jogadas)) return 1;
                        else desfazerMovimento(m, i, j, i, j-2);
                    }
                }
            }
        }
    }
    
    return 0;
}

void mostrarJogadas(char jogadas[MAX_JOGADAS][TAM][TAM], int cont_jogadas) {
    printf("Mostrando todas as jogadas realizadas:\n");
    for (int i = 0; i <= cont_jogadas; i++) {
        printf("\nJogada %d:\n", i + 1);
        imprimirMatriz(jogadas[i]);
    }
}
