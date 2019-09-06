#ifndef SALES_H
#define SALES_H
#include <stdbool.h>

    #define START_YEAR 2000
    typedef struct prod Prod;
    typedef struct sale Sale;

    struct sale
    {
        unsigned long code;                 // Codigo do produto
        char name[100];                     // Quantidade de produtos
        double price;                       // Preco total do conjunto
        unsigned int quantity;
        long int inProductsAdress;
        Sale *next;
    };

    void sell (void);
    void getIncome (void);
    bool getProdByCod (FILE *productsFile, unsigned long wantedCode, Sale* product);         //Procura um produto referente a um codigo passado, armazena as informações em
#endif // SALES_H