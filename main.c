#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int main() {
    int opc = 0; // Inicialize a variável opc
    char nomeArq[100]; // Defina um tamanho fixo para o nome do arquivo
    char tab[TAMX][TAMY];

    while(opc != 3) {
        menu();

        printf("\nInforme a opcao: ");
        scanf("%d", &opc);

        switch(opc) {
            case 1:
                printf("\nInforme o nome do arquivo: ");
                scanf("%s", nomeArq);

                FILE *arq = fopen(nomeArq, "r");

                if(!arq) {
                    printf("\nHouve um erro na abertura do arquivo. Retornado para o menu...");
                } else {
                    printf("\nArquivo aberto com sucesso!");
                }

                prepararTabuleiro(tab, arq);

                break;

            case 2:
                imprimirMatriz(tab);
                break;
            
            case 3:
                printf("\nEncerrando...");
                break;
            default:
                printf("Opção inválida!");
                break;
        }
    }

    printf("\n");
    return 0;
}
