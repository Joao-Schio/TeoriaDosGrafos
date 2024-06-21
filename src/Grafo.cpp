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

void Grafo::addVerticie(int id, std::vector<Arco> vizinhos){
    /**
     * funcao basica para adicionar verticies
    */
    Verticie *v = new Verticie(id, vizinhos);
    vertices.push_back(v);
    numVertices = vertices.size();
    numArestas += vizinhos.size(); 
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

void Grafo::setNumArestas(int numArestas){
    // boilerplate
    this -> numArestas = numArestas;
}

void Grafo::addVerticie(int id, int grauEntrada, int grauSaida){
    // funcao basica para adicionar um verticie
    Verticie *v = new Verticie(id, grauEntrada, grauSaida);
    this -> vertices.push_back(v);
    this -> numVertices = vertices.size();
}

void Grafo::addArco(int id, int idFim, int custo){
    Verticie *origem;
    Verticie *fim;
    for(unsigned i = 0; i < this -> vertices.size(); i++){
        if(this -> vertices.at(i) -> getId() == id){
            origem = this -> vertices.at(i);
        }
        if(this -> vertices.at(i) -> getId() == idFim){
            fim = this -> vertices.at(i);
        }
    }
    Arco arco(fim, custo);
    origem -> addArco(arco);
    this -> numArestas++;
}

unsigned int Grafo::getNumVertices(){
    // boilerplate
    return this -> numVertices;
}


Verticie* Grafo::getVerticie(int id){

    for(unsigned i = 0; i < this -> vertices.size(); i++){
        if(this -> vertices.at(i) -> getId() == id){
            return (this -> vertices.at(i));
        }
    }
    return nullptr;
}

std::vector<Verticie*> Grafo::getVerticesVetor(){
    // coloquei o nome de vetor para deixar mais clara a diferenca entre o nome das funcoes
    return this -> vertices;
}

void Grafo::removeArco(int verticie, int vizinho){
    for(unsigned i = 0; i < this -> vertices.size(); i++){
        if(this -> vertices.at(i) -> getId() == verticie){
            std::vector<Arco> *arcos = vertices.at(i) -> getArcosRef();
            for(unsigned j = 0; j < arcos -> size(); j++){
                if(arcos -> at(j).getDestino() -> getId() == vizinho){
                    arcos -> erase(arcos -> begin() + j);
                }
            }
        }
    }
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