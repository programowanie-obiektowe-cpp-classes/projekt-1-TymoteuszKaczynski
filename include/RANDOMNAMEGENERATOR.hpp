#pragma once
#ifndef P1_CPP_LAB_RANDOMNAMEGENERATOR_HPP
#define P1_CPP_LAB_RANDOMNAMEGENERATOR_HPP

#include <array>
#include <format>
#include <random>

inline constexpr std::array first_names{
    "Ann",
    "Andrew",
    "John",
    "Jane",
    "Bob",
    "Alice",
    "Bertram",
    "Monica",
    "Laura",
    "Eric",
    "Richard",
    "Karen",
    "Clara",
    "Rupert",
    "Bruce",
    "Martha",
    "Elizabeth",
    "Corey",
    "Nancy",
    "Joe",
    "Amy",
    "Mike",
    "James",
    "Naomi"
};

inline constexpr std::array last_names{
    "Hendricks",
    "Smith",
    "Gates",
    "Stein",
    "Warren",
    "Booker",
    "Williamson",
    "Walters",
    "Dunn",
    "Swanson",
    "Knope",
    "Haverford",
    "Ludgate",
    "Meagle",
    "Favreau",
    "Vietor",
    "Lovett",
    "Pfeifer",
    "Rhodes",
    "Abrams",
    "McFaul",
    "Stone",
    "Sisley",
    "Hanneman",
    "Holden",
    "Nagata"
};
inline constexpr std::array wydzialy{
    "Mechaniki",
    "Architektury",
    "Robotyki",
    "Chemii",
    "Fizyki",
    "Matematyki",
    "Budownictwa",
    "Transportu",    
};

inline auto GetRandomName() -> std::string {
    static auto prng = std::mt19937{std::random_device{}()};
    auto fnd = std::uniform_int_distribution<std::size_t>{0, first_names.size() - 1};
    auto lnd = std::uniform_int_distribution<std::size_t>{0, last_names.size() - 1};
    const auto first_name = first_names[fnd(prng)];
    const auto last_name = last_names[lnd(prng)];
    return std::format("{} {}", first_name, last_name);
}
inline auto GetRandomWydzial() -> std::string {
    static auto wdg = std::mt19937{std::random_device{}()};
    auto wd = std::uniform_int_distribution<std::size_t>{0, wydzialy.size() - 1};
    const auto wydzial = wydzialy[wd(wdg)];
    return std::format("{}", wydzial);
}
bool GenerateRandomBool() {
    
    std::random_device rd;    
    std::mt19937 gen(rd());   
    std::bernoulli_distribution dist(0.5); 
    return dist(gen); 
}
double GenerateRandomDouble(double min, double max) {
    std::random_device rd;   
    std::mt19937 gen(rd());   
    std::uniform_real_distribution<> dist(min, max); 
    return dist(gen);
}
int GenerateRandomInt(int min, int max) {
    std::random_device rd;   
    std::mt19937 gen(rd());  
    std::uniform_int_distribution<int> dist(min, max); 
    return dist(gen); 
}
#endif