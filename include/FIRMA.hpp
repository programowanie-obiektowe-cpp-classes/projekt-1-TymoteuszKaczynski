#pragma once
#include <iostream>
#include "Pracownik.hpp"
#include "KREDYT.hpp"
#include <stdio.h>
#include <variant>
#include <memory>
#include <algorithm>

class FIRMA {
private:
    double stan_konta;
    int ilosc_kredytow;
    int ilosc_pracownikow;
    int licznik_miesiecy;
    double pojemnosc;
    double produkty;
    double popyt;
    double produkty_na_magazynie=0;
    std::unique_ptr<std::unique_ptr<PRACOWNIK>[]> pracownicy = std::make_unique<std::unique_ptr<PRACOWNIK>[]>(50);
    std::unique_ptr<std::unique_ptr<KREDYT>[]> kredyty = std::make_unique<std::unique_ptr<KREDYT>[]>(10);
    std::unique_ptr<double[]> historia_przychodow = std::make_unique<double[]>(10000);

public:
    FIRMA() : stan_konta(100000), ilosc_kredytow(0), ilosc_pracownikow(0), pojemnosc(0), produkty(0), popyt(0), licznik_miesiecy(0) {}

    void WezKredyt(double kwota, int czas_splaty) {
        if (ilosc_kredytow <= 20) {
            kredyty[ilosc_kredytow] = std::make_unique<KREDYT>(kwota, czas_splaty);
            ilosc_kredytow++;
        } else {
            std::cout << "Za duzo kredytow." << std::endl;
        }
    }
   
    double GetZadluzenie()
    {
          double zadluzenie = 0.0;
    for (int i = 0; i < ilosc_kredytow; ++i) {
                zadluzenie += kredyty[i]->GetDlug();
        
    }
       return zadluzenie;
    }

    void Zatrudnij(std::unique_ptr<PRACOWNIK> pracownik) {
        if (ilosc_pracownikow < 50) {
            pracownicy[ilosc_pracownikow] = std::move(pracownik);
            ilosc_pracownikow++;
        } else {
            std::cout << "Za duzo pracownikow.";
        }
    }

    void DrukujPracownikow() const {
        for (size_t i = 0; i < ilosc_pracownikow; ++i) {
            if (pracownicy[i]) {
                pracownicy[i]->Print();
            }
        }
    }

    void Zaplac() {
        //pensje
        for (size_t i = 0; i < ilosc_pracownikow; ++i) {
            if (pracownicy[i]) {
                stan_konta -= pracownicy[i]->getWynagrodzenie();
            }
        }
        //raty
         double wszystkie_raty = 0.0;
        for (int i = 0; i < ilosc_kredytow; ++i) {
            wszystkie_raty += kredyty[i]->GetKosztRaty();
        }
        stan_konta -= wszystkie_raty;
    }
 
    double GetStanKonta() const {
        return stan_konta;
    }

    void ZmienStanKonta() {
        stan_konta -= 10000000;
    }

    
    double ObliczWartoscFirmy(){
        int N = std::min(licznik_miesiecy, 3); // ilosc miesiecy do sredniej
    if (N == 0) { //sprawdzenie dla granicznego przypadku
        return 0.0; 
    }

    double aktualna_wartosc_firmy = 0;
    for (int i = licznik_miesiecy - 1; i >= licznik_miesiecy - N; --i) {
        aktualna_wartosc_firmy += historia_przychodow[i];
    }

    std::cout << "wartosc spolki " << aktualna_wartosc_firmy << std::endl;
    return aktualna_wartosc_firmy / N;
       }

    void Sprzedaj() {
        pojemnosc = 0;
        produkty = 0;
        popyt = 0;

        // obliczanie pojemnosci magazynu
        for (size_t i = 0; i < ilosc_pracownikow; ++i) {
            if (pracownicy[i]) {
                MAG* magPtr = dynamic_cast<MAG*>(pracownicy[i].get());
                if (magPtr) {
                    pojemnosc += MAG::CMag;  
                }
            }
        }
    std::cout << "pojemnosc magazynu wynosi "<< pojemnosc << std::endl;
        // obliczanie ilosci wyprodukowancyh produktow
        for (size_t i = 0; i < ilosc_pracownikow; ++i) {
            if (pracownicy[i]) {
                ROB* robPtr = dynamic_cast<ROB*>(pracownicy[i].get());
                if (robPtr) {
                    produkty += ROB::CR;  
                }
            }
        }
            produkty_na_magazynie = std::min(produkty_na_magazynie + produkty, pojemnosc);
        //drukowanie teoretycznej wartosci produkcji z uwzglednieniem nadprodukcji 
         std::cout << "wyprodukowano produktow "<< produkty << std::endl;
        // obliczanie popytu
        for (size_t i = 0; i < ilosc_pracownikow; ++i) {
            if (pracownicy[i]) {
                MKT* mktPtr = dynamic_cast<MKT*>(pracownicy[i].get());
                if (mktPtr) {
                    popyt += MKT::CMkt;  
                }
            }
        }
    std::cout << "popyt wynosi "<< popyt << std::endl;

        double sprzedane_produkty = std::min(popyt, produkty_na_magazynie);
        
        double ilosc_inzynierow = 0;
            for (size_t i = 0; i < ilosc_pracownikow; ++i) {
            if (pracownicy[i]) {
                INZ* inzPtr = dynamic_cast<INZ*>(pracownicy[i].get());
                if (inzPtr) {
                    ilosc_inzynierow += 1;
                }
            }
        }
    std::cout << "wartosc produktu wynosi "<< ilosc_inzynierow * INZ::CI << std::endl;
        historia_przychodow[licznik_miesiecy] = sprzedane_produkty * ilosc_inzynierow * INZ::CI; 
        stan_konta += historia_przychodow[licznik_miesiecy];
        licznik_miesiecy++;
        produkty_na_magazynie-=sprzedane_produkty;
    std::cout << "sprzedano produktow: "<< sprzedane_produkty << std::endl;
    std::cout << "W magazynie zostalo "<< produkty_na_magazynie<<" produktow"<< std::endl;
    }

    void AnalizaKosztow()
    {
        //drukowanie kredytow
        double wszystkie_raty = 0.0;
        for (int i = 0; i < ilosc_kredytow; ++i) {
            wszystkie_raty += kredyty[i]->GetKosztRaty();
        }
        std::cout<<"koszt kredytu: "<< wszystkie_raty << std::endl; 
        //drukowanie plac
        double suma_pensji=0;
         for (size_t i = 0; i < ilosc_pracownikow; ++i) {
            if (pracownicy[i]) {
                suma_pensji += pracownicy[i]->getWynagrodzenie();
            }
        }
        std::cout<<"koszt pensji: "<< suma_pensji << std::endl; 
       
        std::cout <<"przychod z tego miesiaca "<<historia_przychodow[licznik_miesiecy-1]<< std::endl;
        }
};