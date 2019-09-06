#include <stdio.h>
#include <time.h>
#include <stdlib.h> 
#include "../includes/auxFunctions.h"

void clearScreen (void)
{
    system("cls");
    // system("clear");
    // printf("\e[H\e[2J");
}

void pauseScreen (void)
{   

    clearBuffer();
    getc(stdin);
    clearBuffer();
}

void clearBuffer (void)
{
    setbuf(stdin, 0);

    /*
    char c;
    while ( (c = getc(stdin) != '\n') && c != EOF);
    */
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