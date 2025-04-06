#ifndef JOGO_H
#define JOGO_H

int leInteiro(const char *mensagem);
char **criarTabuleiro(int linhas, int colunas);
void preencherTabuleiro(char **tabuleiro, int linhas, int colunas);
void imprimirTabuleiro(char **tabuleiro, int linhas, int colunas);
void modificarCasa(char **tabuleiro, int linha, int coluna, int acao);
void liberarTabuleiro(char **tabuleiro, int linhas);

#endif
