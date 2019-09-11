#include <stdio.h>
#include <time.h>
#include <stdlib.h> 
#include "../includes/auxFunctions.h"

void clearScreen (void)
{
    // system("cls");
    system("clear");
    // printf("\e[H\e[2J");
}

void pauseScreen (void)
{
    printf("\nPressione Enter para prosseguir\n");   
    clearBuffer();
    getc(stdin);
    clearBuffer();
}

void clearBuffer (void)
{
    setbuf(stdin, NULL);
    
    // char c;
    // while ( (c = getc(stdin) != '\n') && c != EOF);
    
}

void checkPointerIntegrity (void* pointer)
{
    if (!pointer)
    {
        printf("MEM ERROR ALLOCATION!!\n");
        pauseScreen();
        exit(1);    
    }
}

void checkFileIntegrity (FILE* file)
{
    if (!file)
    {
        printf("FILE OPENING ERROR!!\n");
        pauseScreen();
        exit(2);
    }
}

unsigned long getCurrentDate (void)
{
    time_t rawtime;
    struct tm* currentTime;

    time(&rawtime);
    currentTime = localtime(&rawtime);

    return ((currentTime->tm_year+1900) * 10000) + ((currentTime->tm_mon + 1) * 100) + (currentTime->tm_mday);
}

unsigned long getUsersDate (void)
{

    int year, month, day;
    unsigned long currentYear = getCurrentDate() / 10000;
    
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
