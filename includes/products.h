#ifndef PRODUCTS_H
#define PRODUCTS_H
#include <stdbool.h>
#include "sales.h"

    #define FOUND_IT 1

    void registerproduct (void);
    void updatePrice (void);
    void getMostSoldProduct (void);
    bool foundProd (FILE *productsFile, unsigned long wantedCode, Sale* product);
    void printProduct (Sale *product);
#endif