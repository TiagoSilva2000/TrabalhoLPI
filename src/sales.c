#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../includes/auxFunctions.h"
#include "../includes/sales.h"
#include "../includes/clients.h"

/*
Pedir codigo do produto
Buscar pelo codigo no produos.txt
Pegar as informacoes do produto
Guardar em um struct produto
Guardar esse produto num carrinho
*/

bool getProdByCod (FILE *productsFile, unsigned long wantedCode, Sale* product)         //Procura um produto referente a um codigo passado, armazena as informações em
{
   unsigned int ignoreQnt;
    /*

        Ler o primeiro unsigned long
        Comparar com cod
        Se for diferente
            Anda até o \n
            Anda mais um pra ficar no inicio da proxima linha
        Se for igual
            Pega as outras informações e guarda num prod novo
            retorna esse prod
        Se terminar e não achar, retorna NULL
    */
   rewind(productsFile);
   do
   {
       product->inProductsAdress = ftell(productsFile);
   } while (fscanf(productsFile, "%lu;%[^;];%lf;%u\n", &product->code, product->name, &product->price, &ignoreQnt) > 0 
            && product->code != wantedCode);
    
    
    rewind(productsFile);
    
    return product->code == wantedCode;
}

unsigned long getCode()
{
    //Digite o codigo do produto
    clearScreen();
    printf("======================================\n");
    printf("=                                    =\n");
    printf("=     DIGITE O CODIGO DO PRODUTO     =\n");
    printf("=            0 para Sair             =\n");
    printf("======================================\n");

    unsigned long prodCod;
    scanf("%lu", &prodCod);

    return prodCod;
}

size_t GetQuantity()
{
    //Digite a quantidade

    size_t prodQuant;
    do
    {
        clearScreen();
        printf("======================================\n");
        printf("=                                    =\n");
        printf("=                                    =\n");
        printf("=   DIGITE A QUANTIDADE DO PRODUTO   =\n");
        printf("=                                    =\n");
        printf("=                                    =\n");
        printf("=      Pressione 0 para Cancelar     =\n");
        printf("======================================\n");

        if (prodQuant < 0)
        {
            printf("Quantidade invalida! Insira uma quantidade valida, por favor.\n");
            pauseScreen();
        }
    scanf("%lu", &prodQuant);
    } while (prodQuant < 0);

    return prodQuant;
}

void addSale (Sale *product, size_t quantity, Sale **start)
{
    /*
    Pedir um codigo
    Procurar pelo produto
    Validar o produto
    Guardar o produto
    Guardar o codigo do produto no Node

    Pedir a quantidade
    Guardar a quantidade no Node

    Multiplicar a quantidade pelo preço
    Guardar o preço no Node

    Adicionar esse node a uma lista
    */
    Sale *newSet = (Sale*) malloc(sizeof(Sale));
    checkPointerIntegrity(newSet);

    newSet->code = product->code;
    newSet->price = product->price;
    newSet->inProductsAdress = product->inProductsAdress;
    strcpy(newSet->name, product->name);
    newSet->quantity = quantity;
    newSet->next = NULL;

    if(!*start) 
        *start = newSet;                                              //Carrinho vazio, adiciona no inicio
    else
    {
        Sale* currentSale = *start;

        while (currentSale->next != NULL && currentSale->code != product->code)
            currentSale = currentSale->next;
    
        if (currentSale->next == NULL && product->code != currentSale->code)
            currentSale->next = newSet;                                             //Coloca no final
        else
            currentSale->quantity += quantity;
    }                                                                    //Tem coisa no carrinho
}

Sale* RemoveFromCart(Sale **cart)
{
    /*
    Pedir o codigo do produto a ser removido
    Procurar o produto no carrinho pelo codigo
        Pegar um produto no carrinho
        Comparar o codigo com o do produto
        Se o codigo for igual
            Retirar ele
        Se o codigo for diferente
            Ir para o proximo produto
    Remover o produto do carrinho
    */

    if(!*cart)
    {
        printf("\nCarrinho vazio\n");
        pauseScreen();
        return NULL;
    }

    size_t quantity;
    unsigned long cod = getCode();
    if (cod == 0)
        return NULL;
    

    //Procurar produto
    Sale *currentSale = *cart, *prev = NULL;
    while(currentSale && currentSale->code != cod)
    {
        prev = currentSale;
        currentSale = currentSale->next;
    }

    //Produto não encontrado
    if(!currentSale)
    {
        printf("Codigo do produto nao esta no carrinho");
        pauseScreen();
        return NULL;
    }
    //Retirar o produto encontrado
    else
    {   
        bool wrongQuantity = true;
        while (wrongQuantity)
        { 
            /*
            Pegar a quantidade
            Checar se a quantidade é maior que a de produtos nessa sale
            Se a quantidade for MAIOR que a quantidade de produtos nessa Sale
                Retornar erro de quantidade
                Volta pra pedir a quantidade
            Senão se a quantidade for IGUAL a quantidade de produtos nessa Sale
                Retirar o node da Sale
            Senão se a quantidade for MENOR a quantidade de produtos nessa Sale
                Diminuir a quantidade
                Diminuir o preço
                    Verificar o preço original desse produto
                    Diminuir do total da Sale
            Tirar produto
            */

            quantity = GetQuantity();
            if(quantity > currentSale->quantity)
            {
                //Retorna erro de quantidade
                printf("Nao existem tantos produtos com este codigo no carrinho\n\n");
                printf("Digite outro codigo\n");
                pauseScreen();
            }
            else
            {
                if(quantity == currentSale->quantity)
                {
                    //Se estiver no começo
                    if(currentSale == *cart) *cart = currentSale->next;

                    //Se estiver no meio ou no final
                    else prev->next = currentSale->next;
                }
                else
                    currentSale->quantity -= quantity;
                wrongQuantity = false;
            }
        }
        
    }

    pauseScreen();
    return(currentSale);
}

