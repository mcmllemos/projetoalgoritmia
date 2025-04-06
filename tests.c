/* #include <CUnit/CUnit.h>
#include <CUnit/Basic.h> */
#include <ctype.h>
#include <stdlib.h>
#include "jogo.h" // a gente vai mover os protótipos das funções para esse header

// Funções auxiliares para testes
void test_criar_e_liberar_tabuleiro() {
    char **tab = criarTabuleiro(3, 4);
    CU_ASSERT_PTR_NOT_NULL(tab);
    for (int i = 0; i < 3; i++)
        CU_ASSERT_PTR_NOT_NULL(tab[i]);
    liberarTabuleiro(tab, 3);
}

void test_preencher_tabuleiro() {
    char **tab = criarTabuleiro(2, 2);
    preencherTabuleiro(tab, 2, 2);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            CU_ASSERT_TRUE(tab[i][j] >= 'a' && tab[i][j] <= 'e');
    liberarTabuleiro(tab, 2);
}

void test_modificarCasa_maiuscula() {
    char **tab = criarTabuleiro(1, 1);
    tab[0][0] = 'a';
    modificarCasa(tab, 0, 0, 1);
    CU_ASSERT_EQUAL(tab[0][0], 'A');
    liberarTabuleiro(tab, 1);
}

void test_modificarCasa_riscar() {
    char **tab = criarTabuleiro(1, 1);
    tab[0][0] = 'b';
    modificarCasa(tab, 0, 0, 2);
    CU_ASSERT_EQUAL(tab[0][0], '#');
    liberarTabuleiro(tab, 1);
}

int call_tests() {
    srand(0); // determinismo nos testes

    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Testes do Jogo", 0, 0);

    CU_add_test(suite, "Criar e liberar tabuleiro", test_criar_e_liberar_tabuleiro);
    CU_add_test(suite, "Preencher tabuleiro", test_preencher_tabuleiro);
    CU_add_test(suite, "Modificar casa - maiúscula", test_modificarCasa_maiuscula);
    CU_add_test(suite, "Modificar casa - riscar", test_modificarCasa_riscar);

    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}