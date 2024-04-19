#include "Verticie.hpp"
#include <iostream>
#include <vector>





Verticie::Verticie(){
    this -> id = -1;
    this -> vizinhos = std::vector<std::tuple<int,int>>();
}

Verticie::Verticie(int id){
    this -> id = id;
    this -> vizinhos = std::vector<std::tuple<int,int>>();
}

Verticie::Verticie(int id, std::vector<std::tuple<int,int>> vizinhos){
    this -> id = id;
    this -> vizinhos = vizinhos;
}

void Verticie::addVizinho(std::tuple<int,int> aresta){
    this -> vizinhos.push_back(aresta);
}

int Verticie::getId(){
    return this -> id;
}

std::vector<std::tuple<int,int>> Verticie::getVizinhos(){
    return this -> vizinhos;
}

