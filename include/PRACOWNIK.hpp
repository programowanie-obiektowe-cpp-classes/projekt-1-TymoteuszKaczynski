#pragma once
#include <iostream>
#include "RANDOMNAMEGENERATOR.hpp"


class PRACOWNIK {
protected:
    std::string imie;
    double wynagrodzenie;
public:
    PRACOWNIK() : imie(GetRandomName()) {}

    // std::string getName() const {
    //     return name;
    // }
    virtual void Print(){
        std::cout<<imie<<std::endl;
    }
    double getWynagrodzenie(){
        return wynagrodzenie;
    }

};

class INZ : public PRACOWNIK
{
    private:
        std::string wydzial = GetRandomWydzial(); // Dodac generator automatycznych wydzialow
       
    public:
        static constexpr double CI = 100;
        INZ() {
            wynagrodzenie = 6000;
        }
        void Print() override {
            std::cout<<imie<<" Wydzial: "<<wydzial<<" Wynagrodzenie: "<<wynagrodzenie<<" PLN"<<std::endl;
        }
};

class MKT : public PRACOWNIK
{
    private:
        int liczba_obserwojacych = GenerateRandomInt(0,10000); // mozna dac rand()
        
    public:
        static constexpr double CMkt = 200;
        MKT() {
            wynagrodzenie = 4000;
        }
        void Print() override {
            std::cout<<imie<<" Liczba obserwujacych: "<<liczba_obserwojacych<<" Wynagrodzenie: "<<wynagrodzenie<<" PLN"<<std::endl;
        }
};

class MAG : public PRACOWNIK
{
   private:
        bool obsloga_wozka = GenerateRandomBool(); 
    public:
        static constexpr double CMag = 50;
        MAG() {
            wynagrodzenie = 3500;
        }
        void Print() override {
            std::cout<<imie<<" Obsluga wozka widlowego: "<<obsloga_wozka<<" Wynagrodzenie: "<<wynagrodzenie<<" PLN"<<std::endl;
        }
};

class ROB : public PRACOWNIK
{
    private:
        double rozmiar_buta = GenerateRandomDouble(30,50);
    public:
        static  constexpr double CR = 20;
        ROB() {
            wynagrodzenie = 4500;
        }
        void Print() override {
            std::cout<<imie<<" Rozmiar buta: "<< rozmiar_buta <<" Wynagrodzenie: "<<wynagrodzenie<<" PLN"<<std::endl;
        }
};