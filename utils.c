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
            printf("\t%c", tab[i][j]);
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
        }
        
        // Copiar apenas TAM caracteres para o tabuleiro
        strncpy(tab[i], linha, TAM);
        tab[i][TAM-1] = '\0';  // Garantir terminação nula
    }
    return 1;  // Sucesso
}

int daPraMexer(const char m[TAM][TAM], int x1, int y1, int x2, int y2) {
    // Verificar se as coordenadas estão dentro dos limites
    if (x1 < 0 || x1 >= TAM || y1 < 0 || y1 >= TAM ||
        x2 < 0 || x2 >= TAM || y2 < 0 || y2 >= TAM) {
        return 0;
    }

    // Verificar se o movimento é válido
    if (m[x1][y1] != 'o' || m[x2][y2] != ' ') {
        return 0;
    }

    // Calcular a posição média
    int medX = (x1 + x2) / 2;
    int medY = (y1 + y2) / 2;

    // Verificar se há uma peça na posição média
    if (m[medX][medY] != 'o') {
        return 0;
    }

    // Verificar se o movimento é ortogonal e de duas casas
    if ((abs(x1 - x2) == 2 && y1 == y2) || (abs(y1 - y2) == 2 && x1 == x2)) {
        return 1;
    }

    return 0;
}