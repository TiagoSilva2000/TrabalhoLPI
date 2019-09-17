#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ctype.h"
#include "../includes/auxFunctions.h"
#include "../includes/products.h"
#include "../includes/sales.h"

bool foundProd (FILE *productsFile, unsigned long wantedCode, Sale* product)         //Procura um produto referente a um codigo passado, armazena as informações em
{
   unsigned int ignoreQnt;
   
   
   rewind(productsFile);
   do
   { product->inProductsAdress = ftell(productsFile); } 
    while (fscanf(productsFile, "%lu;%[^;];%lf;%u\n", &product->code, product->name, 
                &product->price, &ignoreQnt) > 0 && product->code != wantedCode);
    
    
    rewind(productsFile);
    return product->code == wantedCode;
}

void getProdInfo(unsigned long* prodCode, char* prodName, double* price)
{

    FILE* productsFile = fopen("../files/products.txt", "r");
    checkFileIntegrity(productsFile);
    int confirm = 0;
    Sale tempProduct;

    do
    {    
        clearScreen();
        do
        {
            printf("Digite o numero do codigo de barras:\n");
            scanf("%10lu", prodCode);
            clearBuffer();
            if (foundProd (productsFile, *prodCode, &tempProduct) == FOUND_IT)
            {   
                printf("Codigo do numero ja existe no nosso cadastro!\n");
                pauseScreen();
                prodCode = 0;
            }

        } while (prodCode == 0);

        printf("Digite o nome do produto:\n");
        scanf("%80[^\n]s", prodName);
        clearBuffer();

        printf("Digite o price do produto:\n");
        scanf("%10lf", price);

        clearScreen(); clearBuffer();
        printf("Pressione 1 para confirmar ou outro numero para corrigir com:\n");
        printf("Codigo: %lu\nNome: %s\nPrice: %.2f\n", *prodCode, prodName, *price);
        scanf("%d", &confirm);

    } while (confirm != 1);

    fclose(productsFile);
}

void createNewProduct (void)   
{
    FILE *productsFile;
    char prodName[80];
    unsigned long prodCode;
    double prodPrice;


    clearScreen();
    getProdInfo (&prodCode, prodName, &prodPrice);

    productsFile = fopen("../files/products.txt", "a+");
    checkFileIntegrity(productsFile);
    
    fprintf(productsFile, "%010lu;%s;%010.2f;%010u\n", prodCode, prodName, prodPrice, 0);
    
    clearScreen();
    printf("\nProduto registrado.\n");
    fclose(productsFile);
    pauseScreen();
}

void registerproduct (void)
{
    
    int option = 0;

    do
    {   
        clearScreen();
        printf("Digite:\n");
        printf("1 para cadastrar produto\n");
        printf("0 para sair\n");
        scanf("%d", &option);
        if (option != 1 && option != 0)
        {
            printf("Codigo invalido!\n");
            pauseScreen();
        }
        else if (option == 1)
            createNewProduct();
        
    } while (option != 0);

}

long int searchProductAndModify (unsigned long wantedCode, double newPrice)
{
    FILE* productsFile = fopen("../files/products.txt", "rb+");
    checkFileIntegrity(productsFile);
    long int prodAdress = 0;
    unsigned long cmpCode;
    char tempName[100], choice;
    unsigned int tempQnt;  
    double tempPrice;

    rewind(productsFile);
    do
    { prodAdress = ftell(productsFile); } 
    while (fscanf (productsFile, "%lu;%[^;];%lf;%u\n", &cmpCode, tempName, &tempPrice, &tempQnt) > 0 && cmpCode != wantedCode);

    if (cmpCode != wantedCode)
    {
        fclose(productsFile);
        return -1;
    }

    fseek(productsFile, prodAdress, SEEK_SET);
    fscanf (productsFile, "%lu;%[^;];%lf;%u\n", &cmpCode, tempName, &tempPrice, &tempQnt);
    
    do
    {
        clearBuffer();
        clearScreen();
        printf("Informacoes sobre o produto:\n1-Codigo:%lu\n2-Decricao:%s\n3-Preco/Novo Preco:%g / %g\n4-Quantidade ja vendida:%u\n",
                cmpCode, tempName, tempPrice, newPrice, tempQnt);
        printf("Voce realmente deseja alterar esse produto?[s/n]"); scanf("%c", &choice);
        choice = toupper(choice);

        if (choice != 'S' && choice != 'N')
        {
            printf("Codigo invalido. Digite outro, por favor\n");
            pauseScreen();
        }
    } while (choice != 'S' && choice != 'N');
    
    if (choice == 'N')
        return -2;
    
    fseek(productsFile, prodAdress, SEEK_SET);
    fprintf(productsFile, "%010lu;%s;%010.2lf;%010u", cmpCode, tempName, newPrice, tempQnt);

    fclose(productsFile);
    return prodAdress;
}

