#include "Verticie.hpp"
#include <iostream>
#include <vector>





Verticie::Verticie(){
    this -> id = -1;
    this -> arcos = std::vector<std::tuple<int,int>>();
}

Verticie::Verticie(int id){
    this -> id = id;
    this -> arcos = std::vector<std::tuple<int,int>>();
}

Verticie::Verticie(int id, std::vector<std::tuple<int,int>> arcos){
    this -> id = id;
    this -> arcos = arcos;
}

void Verticie::addArco(std::tuple<int,int> arco){
    this -> arcos.push_back(arco);
}

int Verticie::getId(){
    return this -> id;
}

std::vector<std::tuple<int,int>> Verticie::getArcos(){
    return this -> arcos;
}

