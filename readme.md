# Trabalho da Disciplina de Linguagens de Programação I, UNEB

## *Nomenclatura*

    *int* nomeDaVariavel;
    *int*  nomeDaFuncao();
    *struct* EstrutruraDeDado;
    *#define* CONSTANTE;

## **Headers**

    ###*<Products.h>*

    ###*<Sales.h>*

        ####`void unloadCartNode (FILE* salesFile, Sale** cartNode, unsigned long int* date, unsigned long long int* cpf)`

            

        ####`void saleConfirmed (Sale** shoppingCart)`


        ####`long int registerSale (Sale** shoppingCart, unsigned long* currentDate, unsigned long long* clientCPF, float* totalBought, float* usedCredit)`

    ###*<Clients.h>*

        ####`void updateClient (unsigned long long* clientCPF, long* inClientAdress, long* inSalesAdress, float* totalBought)`

            Verifica se um cliente já está cadastrado, caso esteja, atualiza o número de visitas e o total comprado, caso contrário faz o cadastro.

        ####`long int searchForCPF (unsigned long long int* wantedCPF, long* inSalesAdress)`

            Confere se um CPF está presente no arquivo de clientes.

        ####`float getUsedCredit (unsigned long long* clientCPF, const long* inSalesAdress)`

            Inspecionar a quantidade de creditos que o cliente possui e perguntar se gostaria de usá-lo na compra corrente, caso afirmativo documenta no arquivo de vendas.

        ####`void getRichestClient (void)`

            Busca pelo cliente que mais comprou na loja.

        ####`void getMostFrequentClient (void)`

            Busca pelo cliente mais frequente na loja.

        ####`unsigned long long int askingForCPF (void)`

    ###*<AuxFunctions.h>*

        ####`void clearScreen (void)`

            Função que faz a limpeza da tela adaptada que pode ser adaptada para que funione em alguns sistemas operacionais( Windows, Linux, MacOS).
        
        ####`void pauseScreen (void)`

            Utilizada para simular uma pausa de tela.

        ####`void clearBuffer (void)`

            Realiza a limpeza do Buffer.

        ####`void checkPointerIntegrity (void* pointer)`

            Verifica se foi possivel alocar um ponteiro.

        ####`void checkFileIntegrity (FILE* file)`

            Verifica a existência de um  arquivo.

        Aqui serão encontradas funções auxiliares como Limpeza de tela, Limpeza de buffer

## *Arquivos*

    ###Products.txt

        unsigned long productCode; char* description; double price; unsigned int quantity\n
        %010lu;%s;%010.2lf;%010u\n

    ###Sales.txt

        unsigned long date; unsigned long long cpf; unsigned long productCode; unsigned int quantity;double price\n
        %lu;%011llu;%lu;%u;%010.2lf\n
      
    ###Clients.txt

        unsigned long long cpf; char* name; long firstAdress; unsigned int visits; double total\n
        %011llu;%s;%010ld;%010u;%010.2lf\n
