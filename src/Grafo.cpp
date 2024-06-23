#include "Grafo.hpp"
#include <iostream>
#include <vector>




Grafo::Grafo(int vertices, int arcos){
    this -> numArcos = arcos;
    this -> numVertices = vertices;
    this -> vertices  = std::vector<Verticie*>(numVertices);
}


void Grafo::printVertices(){
    /**
     * funcao basica para printar o grafo
    */
    for(unsigned i = 0; i < vertices.size(); i++){
        std::vector<Arco> arcos = this -> vertices.at(i) -> getArcos();
        std::cout << vertices.at(i) -> getId() << " ";
        for(unsigned j = 0; j < arcos.size(); j++){
            std::cout << arcos[j].getDestino() -> getId() << " " << arcos[j].getCusto() << " ";
        }
        std::cout << std::endl;
    }
}

void Grafo::setNumVertices(int numVertices){
    // boilerplate
    this -> numVertices = numVertices;
}

void Grafo::setNumArcos(int numArestas){
    // boilerplate
    this -> numArcos = numArestas;
}

void Grafo::addVerticie(int id, int grauEntrada, int grauSaida){
    // funcao basica para adicionar um verticie
    Verticie *v = new Verticie(id, grauEntrada, grauSaida);
    this -> vertices.at(v -> getId()) = v;
    this -> numVertices = vertices.size();
}

void Grafo::addArco(int id, int idFim, int custo){
    Verticie *origem = this -> vertices.at(id);
    Verticie *fim = this -> vertices.at(idFim);
    Arco arco(fim, custo);
    origem -> addArco(arco);
    // Nao vou aumentar o numero de arcos pois o construtor padrao ja define ele levando em consideração todos os arcos
}

int Grafo::getNumVertices(){
    // boilerplate
    return this -> numVertices;
}


Verticie* Grafo::getVerticie(int id){
    // como na insercao o vetor é tratado como uma tabela de dispersão
    // pode-se considerar que v[i] = VerticeI
    return (this -> vertices.at(id));
}

std::vector<Verticie*> Grafo::getVerticesVetor(){
    // coloquei o nome de vetor para deixar mais clara a diferenca entre o nome das funcoes
    return this -> vertices;
}

void Grafo::setVerticieVetor(std::vector<Verticie*> v){
    this -> vertices = v;
}


Grafo::~Grafo(){
    // boilerplate
    for(unsigned i = 0; i < this -> vertices.size(); i++){
        delete this -> vertices.at(i);
    }
}