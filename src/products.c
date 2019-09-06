#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ctype.h"
#include "../includes/auxFunctions.h"
#include "../includes/products.h"
#include "../includes/sales.h"
#define FOUND_IT 1

// Funcao para pegar produto
void getProdInfo(unsigned long* prodCode, char* prodName, double* price){

    FILE* productsFile = fopen("../files/products.txt", "r");
    checkFileIntegrity(productsFile);
    int confirm = 0;
    Sale tempProduct;

    do
    {    
        do
        {
            printf("Digite o numero do codigo de barras:\n");
            scanf("%10lu", prodCode);
            clearBuffer();
            if (getProdByCod (productsFile, *prodCode, &tempProduct) == FOUND_IT)
            {   
                printf("Codigo do numero ja existe no nosso cadastro!\n");
                pauseScreen();
                prodCode = 0;
            }

        } while (prodCode == 0);
        //Procura um produto referente a um codigo passado, armazena as informações em);

        // Armazena nome primario e secundario do produto
        printf("Digite o nome do produto:\n");
        scanf("%80[^\n]s", prodName);
        clearBuffer();

        // Armazena price do produto no final da linha e de o \n para descer ate a proxima linha.
        printf("Digite o price do produto:\n");
        scanf("%10lf", price);

        // Confirmacao
        printf("Pressione 1 para confirmar, outro numero para repetir com:\n");
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
    
    // fseek(productsFile, 0, SEEK_END);
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

    printf("\nSAIU!\n");
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
        printf("Voce realmente deseja alterar esse produto?[y/n]"); scanf("%c", &choice);
        choice = toupper(choice);

        if (choice != 'Y' && choice != 'N')
        {
            printf("Codigo invalido. Digite outro, por favor\n");
            pauseScreen();
        }
    } while (choice != 'Y' && choice != 'N');
    
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
        }
            pauseScreen();
            clearBuffer();
    } while (prodAdress == -1 || prodAdress == -2);
    if (prodCode == 0)
        printf("\nSAIU\n");
}

void getMostSoldProduct (void)
{
    FILE* productsFile;
    unsigned int highestQnt = 0, cmpQnt;
    unsigned long highestCode, cmpCode;
    char ignore[80], highestName[80];
    double ignorePrice;

    productsFile = fopen("../files/products.txt", "r");
    checkFileIntegrity(productsFile);

    while (fscanf (productsFile, "%lu;%[^;];%lf;%u\n", &cmpCode, ignore, &ignorePrice,  &cmpQnt) > 0)
    {
        if (cmpQnt > highestQnt)
        {
            highestCode = cmpCode;
            highestQnt = cmpQnt;
            strcpy(highestName, ignore);
        }
    }

    if (highestQnt > 0)
        printf("Produto mais vendido: %lu.\nNome: %s.\nQuantidade de vezes vendido: %u\n", highestCode, highestName, highestQnt);
    else
        printf("Nenhum produto foi vendido ate agora...\n");
    
    pauseScreen();
    fclose(productsFile);
}