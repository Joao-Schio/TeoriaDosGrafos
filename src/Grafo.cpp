#include "Grafo.hpp"
#include <iostream>
#include <vector>




Grafo::Grafo(){
    /**
     * definicao vazia
    */
    numVertices = 0;
    numArestas = 0;
}

void Grafo::addVerticie(int id, std::vector<std::tuple<Verticie*,int>> vizinhos){
    /**
     * funcao basica para adicionar verticies
    */
    Verticie* v = new Verticie(id, vizinhos);
    vertices.push_back(v);
    numVertices = vertices.size();
    numArestas += vizinhos.size(); 
}

void Grafo::printVertices(){
    /**
     * funcao basica para printar o grafo
    */
    for(unsigned i = 0; i < vertices.size(); i++){
        std::vector<std::tuple<Verticie*,int>> arcos = this -> vertices[i] -> getArcos();
        std::cout << "Verticie " << vertices[i] -> getId() << " tem vizinhos: ";
        for(unsigned j = 0; j < arcos.size(); j++){
            std::cout << std::get<0>(arcos[j]) -> getId() << " " << "com custo " << std::get<1>(arcos[j]) << " ";
        }
        std::cout << std::endl;
    }
}

void Grafo::setNumVertices(int numVertices){
    // boilerplate
    this -> numVertices = numVertices;
}

void Grafo::setNumArestas(int numArestas){
    // boilerplate
    this -> numArestas = numArestas;
}

void Grafo::addVerticie(int id, int grauEntrada, int grauSaida){
    // funcao basica para adicionar um verticie
    Verticie *v = new Verticie(id,grauEntrada, grauSaida);
    this -> vertices.push_back(v);
    this -> numVertices = vertices.size();
}

void Grafo::addArco(int id, int idFim, int custo){

    Verticie* fim = this -> getVerticie(idFim);
    std::tuple<Verticie*,int> arco = std::make_tuple(fim,custo);
    for(unsigned i = 0 ; i < this -> getNumVertices(); i++){
        if(this -> vertices.at(i) -> getId() == id){
            this -> vertices[i] -> addArco(arco);
            return;
        }
    }
}

unsigned int Grafo::getNumVertices(){
    // boilerplate
    return this -> numVertices;
}


Verticie* Grafo::getVerticie(int id){
    for(unsigned i = 0; i < vertices.size(); i++){
        if(vertices[i] -> getId() == id){
            return vertices[i];
        }
    }
    return new Verticie(-1,0,0); // os ids sao sempre positivos portanto -1 significa que falhou
}

std::vector<Verticie*>& Grafo::getVerticesVetor(){
    // coloquei o nome de vetor para deixar mais clara a diferenca entre o nome das funcoes
    return this -> vertices;
}

void Grafo::removeArco(int verticie, int vizinho){
    for(unsigned i = 0; i < this -> vertices.size(); i++){
        if(this -> vertices.at(i) -> getId() == verticie){
            std::vector<std::tuple<Verticie*,int>> arcos = vertices.at(i) -> getArcos();
            for(unsigned j = 0; j < arcos.size(); j++){
                if(std::get<0>(arcos.at(j)) -> getId() == vizinho){
                    arcos.erase(arcos.begin() + j);
                }
            }
        }
    }
}