void printProduct(Sale *product)
{

    if(!product)
    {
        printf("Produto nao existe");
        return;
    }

    printf("\nProduct Code = %lu\n", product->code);
    printf("Product Name = %s\n", product->name);
    printf("Product Price = %.2f\n", product->price);
}

void printSale (Sale **start)
{

    if (!(*start))
    {
        printf("Carrinho vazio\n");
        pauseScreen();
        pauseScreen();
        return;
    }

    Sale *curNode = *start;
    while(curNode != NULL)
    {
        printf("%lu - %u - %s - %.2f\n", curNode->code, curNode->quantity, curNode->name, curNode->price * curNode->quantity);
        curNode = curNode->next;
    }
    pauseScreen();
    pauseScreen();
}

void printSellMenu()
{
    clearScreen();
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


void addProductToCart (FILE* productsFile, Sale** saleCart)
{
 
    char validation = 'n';
    Sale tempProd;
    unsigned long int prodCode;
    unsigned int tempQnt;

    while(validation == 'n' && ((prodCode = getCode()) != 0))                                //Ciclo de validação do produto
    {
        clearScreen();        //Pede um codigo de produto e procura ele por esse codigo

        if(getProdByCod(productsFile, prodCode, &tempProd))                                            //Se o produto foi encontrado
        {
            do
            {
                clearScreen();
                printProduct(&tempProd);                                 //Mostra o produto
                printf("\nEsse eh o produto? (y/n)");                   //Pede confirmação
                scanf(" %c",&validation);

                if (validation != 'n' && validation != 'y')
                {
                    clearScreen();
                    printf("Opcao invalida\n");                                 //Informa o erro
                    pauseScreen();
                }

            } while(validation != 'n' && validation != 'y');              //Se digitar algo não permitido           
        }
        else                                                    //Se o produto não foi encontrado
        {
            clearScreen();
            printf("\nCodigo Invalido\n");
            pauseScreen();
        }
    }
    if (validation == 'y')
    {
        tempQnt = GetQuantity();
        if (tempQnt > 0)
            addSale(&tempProd, tempQnt, saleCart);
    }
}


void sell (void)
{
    FILE *productsFile = fopen("../files/products.txt", "rb+");
    Sale *saleCart = NULL;
    char op = '1';

    //Update
    while(op != '0')
    {
        clearScreen();

        printSellMenu();

        clearBuffer();
        scanf("%c", &op);
        clearBuffer();

        switch (op)
        {
            //mostrar carrinho
            case '1':
            {
                printSale(&saleCart);
                break;
            }
            //adicionar produto ao carrinho
            case '2':
            {
                addProductToCart(productsFile, &saleCart);
                break;
            }
            case '3':     //remover produto do carrinho
            {
                RemoveFromCart(&saleCart);
                break;
            }
            case '0':     //sair
            {
                saleConfirmed (&saleCart);
                break;
            }
            default:    //opção invalida
            {
                clearScreen();
                printf("\nOpcao invalida\n");
                pauseScreen();
                break;
            }
        }
    }

    fclose (productsFile);
}

// Uma função pra receber uma currentDate e retornar ela formatada no formato do salesFile.
unsigned long getFormattedDate (void) {

    int year, month, day = 0;
    unsigned long currentYear = getCurrentDate() / 10000; // extraindo ano da data formatada.
    
    do
    {
        clearScreen();
        printf("Digite o ano que voce deseja recolher os dados:\n");
        scanf("%d", &year);

        if (year < START_YEAR || year > currentYear)
        {
            printf("Data inserida nao permitida. Insira outra, por favor\n");
            pauseScreen();
        }
    } while (year < START_YEAR || year > currentYear);


    do
    {
        clearScreen();
        printf("Digite o mes que voce deseja recolher os dados:\n");
        scanf("%d", &month);
        
        if (month < 1 || month > 12)
        {
            printf("Mes inserido em formato nao permitido. Insira novamente, por favor\n");
            pauseScreen();
        }

    } while (month < 1 || month > 12);
    
    do
    {    
        clearScreen();
        printf("Digite o dia que voce deseja recolher os dados:\n");
        scanf("%d", &day);
        if (day < 0 || day > 30)
        {
            printf("Dia inserido em formato nao permitido. Insira novamente, por favor\n");
            pauseScreen();
        }
    } while (day < 0 || day > 30);


    clearScreen();
    return (year * 10000) + (month * 100) + (day);
}

void getIncome (void) {

    unsigned long startPoint, endPoint = 0;
    float currentPrice, income = 0;
    unsigned long int currentDate = 0, currentProdCode;
    unsigned int currentQnt = 0; // Variaveis apenas para leitura
    unsigned long long int cpf;

    // Abrir os arquivos, inclusive o tempor�rio
    FILE *salesFile = fopen("../files/sales.txt", "r");
    FILE *tempFile = tmpfile();


    //Validação de ambos os arquivos
    if(tempFile == NULL || salesFile == NULL){
        exit(1);
    }

    // Guardar esses valores em uma variável
    startPoint = getFormattedDate();
    endPoint = getFormattedDate();


    while(fscanf(salesFile, "%lu;%lu;%llu;%u;%f", &currentDate, &currentProdCode, &cpf, &currentQnt, &currentPrice) > 0)
        if(currentDate >= startPoint && currentDate <= endPoint)
            income += (currentPrice * currentQnt);

    fprintf(tempFile, "(%lu -> %lu) %.2f\n", startPoint, endPoint, income);
    printf("\n\nDe %lu a %lu, a receita eh de %.2f\n\n\n", startPoint, endPoint, income);

    pauseScreen();
}