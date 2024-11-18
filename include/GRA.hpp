#pragma once
#include "FIRMA.hpp"
#include <utility>
class GRA {
private:
     static constexpr double M = 2;
public:
    FIRMA firma;
    GRA(){
        firma.Zatrudnij(std::move(std::make_unique<INZ>()));
        firma.Zatrudnij(std::move(std::make_unique<MKT>()));
        firma.Zatrudnij(std::move(std::make_unique<MAG>()));
        firma.Zatrudnij(std::move(std::make_unique<ROB>()));
        while (firma.GetStanKonta() > 0 && firma.ObliczWartoscFirmy()-firma.GetZadluzenie()<100000000 ){
            CzytajAkcje();
        }
         if (firma.GetStanKonta()<=0)
        {std::cout<<"przegrales"<<"\n";}
         if (firma.GetStanKonta()>100000000)
        {std::cout<<"wygrales"<<"\n";}
    };

    void Tick(){
        firma.Zaplac();   
        firma.Sprzedaj();     
        std::cout<<"Stan konta: "<<firma.GetStanKonta()<<std::endl; 
    }
    void CzytajAkcje(){
        std::string akcja;
        std::cout<<std::endl<<"Podaj akcje do wykonania:";
        std::cin>>akcja;
        if (akcja == "zinz"){
            firma.Zatrudnij(std::move(std::make_unique<INZ>()));
        }
        else if (akcja == "zmkt"){
            firma.Zatrudnij(std::move(std::make_unique<MKT>()));
        }
        else if (akcja == "zmag"){
            firma.Zatrudnij(std::move(std::make_unique<MAG>()));
        }
        else if (akcja == "zrob"){
            firma.Zatrudnij(std::move(std::make_unique<ROB>()));
        }
        else if (akcja == "lp"){
            firma.DrukujPracownikow();
        }
        else if (akcja == "kred"){
            double kwota;
            double czas_splaty;
            std::cout<<"Podaj kwote kredytu:";
            std::cin>>kwota;
            std::cout<<"Podaj ilosc rat:";
            std::cin>>czas_splaty;
            if (firma.GetZadluzenie()>firma.ObliczWartoscFirmy()*M)
            { std::cout<< "wartosc zadluzenia przekracza wartosc firmy"<<std::endl;}
            else {firma.WezKredyt(kwota, czas_splaty);}
        }
        else if (akcja == "zk"){
            //konczy gre natychmiast
            firma.ZmienStanKonta();
        }
        else if (akcja == "kt"){
            //konczy ture
            Tick();
        }
        else if (akcja == "an")
        {
            //daje analize przychodow i kosztow z ostatniego miesiaca
            firma.AnalizaKosztow();
        }
    }     
};