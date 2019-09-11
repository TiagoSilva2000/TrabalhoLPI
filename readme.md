# Trabalho da Disciplina de Linguagens de Programação I, UNEB

## *Nomenclatura*

    *int* nomeDaVariavel;
    *int*  nomeDaFuncao();
    *struct* EstrutruraDeDado;
    *#define* CONSTANTE;

## **Headers**

 ### *<Products.h>*

 ### *<Sales.h>*

        `void unloadCartNode (FILE* salesFile, Sale** cartNode, unsigned long int* date, unsigned long long int* cpf)`

        `void saleConfirmed (Sale** shoppingCart)`

        `void unloadCartNode (Sale** currentNode)`

        `long int registerSale (Sale** shoppingCart, unsigned long* currentDate, unsigned long long* clientCPF, float* totalBought, float* usedCredit)`

 ### *<Clients.h>*

        `void updateClient (unsigned long long* clientCPF, long* inClientAdress, long* inSalesAdress, float* totalBought)`

        `long int searchForCPF (unsigned long long int* wantedCPF, long* inSalesAdress)`

        `void getRichestClient (void)`

        `void getMostFrequentClient (void)`

        `unsigned long long int askingForCPF (void)`

 ### *<AuxFunctions.h>*
        Aqui serão encontradas funções auxiliares como Limpeza de tela, Limpeza de buffer

## *Arquivos*

 ### Products.txt

        unsigned long productCode; char* description; double price; unsigned int quantity\n
        %010lu;%s;%010.2lf;%010u\n

 ### Sales.txt

        unsigned long date; unsigned long long cpf; unsigned long productCode; unsigned int quantity;double price\n
        %lu;%011llu;%lu;%u;%010.2lf\n
      
 ### Clients.txt

        unsigned long long cpf; char* name; long firstAdress; unsigned int visits; double total\n
        %011llu;%s;%010ld;%010u;%010.2lf\n
