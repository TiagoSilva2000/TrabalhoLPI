#include <stdio.h>
#include "../includes/interface.h"

void mainInterface (void)
{
    printf("1 - Cadastrar Produto\n");
    printf("2 - Vender\n");
    printf("3 - Gerar Relatorio de Receita\n");
    printf("4 - Destaques\n");
    printf("5 - Atualizar Preco\n");
    printf("985 - Sair\n");

}

void highlightsInterface (void)
{
    
    printf("1 - Produto Mais Vendido\n");
    printf("2 - Cliente Mais Frequente\n");
    printf("3 - Cliente que Mais Comprou\n");
    printf("985 - Sair\n");

}

void prodQntInterface (void)
{

    printf("======================================\n");
    printf("=                                    =\n");
    printf("=                                    =\n");
    printf("=   DIGITE A QUANTIDADE DO PRODUTO   =\n");
    printf("=                                    =\n");
    printf("=                                    =\n");
    printf("=      Pressione 0 para Cancelar     =\n");
    printf("======================================\n");

}

void prodCodeInterface (void)
{

    printf("======================================\n");
    printf("=                                    =\n");
    printf("=     DIGITE O CODIGO DO PRODUTO     =\n");
    printf("=            0 para Sair             =\n");
    printf("======================================\n");

}

void sellInterface (void)
{

    printf("======================================\n");
    printf("=                                    =\n");
    printf("=           MENU DE VENDAS           =\n");
    printf("=                                    =\n");
    printf("= - SELECIONE UMA OPCAO              =\n");
    printf("=                                    =\n");
    printf("= 1 - MOSTRAR O CARRINHO             =\n");
    printf("= 2 - ADICIONAR PRODUTO AO CARRINHO  =\n");
    printf("= 3 - REMOVER PRODUTO DO CARRINHO    =\n");
    printf("= 0 - FINALIZAR A COMPRA             =\n");
    printf("=                                    =\n");
    printf("======================================\n");

}