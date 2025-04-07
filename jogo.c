#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Lê um inteiro com verificação de entrada
int leInteiro(const char *mensagem) {
    int valor;
    char c;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%d", &valor) == 1) {
            while ((c = getchar()) != '\n' && c != EOF); // limpa buffer
            return valor;
        } else {
            printf("Entrada inválida. Tente novamente.\n");
            while ((c = getchar()) != '\n' && c != EOF); // limpa buffer
        }
    }
}

// Aloca memória para o tabuleiro
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

// Preenche o tabuleiro com letras aleatórias
void preencherTabuleiro(char **tabuleiro, int linhas, int colunas) {
    char letras[] = {'a', 'b', 'c', 'd', 'e'};
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            int indice = rand() % 5;
            tabuleiro[i][j] = letras[indice];
        }
    }
}

// Imprime o tabuleiro
void imprimirTabuleiro(char **tabuleiro, int linhas, int colunas) {
    printf("\nTabuleiro %dx%d:\n", linhas, colunas);
    printf("   ");
    for (int j = 0; j < colunas; j++)
        printf("%2d ", j);
    printf("\n");

    for (int i = 0; i < linhas; i++) {
        printf("%2d ", i);
        for (int j = 0; j < colunas; j++) {
            printf(" %c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Modifica uma casa do tabuleiro
void modificarCasa(char **tabuleiro, int linha, int coluna, char acao) {
    if (acao == 'm' && islower(tabuleiro[linha][coluna])) {
        tabuleiro[linha][coluna] = toupper(tabuleiro[linha][coluna]);
    } else if (acao == 'c') {
        tabuleiro[linha][coluna] = '#';
    }
}

// Libera a memória do tabuleiro
void liberarTabuleiro(char **tabuleiro, int linhas) {
    for (int i = 0; i < linhas; i++)
        free(tabuleiro[i]);
    free(tabuleiro);
}


//começo das novas funções adicionadas v1
void copiarTabuleiro(char **src, char **dest, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

#define MAX_HISTORY 100

typedef struct {
    char **tabuleiro;
    int linhas;
    int colunas;
} EstadoTabuleiro;

EstadoTabuleiro history[MAX_HISTORY];
int history_size = 0;

void salvarEstado(char **tabuleiro, int linhas, int colunas) {
    if (history_size < MAX_HISTORY) {
        // Cria uma cópia do tabuleiro atual
        history[history_size].tabuleiro = criarTabuleiro(linhas, colunas);
        copiarTabuleiro(tabuleiro, history[history_size].tabuleiro, linhas, colunas);
        history[history_size].linhas = linhas;
        history[history_size].colunas = colunas;
        history_size++;
    }
}

void desfazerUltimaJogada(char **tabuleiro, int *linhas, int *colunas) {
    if (history_size > 0) {
        history_size--;
        copiarTabuleiro(history[history_size].tabuleiro, tabuleiro, history[history_size].linhas, history[history_size].colunas);
        *linhas = history[history_size].linhas;
        *colunas = history[history_size].colunas;
        liberarTabuleiro(history[history_size].tabuleiro, history[history_size].linhas);
    } else {
        printf("Nenhuma jogada para desfazer.\n");
    }
}
//fim das novas funções adicionadas v1



// Função principal


int main() {
    char **tabuleiro = NULL;
    int linhas = 0, colunas = 0;
    int lin, col;
    char cond;
    int opcao;

    srand(time(NULL));

    do {
        printf("\nMenu\n");
        printf("1 - Jogar\n");
        printf("2 - Comandos\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        while (getchar() != '\n');

        if (opcao == 1) {
            linhas = leInteiro("Digite o número de linhas: ");
            colunas = leInteiro("Digite o número de colunas: ");

            tabuleiro = criarTabuleiro(linhas, colunas);
            if (!tabuleiro) {
                printf("Erro ao alocar memória.\n");
                return 1;
            }

            preencherTabuleiro(tabuleiro, linhas, colunas);
            

            int continuar = 1;
            do {
                imprimirTabuleiro(tabuleiro, linhas, colunas);
               
                printf("Informe a condição, linha e a coluna (ou 0 para sair): ");

                char entrada[20];
                fgets(entrada, sizeof(entrada), stdin);

                if (entrada[0] == '0' && entrada[1] == '\n') {
                    continuar = 0;
                } else if (entrada[0] == 'd' && entrada[1] == '\n') {
                    desfazerUltimaJogada(tabuleiro, &linhas, &colunas);
                } else {
                    if (sscanf(entrada, "%c %d %d", &cond, &lin, &col) != 3) {
                        printf("Entrada inválida! Tente de novo.\n");
                    } else if (lin >= 0 && lin < linhas && col >= 0 && col < colunas) {
                        salvarEstado(tabuleiro, linhas, colunas);
                        modificarCasa(tabuleiro, lin, col, cond);
                    } else {
                        printf("Posição inválida!\n");
                    }
                }
                
                
                printf("Histórico de jogadas: %d\n", history_size);
                
                
                
            } while (continuar);

            printf("\nEstado final do tabuleiro:\n");
            imprimirTabuleiro(tabuleiro, linhas, colunas);
            liberarTabuleiro(tabuleiro, linhas);
            tabuleiro = NULL;
        }
        
        if (opcao == 2) {
            printf("\ng - guardar jogo\n");
            printf("l - ler estado de jogo de um ficheiro\n");
            printf("b - substituir por maiúsculas\n");
            printf("r - substituir por #\n");
            printf("v - verificar o estado do jogo e apontar todas as restrições violadas\n");
            printf("a - ajuda\n");
            printf("d - desfazer a ultima jogada\n");
            printf("s - sair para o menu\n");
            printf("A - invocar o comando a enquanto o jogo sofrer alterações\n");
            printf("R - resolver jogo\n");
            getchar();
        }
        
        
    } while (opcao != 0);

    return 0;
}
