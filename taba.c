
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

void salvarTabuleiroComNome(char **tabuleiro, int linhas, int colunas);

int leInteiro(const char *mensagem) {
    int valor;
    char c;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%d", &valor) == 1) {
            while ((c = getchar()) != '\n' && c != EOF);
            return valor;
        } else {
            printf("Entrada inválida. Tente novamente.\n");
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}

char **criarTabuleiro(int linhas, int colunas) {
    char **tabuleiro = malloc(linhas * sizeof(char *));
    if (!tabuleiro) return NULL;
    for (int i = 0; i < linhas; i++) {
        tabuleiro[i] = malloc(colunas * sizeof(char));
        if (!tabuleiro[i]) {
            for (int j = 0; j < i; j++) free(tabuleiro[j]);
            free(tabuleiro);
            return NULL;
        }
    }
    return tabuleiro;
}

void preencherTabuleiro(char **tabuleiro, int linhas, int colunas) {
    char letras[] = {'a', 'b', 'c', 'd', 'e'};
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            int indice = rand() % 5;
            tabuleiro[i][j] = letras[indice];
        }
    }
}

void imprimirTabuleiro(char **tabuleiro, int linhas, int colunas) {
    printf("\nTabuleiro %dx%d:\n", linhas, colunas);
    printf("   ");
    for (int j = 0; j < colunas; j++) printf("%2d ", j);
    printf("\n");
    for (int i = 0; i < linhas; i++) {
        printf("%2d ", i);
        for (int j = 0; j < colunas; j++) {
            printf(" %c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void modificarCasa(char **tabuleiro, int linha, int coluna, int acao) {
    if (acao == 1 && islower(tabuleiro[linha][coluna])) {
        tabuleiro[linha][coluna] = toupper(tabuleiro[linha][coluna]);
    } else if (acao == 2) {
        tabuleiro[linha][coluna] = '#';
    }
}

void liberarTabuleiro(char **tabuleiro, int linhas) {
    for (int i = 0; i < linhas; i++) free(tabuleiro[i]);
    free(tabuleiro);
}

void copiarTabuleiro(char **destino, char **origem, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++)
            destino[i][j] = origem[i][j];
}

void salvarTabuleiroParaFicheiro(char **tabuleiro, int linhas, int colunas) {
    FILE *fp = fopen("tabuleiro_salvo.txt", "w");
    if (!fp) {
        printf("Erro ao salvar o tabuleiro.\n");
        return;
    }
    fprintf(fp, "%d %d\n", linhas, colunas);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fprintf(fp, "%c", tabuleiro[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    printf("Jogo salvo com sucesso em 'tabuleiro_salvo.txt'.\n");
}

void salvarTabuleiroComNome(char **tabuleiro, int linhas, int colunas) {
    char nome[100];
    printf("Deseja guardar o jogo com um nome específico? (s/n): ");
    char resp;
    scanf(" %c", &resp);
    getchar();
    if (resp == 's' || resp == 'S') {
        printf("Digite o nome do ficheiro (sem extensão): ");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = 0;
        if (strcmp(nome, "saves") == 0) {
            printf("Erro: 'saves' é o nome da pasta. Escolha outro nome!\n");
            return;
        }
        char caminho[150];
        snprintf(caminho, sizeof(caminho), "saves/%s.txt", nome);
        FILE *fp = fopen(caminho, "w");
        if (!fp) {
            printf("Erro ao guardar o ficheiro '%s'.\n", caminho);
            return;
        }
        fprintf(fp, "%d %d\n", linhas, colunas);
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                fprintf(fp, "%c", tabuleiro[i][j]);
            }
            fprintf(fp, "\n");
        }
        fclose(fp);
        printf("Jogo guardado como '%s'.\n", caminho);
    } else {
        salvarTabuleiroParaFicheiro(tabuleiro, linhas, colunas);
    }
}

void verificaRegras(char **tabuleiro, int l, int c) {
    int i, j, k;
    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            for (k = j + 1; k < c; k++) {
                if (tabuleiro[i][j] == '#' && tabuleiro[i][k] == '#') {
                    printf("Repetição '#' na linha %d nas colunas %d e %d\n", i, j, k);
                    return;
                }
            }
        }
    }
    for (j = 0; j < c; j++) {
        for (i = 0; i < l - 1; i++) {
            if (tabuleiro[i][j] == '#' && tabuleiro[i + 1][j] == '#') {
                 printf("Repetição '#' na coluna %d nas linhas %d e %d\n", j, i, i + 1);
                 return;
            }
        }
    }
}


