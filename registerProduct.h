bool checkDate (char* input_date)
{   
    if (strlen(input_date) != 8)
        return false;

    int year = 0, month = 0, day = 0;

    for(int i = 0, value = 1000; i < 4; i++, value /= 10)
        year += ((input_date[i] - '0') * value);
    month = ((input_date[4] - '0') * 10) + (input_date[5] - '0');
    day = ((input_date[6] - '0') * 10) + (input_date[7] - '0');

    if (year < CURRENT_YEAR)
        return false;
    else if (month > 12 || month < 1)
        return false;
    else if (day < 0 || day > 31)
        return false;

    return true;
}

void askForInput (int query, New_product &item)
{
    if (query == 1)
    {
        system("cls");
        printf("Please, enter the code of the new product:\n");
        scanf ("%i", &item.id_code);
        system("cls");
        clear_buffer();
    }
    else if (query == 2)
    {
        printf("Please, enter its description:\n");
        scanf("%100[^\n]s", item.description);
        system("cls");
        clear_buffer();
    }
    else if (query == 3)
    {
        do {
            printf("Please, enter the quantity of the new product:\n");
            scanf("%i", &item.qnt);
            system("cls");
            clear_buffer();
        } while (item.qnt < 0);

    }
    else if (query == 4)
    {
        do {
            printf("Please, enter its price: ");
            scanf("%lf", &item.price);
            system("cls");
            clear_buffer();
        } while (item.price < 0);
    }
    else if (query == 5)
    {
        bool theDateIsRight;
        do{
            printf("Please, enter its expiration date (YYYYMMDD):\n");
            scanf("%s", item.expDate);
            system("cls");
            clear_buffer();
            theDateIsRight = checkDate(item.expDate);

            if (!theDateIsRight)
            {
                printf("The previous date was inacurrate. Please, correct it.\n");
                getchar();
                system("cls");
            }
         } while (!theDateIsRight);

    }

}

bool getNewProductInfo (FILE* products)
{   
    New_product item; // objeto instanciado para armazenar temporariamente os dados do novo produto a ser adicionado.
    int iWantToCorrect = 0; // variável inteira para verificar se o usuário quer, ou não, corrigir alguma informação adicionada.
    int selection; // variável para escolher qual informaçãos será corrigida.

    for(int i = 1; i <= 5; i++)
        askForInput(i, item);

    do {
        system("cls");
        printf("The following informations were entered:\n");    
        printf("%i\n%s\n%i\n%.2lf\n%s\n", item.id_code, item.description, item.qnt, item.price, item.expDate);
        
        printf("\nDo you want to correct any data that was entered? 0 - No / Any other number - Yes\n");
        scanf("%i", &iWantToCorrect);
        if (iWantToCorrect)
        {
            do {
                printf ("Which one?\n1 - ID Code\n2 - Description\n3 - Quantity\n4 - Price\n5 - Expiration Date\n");
                scanf("%i", &selection);

                if (selection >= 1 && selection <= 5)
                    askForInput(selection, item);
                else
                {
                    printf("Please, enter a possible answer:");
                    getchar();
                    system("cls");
                }

            } while (selection <= 1 && selection >= 5); 
        }
    } while (iWantToCorrect != 0);
    
    fprintf(products, "%i;%s;%i;%.2lf;%s;\n", item.id_code, item.description, item.qnt, item.price, item.expDate);
    
    return true;
}