void updatePrice (void)
{
    unsigned long prodCode;
    double newPrice;
    long int prodAdress;

    do
    {
        clearScreen();
        do
        {
            clearScreen();
            printf("Insira o codigo do produto do qual voce quer mudar o price.\n"); 
            printf("Digite 0 para cancelar a operacao:\n");
            scanf("%lu", &prodCode);
            if (prodCode < 0)
            {
                printf("Codigo invalido!\nInsira outro novamente, por favor\n");
                pauseScreen();
            }
        } while (prodCode < 0);
        
        if (prodCode != 0)
        {
            do
            {        
                clearScreen();
                printf("Insira o novo preco do produto: "); 
                scanf("%lf", &newPrice);
                if(newPrice <= 0)
                {
                    printf("Preco invalido. Digite outro, por favor\n");
                    pauseScreen();
                }
            } while (newPrice <= 0);
            

            prodAdress = searchProductAndModify(prodCode, newPrice);
            if (prodAdress == -1)
                printf("Codigo nao encontrado!\nInsira outro ou cancele a operacao\n");
            else if (prodAdress == -2)
                printf("Digite outro codigo, por favor\n");
            else
                printf("\nPreco atualizado com sucesso!!!\n");
            pauseScreen();
        }
        clearBuffer();
    } while (prodAdress == -1 || prodAdress == -2);

}

void getMostSoldProduct (void)
{
    FILE* productsFile;
    unsigned int highestQnt = 0, qntToCmp = 0;
    unsigned long highestCode, cmpCode;
    char wealthiestName[80], highestName[80];
    double ignorePrice;

    productsFile = fopen("../files/products.txt", "r");
    checkFileIntegrity(productsFile);

    while (fscanf (productsFile, "%lu;%[^;];%lf;%u\n", &cmpCode, wealthiestName, &ignorePrice,  &qntToCmp) > 0)
    {
        if (qntToCmp > highestQnt)
        {
            highestCode = cmpCode;
            highestQnt = qntToCmp;
            strcpy(highestName, wealthiestName);
        }
    }

    if (highestQnt > 0)
        printf("Produto mais vendido: %lu.\nNome: %s.\nQuantidade de vezes vendido: %u\n", highestCode, highestName, highestQnt);
    else
        printf("Nenhum produto foi vendido ate agora...\n");
    
    pauseScreen();
    fclose(productsFile);
}

void sumPurchaseToProductsFile (FILE* productsFile, Sale* purchaseNode)
{
    if (!purchaseNode) return;

    unsigned long tempCode;
    char tempName[80];
    double tempPrice;
    unsigned int tempQnt;

    fseek(productsFile, purchaseNode->inProductsAdress, SEEK_SET);
    fscanf(productsFile, "%lu;%[^;];%lf;%u\n", &tempCode, tempName, &tempPrice, &tempQnt);
    fseek(productsFile, purchaseNode->inProductsAdress, SEEK_SET);
    fprintf(productsFile, "%010lu;%s;%010.2f;%010u\n", tempCode, tempName, tempPrice, tempQnt + purchaseNode->quantity);
}

void printProduct (Sale *product)
{
    if(!product)
    {
        printf("Produto nao existe\n");
        return;
    }

    printf("\nProduct Code = %lu\n", product->code);
    printf("Product Name = %s\n", product->name);
    printf("Product Price = %.2f\n", product->price);
}