int main(void) {
    mkdir("saves", 0777);
    int linhas = 0, colunas = 0;
    char **tabuleiro = NULL;
    char **tabuleiroAnterior = NULL;
    int opcao = -1;

    while (opcao != 1 && opcao != 2 && opcao != 0) {
        printf("=====================================\n");
        printf("            MENU INICIAL             \n");
        printf("=====================================\n");
        printf("1 - Novo jogo\n");
        printf("2 - Carregar jogo anterior\n");
        printf("0 - Sair\n");
        printf("=====================================\n");
        opcao = leInteiro("Escolha a opção: ");
    }

    if (opcao == 0) {
        printf("A sair do jogo...\n");
        return 0;
    }

    if (opcao == 2) {
        DIR *dir;
        struct dirent *entry;
        char ficheiros[100][100];
        int total = 0;

        dir = opendir("saves");
        if (!dir) {
            printf("Erro ao abrir a pasta de saves. Um novo jogo será iniciado.\n");
            opcao = 1;
        } else {
            printf("=====================================\n");
            printf("         JOGOS DISPONÍVEIS           \n");
            printf("=====================================\n");

            while ((entry = readdir(dir)) != NULL) {
                if (strstr(entry->d_name, ".txt")) {
                    printf("%d - %s\n", total + 1, entry->d_name);
                    strcpy(ficheiros[total], entry->d_name);
                    total++;
                }
            }
            closedir(dir);

            if (total == 0) {
                printf("Nenhum jogo encontrado. Um novo será iniciado.\n");
                opcao = 1;
            } else {
                int escolha = -1;
                while (escolha < 0 || escolha > total) {
                    escolha = leInteiro("Escolha o número do jogo a carregar (0 para cancelar): ");
                }

                if (escolha == 0) {
                    printf("A carregar novo jogo em vez de save...\n");
                    opcao = 1;
                } else {
                    char caminho[150];
                    snprintf(caminho, sizeof(caminho), "saves/%s", ficheiros[escolha - 1]);

                    FILE *fp = fopen(caminho, "r");
                    if (!fp) {
                        printf("Erro ao abrir ficheiro '%s'. Novo jogo será iniciado.\n", caminho);
                        opcao = 1;
                    } else {
                        fscanf(fp, "%d %d\n", &linhas, &colunas);
                        tabuleiro = criarTabuleiro(linhas, colunas);
                        tabuleiroAnterior = criarTabuleiro(linhas, colunas);
                        for (int i = 0; i < linhas; i++) {
                            for (int j = 0; j < colunas; j++) {
                                tabuleiro[i][j] = fgetc(fp);
                            }
                            fgetc(fp);
                        }
                        fclose(fp);
                        copiarTabuleiro(tabuleiroAnterior, tabuleiro, linhas, colunas);
                    }
                }
            }
        }
    }

    if (opcao == 1) {
        linhas = leInteiro("Digite o número de linhas: ");
        colunas = leInteiro("Digite o número de colunas: ");
        tabuleiro = criarTabuleiro(linhas, colunas);
        tabuleiroAnterior = criarTabuleiro(linhas, colunas);
        if (!tabuleiro || !tabuleiroAnterior) {
            printf("Erro ao alocar memória.\n");
            return 1;
        }
        preencherTabuleiro(tabuleiro, linhas, colunas);
        copiarTabuleiro(tabuleiroAnterior, tabuleiro, linhas, colunas);
    }

    int sair = 0;
    int primeiraVez = 1;
    char linhaInput[100];

    while (!sair) {
        imprimirTabuleiro(tabuleiro, linhas, colunas);
        if (primeiraVez) {
            printf("Menu:\n");
            printf("O 'b' serve para indicar letras maiúsculas.\n");
            printf("O 'r' serve para marcar espaços em branco.\n");
        }

        printf("Escolha a ação no formato b ou r, linha, coluna | v para ver os erros | 0 para sair | d para voltar atrás | s para salvar:\n");

        if (fgets(linhaInput, sizeof(linhaInput), stdin) != NULL) {
            linhaInput[strcspn(linhaInput, "\n")] = 0;

            if (strcmp(linhaInput, "0") == 0) {
                sair = 1;
            } else if (strcmp(linhaInput, "d") == 0 || strcmp(linhaInput, "D") == 0) {
                copiarTabuleiro(tabuleiro, tabuleiroAnterior, linhas, colunas);
                printf("\nÚltima jogada anulada.\n");
                
            } else if (strcmp(linhaInput, "v") == 0 || strcmp(linhaInput, "V") == 0) {
                verificaRegras(tabuleiro, linhas, colunas);
                
            } else if (strcmp(linhaInput, "s") == 0 || strcmp(linhaInput, "S") == 0) {
                salvarTabuleiroComNome(tabuleiro, linhas, colunas);
            } else {
                char acao;
                int lin, col;
                int res = sscanf(linhaInput, " %c %d %d", &acao, &lin, &col);

                if (res == 3) {
                    if (lin >= 0 && lin < linhas && col >= 0 && col < colunas) {
                        copiarTabuleiro(tabuleiroAnterior, tabuleiro, linhas, colunas);
                        if (acao == 'b') {
                            modificarCasa(tabuleiro, lin, col, 1);
                            primeiraVez = 0;
                        } else if (acao == 'r') {
                            modificarCasa(tabuleiro, lin, col, 2);
                            primeiraVez = 0;
                        } else {
                            printf("Ação inválida!\n");
                        }
                    } else {
                        printf("Posição inválida!\n");
                    }
                } else {
                    printf("Formato inválido! Use: M linha coluna ou # linha coluna\n");
                }
            }
        } else {
            printf("Erro na leitura!\n");
            sair = 1;
        }
    }

    printf("\nEstado final do tabuleiro:\n");
    imprimirTabuleiro(tabuleiro, linhas, colunas);
    liberarTabuleiro(tabuleiro, linhas);
    liberarTabuleiro(tabuleiroAnterior, linhas);
    return 0;
}