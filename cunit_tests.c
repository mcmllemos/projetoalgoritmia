#include "cunit/includes/CUnit.h"
#include "cunit/includes/Basic.h"
#include "jogo.h"

void test_criar_e_liberar_tabuleiro(void) {
    char **tab = criarTabuleiro(3, 4);
    CU_ASSERT_PTR_NOT_NULL(tab);
    for (int i = 0; i < 3; i++)
        CU_ASSERT_PTR_NOT_NULL(tab[i]);
    liberarTabuleiro(tab, 3);
}

void test_preencher_tabuleiro(void) {
    char **tab = criarTabuleiro(2, 2);
    preencherTabuleiro(tab, 2, 2);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            CU_ASSERT_TRUE(tab[i][j] >= 'a' && tab[i][j] <= 'e');
    liberarTabuleiro(tab, 2);
}

void test_modificarCasa_maiuscula(void) {
    char **tab = criarTabuleiro(1, 1);
    tab[0][0] = 'a';
    modificarCasa(tab, 0, 0, 1);
    CU_ASSERT_EQUAL(tab[0][0], 'A');
    liberarTabuleiro(tab, 1);
}

void test_modificarCasa_riscar(void) {
    char **tab = criarTabuleiro(1, 1);
    tab[0][0] = 'b';
    modificarCasa(tab, 0, 0, 2);
    CU_ASSERT_EQUAL(tab[0][0], '#');
    liberarTabuleiro(tab, 1);
}

int call_tests(void){

    CU_pSuite pSuite = NULL;

    if(CU_initialize_registry() != CUE_SUCCESS){
        return CU_get_error();
    }

    pSuite = CU_add_suite("Testes Jogo", 0, 0);

    if(CU_add_test(pSuite, "Teste criação tabuleiro", test_criar_e_liberar_tabuleiro) == NULL){
        return CU_get_error();
    }
    if(CU_add_test(pSuite, "Teste preencher tabuleiro", test_preencher_tabuleiro) == NULL){
        return CU_get_error();
    }
    if(CU_add_test(pSuite, "Teste modificar - Maiuscula", test_modificarCasa_maiuscula) == NULL){
        return CU_get_error();
    }
    if(CU_add_test(pSuite, "Teste modificar - Riscar", test_modificarCasa_riscar) == NULL){
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CUE_SUCCESS;
}
