#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#include "../includes/auxFunctions.h"
#include "../includes/clients.h"
#include "../includes/products.h"
#include "../includes/sales.h"
#include "../includes/interface.h"

int main (void)
{
    short int choice;
    bool running = true;
    FILE* clientsFile, *productsFile, *salesFile;
    
    while (running)
    {
        clearScreen();
        mainInterface();
        scanf("%hi", &choice);
        clearScreen();

        if (choice == 1)
            registerproduct();
        else if (choice == 2)
            sell();
        else if (choice == 3)
            getIncome();
        else if (choice == 4)
        {
            bool highlightRunning = true;
            while (highlightRunning)
            {
                clearScreen();
                highlightsInterface();
                scanf("%hi", &choice);
                clearScreen();

                if (choice == 1)
                    getMostSoldProduct();
                else if (choice == 2)
                    getMostFrequentClient();
                else if (choice == 3)
                    getRichestClient();
                else if (choice == 985)
                    highlightRunning = false;
            }            
            choice = 0;
        }
        else if (choice == 5)
            updatePrice();
        else if (choice == 985)
            running = false;
        pauseScreen();
    }


    return 0;
}