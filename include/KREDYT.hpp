#pragma once
#include <iostream>
#include <stdio.h>
#include <memory>
#include <cmath>

class KREDYT {
private:
    int pozostale_raty;
    double kwota_do_splaty;
    double oprocentowanie = 0.00;
public:
    double dlug;
public:
    KREDYT(double kwota, int ilosc_rat) : dlug(kwota), pozostale_raty(ilosc_rat) {
        if (ilosc_rat > 100)
        {std::cout<<"za duza ilosc rat"<<std::endl;}
             else
        {oprocentowanie=0.01*ilosc_rat;
            double q = 1 + oprocentowanie;
        kwota_do_splaty = dlug * pow(q, ilosc_rat) * (q - 1) / (pow(q, ilosc_rat) - 1); // wzór na ratę o stalej wartosci
        std::cout<<"do_splaty: "<<kwota_do_splaty<<"\n";}
    }

    double GetKosztRaty() {
        if (pozostale_raty == 0) {
            return 0.0;
        } else {
            dlug -= kwota_do_splaty; // aktualizacja pozostałego długu
            pozostale_raty--;
            if (dlug <=0)
            {
                dlug=0;
            }
            return kwota_do_splaty;
        }
    }
    double GetDlug()
    {return dlug;}
};