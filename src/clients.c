#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

#include "../includes/sales.h"
#include "../includes/products.h"
#include "../includes/clients.h"
#include "../includes/auxFunctions.h"


void updateClient (unsigned long long* clientCPF, long* inClientAdress, long* inSalesAdress, float* totalBought)
{
    FILE* clientsFile;
    unsigned long long int tempCPF = *clientCPF;
    char clientName[80];
    long int tempAdress = *inSalesAdress;
    int tempNumVisits = 0;
    float tempTotalBought = 0;


    clientsFile = fopen("../files/clients.txt", "rb+");
    checkFileIntegrity(clientsFile);

    clearBuffer();
    if (*inClientAdress == NOT_EXISTS)
    {
        printf("Insira seu nome: "); scanf("%80[^\n]", clientName);
        fseek(clientsFile, 0, SEEK_END);
    }
    else
    {
        fseek (clientsFile, *inClientAdress, SEEK_SET);
        fscanf(clientsFile, "%llu;%[^;];%ld;%d;%f", &tempCPF, clientName, &tempAdress, &tempNumVisits, &tempTotalBought);
        fseek (clientsFile, *inClientAdress, SEEK_SET);
    }
    
    
    fprintf(clientsFile, "%011llu;%s;%011li;%011i;%011.2f\n", tempCPF, clientName, tempAdress,
                                                   tempNumVisits + 1, tempTotalBought + *totalBought);

    fclose(clientsFile);
    clearScreen();
    printf("Compra Registrada!!\n");
    pauseScreen();
}

/*
Procura pelo CPF indicado e retorna o endereço dele no arquivo de clientes.
Se o cliente já estiver cadastrado, recupera o endereço da sua primeira compra
no arquivo de vendas.
*/
long int searchForCPF (unsigned long long int* wantedCPF, long* inSalesAdress)
{

    FILE* clientsFile;
    char ignore[100];
    unsigned long long int tempCPF = 0;
    long int inClientsAdress = -1;

    clientsFile = fopen("../files/clients.txt", "rb+");
    checkPointerIntegrity(clientsFile);

    do
    { inClientsAdress = ftell(clientsFile); } 
    while (fscanf (clientsFile, "%llu;%[^\n]\n", &tempCPF, ignore) > 0 && tempCPF != *wantedCPF);

    if (*wantedCPF == tempCPF)
    {
        int tempVisit;
        long int aux;
        float tempBought;
        char ignore2[80];

        if (*wantedCPF == ANONYMOUS_CODE)
            *inSalesAdress = NOT_EXISTS;
        else
        {
            sscanf(ignore, "%[^;];%ld;%d;%f", ignore2, &aux, &tempVisit, &tempBought);
            *inSalesAdress = aux;
        }
    }
    else
    {
        *inSalesAdress = NOT_EXISTS;
        inClientsAdress = NOT_EXISTS;
    }

    fclose(clientsFile);
    return inClientsAdress;
}

float getUsedCredit (unsigned long long* clientCPF, const long* inSalesAdress)
{
    unsigned long tempDate, prodCode;
    unsigned long long tempCPF;
    unsigned int tempQnt;
    float tempBought, currentCredit = 0, usedCredit = 0;
    FILE* salesFile = fopen("../files/sales.txt", "r");
    checkFileIntegrity(salesFile);


    fseek(salesFile, *inSalesAdress, SEEK_SET);
    while (fscanf(salesFile, "%lu;%llu;%lu;%u;%f", &tempDate, &tempCPF, &prodCode, &tempQnt, &tempBought) > 0)
        if (tempCPF == *clientCPF)
            currentCredit += (tempQnt * tempBought);

    currentCredit *= CREDITS_CONVERT_TAX;
    do
    {
        clearScreen();
        printf("Voce tem %.2f creditos LP. Quanto quer utilizar?\n", currentCredit);
        scanf("%f", &usedCredit);

        if (usedCredit > currentCredit)
        {
            printf("Valor do credito maior do que ha disponivel!\n");
            pauseScreen();
        }

    } while (usedCredit > currentCredit);

    fclose(salesFile);
    return usedCredit;
}

unsigned long long int askingForCPF (void)
{
    unsigned long long int clientCPF = ANONYMOUS_CODE;
    char answer;

    clearBuffer();
    do
    {   
        clearScreen();
        printf("Deseja CPF na nota?[y/n]\n");

        getc(stdin);
        scanf("%c", &answer); 
        clearBuffer();
        answer = toupper(answer);
        
        if (answer != 'Y' && answer != 'N')
        {
            printf("Resposta invalida!!\n");
            pauseScreen();
        }

    } while (answer != 'Y' && answer != 'N');

    if (answer == 'Y')
    {
        do
        {
            clearScreen();
            printf("Informe seu CPF, por favor: "); 
            scanf("%llu", &clientCPF);
            if (clientCPF == 0)
            {
                printf("Codigo de CPF invalido!\n");
                pauseScreen();
            }

        } while (clientCPF == 0);
    }

    return clientCPF;
}

void getMostFrequentClient (void)
{

    FILE* clientsFile = fopen("../files/clients.txt", "r");
    checkFileIntegrity(clientsFile);
    unsigned long long clientCPF = 0, highestCPF = 0;
    unsigned int clientFreq = 0, highestFrequency = 0;
    char ignore[100];
    
    while (fscanf (clientsFile, "%llu;%[^;];%*d;%d;%*f\n", &clientCPF, ignore, &clientFreq) > 0)
    {
        if (clientFreq >= highestFrequency)
        {
            highestCPF = clientCPF;
            highestFrequency = clientFreq;
        }
    }

    if (highestFrequency == 0)
        printf("Que pena... Parece que nenhum cliente visitou a loja ainda!\n");
    else
    {
        if (highestCPF == ANONYMOUS_CODE)
            printf("Pessoas nao cadastradas estao frequentando mais a loja.\n"
                    "Checar modelo de registro.\n");
        else
            printf("Cliente mais frequente: %lld. Frequencia: %u\n", highestCPF, highestFrequency);
    }
    
    pauseScreen();
    fclose(clientsFile);
}

void getRichestClient (void)
{

    FILE* clientsFile = fopen("../files/clients.txt", "r");
    checkFileIntegrity(clientsFile);
    unsigned long long clientCPF = 0, highestCPF = 0;
    double clientBought = 0, highestBought = -1;
    char ignore[100];

    while (fscanf (clientsFile, "%llu;%[^;];%*d;%*d;%lf\n", &clientCPF, ignore, &clientBought) > 0)
    {
        if (clientBought >= highestBought)
        {
            highestCPF = clientCPF;
            highestBought = clientBought;
        }
    }

    if (highestBought == 0)
        printf("Que pena... Parece que nenhum cliente comprou na loja ainda!\n");
    else
    {
        if (highestCPF == ANONYMOUS_CODE)
            printf("Pessoas nao cadastradas estao comprando mais na loja.\n" 
                    "Checar modelo de registro.\n");
        else
            printf("Cliente que mais comprou: %lld. Total comprado: %g\n", highestCPF, highestBought);
    }

    pauseScreen();
    fclose(clientsFile);
}