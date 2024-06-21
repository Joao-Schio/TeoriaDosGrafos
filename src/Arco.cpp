#include "Arco.hpp"


Arco::Arco(Verticie *destino, int custo){
    this -> destino = destino;
    this -> custo = custo;
}

Verticie *Arco::getDestino(){
    return this -> destino;
}

int Arco::getCusto(){
    return this -> custo;
}

void Arco::setDestino(Verticie *destino){
    this -> destino = destino;
}

void Arco::setCusto(int custo){
    this -> custo = custo;
}

int Arco::getIdDestino(){
    return this -> destino -> getId();
}

