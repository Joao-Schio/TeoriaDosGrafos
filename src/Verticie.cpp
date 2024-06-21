#include "Verticie.hpp"
#include <iostream>
#include <vector>





Verticie::Verticie(){
    this -> id = -1;
    this -> arcos = std::vector<Arco>();
}

Verticie::Verticie(int id, int grauEntrada, int grauSaida){
    this -> id = id;
    this -> grauEntrada = grauEntrada;
    this -> grauSaida = grauSaida;
    this -> arcos = std::vector<Arco>();
}

Verticie::Verticie(int id, std::vector<Arco> arcos){
    this -> id = id;
    this -> arcos = arcos;
}

void Verticie::addArco(Arco arco){
    this -> arcos.push_back(arco);
}

int Verticie::getId(){
    return this -> id;
}

std::vector<Arco> Verticie::getArcos(){
    return this -> arcos;
}

bool Verticie::igual(Verticie b){
    return this -> getId() == b.getId();
}

std::vector<Arco>* Verticie::getArcosRef(){
    return &(this -> arcos);
}

