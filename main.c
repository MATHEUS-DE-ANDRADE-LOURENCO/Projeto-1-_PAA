#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define MAX_FILENAME 256

static void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static int ler_opcao(void) {
    int opcao;
    char input[16];
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return -1;
    }
    
    if (sscanf(input, "%d", &opcao) != 1) {
        return -1;
    }
    
    return opcao;
}

static FILE* abrir_arquivo(const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
    }
    return arquivo;
}

int main(void) {
    int opcao = 0;
    char nome_arquivo[MAX_FILENAME];
    char tabuleiro[TAM][TAM];
    FILE* arquivo = NULL;

    while (opcao != 3) {
        menu();

        printf("\nInforme a opcao: ");
        opcao = ler_opcao();

        switch (opcao) {
            case 1:
                printf("\nInforme o nome do arquivo: ");
                if (fgets(nome_arquivo, sizeof(nome_arquivo), stdin) == NULL) {
                    fprintf(stderr, "Erro ao ler o nome do arquivo.\n");
                    continue;
                }
                nome_arquivo[strcspn(nome_arquivo, "\n")] = '\0';  // Remove o '\n' do final

                arquivo = abrir_arquivo(nome_arquivo);
                if (arquivo == NULL) {
                    fprintf(stderr, "\nHouve um erro na abertura do arquivo. Retornando para o menu...\n");
                } else {
                    printf("\nArquivo aberto com sucesso!\n");
                    prepararTabuleiro(tabuleiro, arquivo);
                    fclose(arquivo);
                    arquivo = NULL;
                }
                break;

            case 2:
                imprimirMatriz(tabuleiro);
                break;
            
            case 3:
                printf("\nEncerrando...\n");
                break;

            default:
                printf("Opção inválida!\n");
                break;
        }
    }

    return EXIT_SUCCESS;
}