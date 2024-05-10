#include "Verticie.hpp"
#include <iostream>
#include <vector>





Verticie::Verticie(){
    this -> id = -1;
    this -> arcos = std::vector<std::tuple<Verticie,int>>();
}

Verticie::Verticie(int id, int grauEntrada, int grauSaida){
    this -> id = id;
    this -> grauEntrada = grauEntrada;
    this -> grauSaida = grauSaida;
    this -> arcos = std::vector<std::tuple<Verticie,int>>();
}

Verticie::Verticie(int id, std::vector<std::tuple<Verticie,int>> arcos){
    this -> id = id;
    this -> arcos = arcos;
}

void Verticie::addArco(std::tuple<Verticie,int> arco){
    this -> arcos.push_back(arco);
}

int Verticie::getId(){
    return this -> id;
}

std::vector<std::tuple<Verticie,int>> Verticie::getArcos(){
    return this -> arcos;
}

bool Verticie::igual(Verticie b){
    return this -> getId() == b.getId() && this -> arcos.size() == b.getArcos().size();
}

std::vector<std::tuple<Verticie,int>>* Verticie::getArcosRef(){
    return &(this -> arcos);
}
