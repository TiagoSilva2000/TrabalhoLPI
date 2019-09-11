#ifndef CLIENTS_H
#define CLIENTS_H
#include "sales.h"

    #define CREDITS_CONVERT_TAX 0.005
    #define ANONYMOUS_CODE 0
    #define NOT_EXISTS -1

    void saleConfirmed (Sale** shoppingCart);
    void getRichestClient (void);
    void getMostFrequentClient (void);
    void updateClient (unsigned long long* clientCPF, long* inClientAdress, 
        long* inSalesAdress, float* totalBought);
    void sumPurchaseToProductsFile (FILE* productsFile, Sale* purchaseNode);
    unsigned long long int askingForCPF (void);
    float getUsedCredit (unsigned long long* clientCPF, const long* inSalesAdress);    
    long int searchForCPF (unsigned long long int* wantedCPF, long* inSalesAdress);
#endif