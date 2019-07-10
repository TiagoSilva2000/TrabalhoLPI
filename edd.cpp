/* 
Discentes: Evelyn, Thiago Oliveira e Tiago Moreira
Docente: Cláudio Amorim
Disciplina: Linguagens de Programação I
Data:
Descrição do Trabalho:
    
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CURRENT_YEAR 2019

// A basic structure to hold the data associated with a new product.
typedef struct new_product
{
    int id_code, qnt;
    double price;
    char description [100], expDate[10];

} New_product;

typedef struct client_node
{
    double totalSpent;
    int cpf, frequency;
    char name[80];
} Client_node;

void interface (int &choice)
{
    printf ("1 - Cadastrar Novo Produto\n");
    printf ("2 - Realizar Venda\n");
    printf ("3 - Checar Relatorios\n");
    printf ("4 - Atualizar Preço\n");
    printf ("985 - Finalizar Dia de Operacao\n");
    scanf("%i", &choice);
}

void clear_buffer ()
{
    char c;
    while ((c = getc(stdin)) != '\n' && c != EOF);
}

void sellsProduct (FILE* products, FILE* clients, FILE* sales)
{}




void checkReports ()
{}

void updatePrice ()
{}

void updateReports ()
{}

void heap_sort (){}

void registerClient (Client_node* current_clients)
{
    Client_node new_client = get_client_info ();

    




}







void push_client_node (Char* aux_str, Client_node* current_clients)
{




}


// Implementar heap sort.
Client_node* loadClients (FILE* clients)
{    
    int nodesQnt = 0;
    char aux_str[80];
    Client_node* current_clients = NULL;

    nodesQnt = getw(clients);
    current_clients = (Client_node*) malloc(sizeof(Client_node) * nodesQnt);
    if(!current_clients) exit(1);
    
    while (fgets(aux_str, 80, clients) != EOF)
        push_client_node (aux_str, current_clients);

    heap_sort ();




    return true;
}

int main (void)
{
    int choice = 0;
    FILE* clients = fopen("clients.txt", "a+");
    FILE* products = fopen("products.txt", "a+");
    FILE* sales = fopen("sales.txt", "a+");
    FILE* employers = fopen("employers.txt", "a+");

    while (choice != 985)
    {
        interface(choice);
        if (choice == 1)
           getNewProductInfo(products);
        else if (choice == 2)
            sellsProduct();
        else if (choice == 3)
            checkReports();
        else if (choice == 4)
            updatePrice ();
    }

    updateReports ();

    fclose(clients);
    fclose(products);
    fclose(sales);
    fclose(employers);

    getchar();
    return 0;
}