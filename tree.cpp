#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *left, *right;
} Node;


typedef struct head
{
    int nElem;
    Node** root;

} Tree;

Tree quick_create (void)
{
    Tree new_root;

    new_root.nElem = 0;
    new_root.root = NULL;


    return new_root;
}

int main (void)
{
    Tree clients = quick_create();




    return 0;
}


/*  
    - "Menu de login"
        - Menu da venda
            - Realizar venda
                - Cadastrar clientes
            - Finalizar dia
                - checar se está perto de vencer em promoção
        - Menu do gestor
            - relatórios
                - produtos mais vendidos
                - cliente mais frequente e aquele que compra mais
                - faturamento (temporário)
                - funcionários
            - Atualizar preços
    - Funções para carregar os clientes e produtos nas estruturas
    - Funções para atualizar os arquivos

/*