#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "../includes/auxFunctions.h"
#include "../includes/sales.h"
#include "../includes/clients.h"
#include "../includes/interface.h"
#include "../includes/products.h"

void sell (void)
{
    FILE *productsFile = fopen("../files/products.txt", "rb+");
    Sale *saleCart = NULL;
    char op = '1';


    while (op != '0')
    {
        clearScreen();
        
        sellInterface();
        clearBuffer();
        scanf("%c", &op);
        clearBuffer();

        clearScreen();
        
        if (op == '1')
            printSale(&saleCart);
        else if (op == '2')
            addProductToCart(productsFile, &saleCart);
        else if (op == '3')
            RemoveFromCart(&saleCart);
        else if (op == '0')
            if (saleCart != NULL) saleConfirmed(&saleCart);
        else
            printf("\nOpcao invalida\n");

        getc(stdin);
        pauseScreen();
    }
    
    fclose (productsFile);
}

void printSale (Sale **start)
{
    Sale *curNode = *start;

    if (!(*start))
    {
        printf("Carrinho vazio\n");
        return;
    }

    while(curNode != NULL)
    {
        printf("%lu - %u - %s - %.2f\n", curNode->code, curNode->quantity, 
                                        curNode->name, curNode->price * curNode->quantity);
        curNode = curNode->next;
    }
}

void addProductToCart (FILE* productsFile, Sale** saleCart)
{
    char validation = 'n';
    Sale tempProd;
    unsigned long int prodCode;
    unsigned int tempQnt = 0;



    do
    {
        clearScreen(); clearBuffer();
        prodCodeInterface();
        scanf("%lu", &prodCode);
        if (prodCode == I_WANT_TO_EXIT) return;


        clearScreen();
        if(foundProd(productsFile, prodCode, &tempProd))
        {
            do
            {
                clearScreen(); clearBuffer();
                printProduct(&tempProd);
                
                printf("\nEsse eh o produto? (s/n)\n");
                validation = tolower(getc(stdin));

                if (validation != 'n' && validation != 's')
                {
                    printf("Opcao invalida\n");
                    pauseScreen();
                }

            } while(validation != 'n' && validation != 's');
        }
        else
        {
            clearScreen();
            printf("Codigo Invalido\nPressione Enter para retornar\n");
            pauseScreen();
        }
    } while(validation != 's');

    if (validation == 's')
    {
        clearScreen();
        prodQntInterface();
        scanf("%u", &tempQnt);
        if (tempQnt > 0)
            addSale(&tempProd, tempQnt, saleCart);
    }
        
    printf("Produto %s\n", tempQnt > 0 ? "adicionado com sucesso" : "nao adicionado");

}

Sale* RemoveFromCart(Sale **cart)
{
    size_t quantity;
    unsigned long cod;
    Sale *currentSale = *cart, *prev = NULL;
    bool wrongQuantity = true;


    if(!*cart)
    {
        printf("Carrinho vazio\n");
        return NULL;
    }

    do
    {
        clearScreen();
        prodCodeInterface();
        printSale(cart);
        scanf("%lu", &cod);
    } while (cod <  0);

    if (cod == I_WANT_TO_EXIT)
        return NULL;
    
    while(currentSale && currentSale->code != cod)
    {
        prev = currentSale;
        currentSale = currentSale->next;
    }

    if(!currentSale)
    {
        printf("Codigo do produto nao esta no carrinho\n");
        return NULL;
    }
    
    do
    {
        prodQntInterface();
        scanf("%lu", &quantity);
        if(quantity > currentSale->quantity)
        {
            printf("Nao existem tantos produtos com este codigo no carrinho\n\n");
            printf("Digite outro codigo\n");
            pauseScreen();
        }
        else
        {
            wrongQuantity = false;
            if(quantity == currentSale->quantity)
            {
                if(currentSale == *cart) 
                    *cart = (*cart)->next;
                else 
                    prev->next = currentSale->next;
                free(currentSale);
            }
            else
                currentSale->quantity -= quantity;
        }
    } while (wrongQuantity);

    return currentSale;
}

