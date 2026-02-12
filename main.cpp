#include <iostream>
#include <windows.h>
#include "sql_ops.h"

int main()
{
    char kontrol2, kontrol3;
    SetConsoleOutputCP(65001);
    sql_ops nesne1("veritabani.db");
    do
    {
        nesne1.sql_select();
        std::cout<<"Kayit eklemek istiyor musunuz: evet icin e harfine basiniz: ";
        std::cin>>kontrol2;
        if(toupper(kontrol2)=='E')
        {
            nesne1.sql_kayit();
        }
        std::cout<<"Devam etmek icin e harfine basiniz, cikmak icin herhangi bir harfe basiniz: ";
        std::cin>>kontrol3;
    }
    while(toupper(kontrol3)=='E');

        return 0;
}
