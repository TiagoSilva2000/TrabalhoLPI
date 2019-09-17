#ifndef SALES_H
#define SALES_H
#include <stdbool.h>

    typedef struct prod Prod;
    typedef struct sale Sale;

    struct sale
    {
        unsigned long code;                 
        char name[100];                     
        double price;                       
        unsigned int quantity;
        long int inProductsAdress;
        Sale *next;
    };

    void sell (void);
    void getIncome (void);
    bool foundProd (FILE *productsFile, unsigned long wantedCode, Sale* product);
    long int registerSale (Sale** shoppingCart, unsigned long* currentDate, 
                            unsigned long long* clientCPF, float* totalBought, float* usedCredit);
    void saleConfirmed (Sale** shoppingCart);
    void unloadCartNode (Sale** currentNode);
    void printSale (Sale **start);
    void addProductToCart (FILE* productsFile, Sale** saleCart);
    Sale* RemoveFromCart(Sale **cart);
    void addSale (Sale *product, size_t quantity, Sale **start);
    void cancelSale (Sale** shoppingCart);

#endif // SALES_H