void saleConfirmed (Sale** shoppingCart)
{
    float totalBought = 0, usedCredit = 0;
    long int inSalesAdress = 985, inClientsAdress = 985;
    long newAdress;
    unsigned long int currentDate = getCurrentDate(); 
    unsigned long long int clientCPF = askingForCPF();



    inClientsAdress = searchForCPF(&clientCPF, &inSalesAdress);
    if (inClientsAdress != NOT_EXISTS && clientCPF != ANONYMOUS_CODE)
    {
        usedCredit = getUsedCredit(&clientCPF, &inSalesAdress);
        totalBought -= usedCredit;
    }
    newAdress = registerSale(shoppingCart, &currentDate, &clientCPF, &totalBought, &usedCredit);
    if (inSalesAdress == NOT_EXISTS)
        inSalesAdress = newAdress;
    updateClient(&clientCPF, &inClientsAdress, &inSalesAdress, &totalBought);

    printf("Compra concluida!!\n");
}

long int registerSale (Sale** shoppingCart, unsigned long* currentDate, 
                    unsigned long long* clientCPF, float* totalBought, float* usedCredit)
{   
    Sale* cartWalker = *shoppingCart;
    long int inSalesAdress;
    FILE *salesFile = fopen("../files/sales.txt", "a+"),
         *productsFile = fopen("../files/products.txt", "rb+");
    checkFileIntegrity(salesFile);
    checkFileIntegrity(productsFile);


    fseek(salesFile, 0, SEEK_END);
    inSalesAdress = ftell(salesFile);
    while (cartWalker)
    {
        sumPurchaseToProductsFile (productsFile, cartWalker);
        fprintf(salesFile, "%lu;%llu;%lu;%u;%010.2f\n", *currentDate, *clientCPF, cartWalker->code, 
                cartWalker->quantity, cartWalker->price);
        *totalBought += (cartWalker->quantity * cartWalker->price);
        unloadCartNode(&cartWalker);
    }

    if (*usedCredit > 0)
    {
        float totalDiscount = -1 * ((*usedCredit / CREDITS_CONVERT_TAX) + *usedCredit);
        fprintf(salesFile, "%lu;%llu;%d;%u;%010.2f\n", *currentDate, *clientCPF, 0, 1, totalDiscount);
    }

    fclose(productsFile);
    fclose(salesFile);
    return *clientCPF == ANONYMOUS_CODE ? NOT_EXISTS : inSalesAdress;
}

void addSale (Sale *product, size_t quantity, Sale **start)
{
    Sale *newSet = (Sale*) malloc(sizeof(Sale));
    checkPointerIntegrity(newSet);

    *newSet = *product;
    newSet->quantity = quantity;
    newSet->next = NULL;

    if(!*start)
        *start = newSet;
    else
    {
        Sale* currentSale = *start;

        while (currentSale->next != NULL && currentSale->code != product->code)
            currentSale = currentSale->next;
    
        if (currentSale->next == NULL && product->code != currentSale->code)
            currentSale->next = newSet;
        else
            currentSale->quantity += quantity;
    }
}

void unloadCartNode (Sale** currentNode)
{   
    if(!currentNode) return;
    Sale* auxFree = *currentNode;

    (*currentNode) = (*currentNode)->next;
    free(auxFree);
}

void getIncome (void) 
{

    unsigned long startPoint, endPoint = 0;
    float currentPrice, income = 0;
    unsigned long int currentDate = 0, currentProdCode;
    unsigned int currentQnt = 0;
    unsigned long long int cpf;
    FILE *salesFile = fopen("../files/sales.txt", "r");
    checkFileIntegrity(salesFile);



    printf("Dica:\nData de comeco da empresa:%i  Data atual: %lu\n", START_YEAR, getCurrentDate());
    pauseScreen();

    startPoint = getUsersDate();
    endPoint = getUsersDate();


    while(fscanf(salesFile, "%lu;%lu;%llu;%u;%f", &currentDate, &currentProdCode, &cpf, &currentQnt, &currentPrice) > 0)
        if(currentDate >= startPoint && currentDate <= endPoint)
            income += (currentPrice * currentQnt);

    printf("\n\nDe %lu a %lu, a receita eh de %.2f\n\n\n", startPoint, endPoint, income);

    fclose(salesFile);
}