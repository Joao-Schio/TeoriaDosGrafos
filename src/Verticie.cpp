#include "Verticie.hpp"
#include <iostream>
#include <vector>





Verticie::Verticie(){
    this -> id = -1;
    this -> vizinhos = std::vector<int>();
}

Verticie::Verticie(int id){
    this -> id = id;
    this -> vizinhos = std::vector<int>();
}

Verticie::Verticie(int id, std::vector<int> vizinhos){
    this -> id = id;
    this -> vizinhos = vizinhos;
}

void Verticie::addVizinho(int id){
    this -> vizinhos.push_back(id);
}

int Verticie::getId(){
    return this -> id;
}

std::vector<int> Verticie::getVizinhos(){
    return this -> vizinhos;
}

