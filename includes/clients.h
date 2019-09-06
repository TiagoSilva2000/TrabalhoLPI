#ifndef CLIENTS_H
#define CLIENTS_H
#include "sales.h"

    #define CREDITS_CONVERT_TAX 0.005
    #define ANONYMOUS_CODE 0
    #define NOT_EXISTS -1

    void saleConfirmed (Sale** shoppingCart);
    void getRichestClient (void);
    void getMostFrequentClient (void);

#endif