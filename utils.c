# include "utils.h"

void menu() {
    printf("\n\n");
    printf("╔══════════════════════════════╗\n");
    printf("║         ♜ RESTA UM ♜         ║\n");
    printf("╠══════════════════════════════╣\n");
    printf("║                              ║\n");
    printf("║   1. ▶ Carregar tabuleiro    ║\n");
    printf("║                              ║\n");
    printf("║   2. ▶ Resolver              ║\n");
    printf("║                              ║\n");
    printf("║   3. ▶ Encerrar              ║\n");
    printf("║                              ║\n");
    printf("╚══════════════════════════════╝\n");
}

void imprimirMatriz(char tab[TAM][TAM]) {
    for(int i = 0; i < TAM; i++) {
        printf("\n");
        for(int j = 0; j < TAM; j++) {
            printf("\t%c", tab[i][j]);
        }
    }
}

void prepararTabuleiro(char tab[TAM][TAM], FILE *arq) {
    for(int i = 0; i < TAM; i++) {
        fgets(tab[i], 20, arq);
    }
}

int daPraMexer(char m[TAM][TAM], int x1, int y1, int x2, int y2) {

    // Indica se o movimento sairá da matriz
        // Se x2 ou y2 exceder o tamanho da matriz (8)
        if(x2 > TAM -1 || y2 > TAM-1 || x2 < 0 || y2  < 0) {
            return 0;
        }

    // Indica se o movimento é válido
        // Se m[x1][y1] não é peça, e m[x2][y2] não é espaço vazio
        if (m[x1][y1] != 'o' || m[x2][y2]!= ' ') {
            return 0;
        }
        // Declarar média entre x1 x2 e y1 y2
        int medX = (x1 + x2) / 2;
        int medY = (y1 + y2) / 2;
        // Se m[medX][medY] não for peça

        if (m[x1][y1] != 'o'){
            return 0;
        }

        
        if (m[x1][y1] != '#'){
            return 0;
        }

    return 1;

}

int deuErrado(int m[TAM][TAM]) {
	int v[2] = {2, -2};
	
	for(int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			// Da pra mexer a peça pra esquerda?
			if(daPraMexer(m, i, j, i + 2, j)) return 0;
			
			// Da pra mexer a peça pra direita?
			if(daPraMexer(m, i, j, i - 2, j)) return 0;
			
			// Da pra mexer a peça pra cima?
			if(daPraMexer(m, i, j, i, j + 2)) return 0;
			
			// Da pra mexer a peça pra baixo?
			if(daPraMexer(m, i, j, i, j - 2)) return 0;
		}
	}
	
	return 1;
}


