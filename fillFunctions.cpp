#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>

unsigned long int genProdCode (std::vector<unsigned long int>& codeMap)
{
    unsigned long int generatedCode = (rand() % 100000) + 1;

    for (size_t i = 0; i < codeMap.size(); i++)
        if (generatedCode == codeMap[i])
            genProdCode(codeMap);    

    codeMap.push_back(generatedCode);
    return rand();
} 

std::string genProdName (void)
{
    int strsize = (rand () % 30) + 5;
    std::string name;

    for (size_t i = 0; i < strsize; i++)
        name.push_back((rand() % ('z' - 'a' + 1)) + 'a');
    
    return name;
}

float genProdPrice (void)
{
    float num = (rand() % 1000), 
    dec = (rand() % 100);
    dec = (dec/100.0);

    return num + dec;
}

void fillProducts (void)
{
    FILE* pFile = fopen ("./files/products.txt", "a+");
    // std::ofstream pFile ("./files/products.txt", std::ofstream::ate);
    int n;
    std::vector<unsigned long int> codeMap;

    scanf("%i", &n);
    for (size_t i = 0; i < n; i++)
        fprintf(pFile, "%010lu;%s;%010.2lf;%010u\n", genProdCode(codeMap), genProdName().c_str(), genProdPrice (), 0);

    fclose(pFile);
}

unsigned long long int genCPF (void)
{
    unsigned long long int cpf = 0;
    unsigned long long int modifier = 1;

    for (size_t i = 0; i < 11; i++)
    {
        cpf += (rand() % 10) * modifier;
        modifier *= 10;
    }
    

    return cpf;
}

unsigned int genQnt (void)
{return (rand() % 15) + 1;}


unsigned long int datePlusPlus (unsigned long int currentDate)
{
    unsigned int year, month, day;
    bool carry = 0;

    year = currentDate / 10000;
    currentDate %= 10000;
    month = currentDate / 100;
    currentDate %= 100;
    day = currentDate;

    day++;
    if (day > 30)
    {
        day = 1;
        carry = 1;
    }

    month += carry;
    carry = 0;
    if (month > 12)
    {
        month = 1;
        carry = 1;
    }

    year += carry;

    return (year * 10000) + (month * 100) + (day);
}

void fillSales (void)
{
    std::ofstream sFile ("./files/sales.txt", std::ofstream::ate);    
    int n, p;
    unsigned long int currentDate = 20161015;
    
    
    scanf("%i", &n);
    sFile.precision(2);
    while (n)
    {
        currentDate = datePlusPlus(currentDate);
        p = (rand() % 10);
        while (p)
        {
            sFile << currentDate << ';' << genCPF() << ";" << 33333 << ';' << genQnt() << ';' << (genProdPrice() / 10) << '\n';
            p--;
        }
        n--;
    }


}

int main (void)
{
    srand(time(NULL));
    fillProducts();
    // fillSales();


    return 0;
}