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

void Grafo::addVerticie(int id, std::vector<std::tuple<int,int>> vizinhos){
    /**
     * funcao basica para adicionar verticies
    */
    Verticie v(id, vizinhos);
    vertices.push_back(v);
    numVertices++;
    numArestas += vizinhos.size(); 
}

void Grafo::printVertices(){
    /**
     * funcao basica para printar o grafo
    */
    for(unsigned i = 0; i < vertices.size(); i++){
        std::vector<std::tuple<int,int>> vizinhos = this -> vertices[i].getVizinhos();
        std::cout << "Verticie " << vertices[i].getId() << " tem vizinhos: ";
        for(unsigned j = 0; j < vizinhos.size(); j++){
            std::cout << std::get<0>(vizinhos[j]) << " " << "com custo " << std::get<1>(vizinhos[j]) << " ";
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

void Grafo::addVerticie(int id){
    // funcao basica para adicionar um verticie
    Verticie v(id);
    this -> vertices.push_back(v);
    this -> numVertices++;
}

void Grafo::addVizinho(int id, std::tuple<int,int> aresta){

    for(unsigned i = 0; i < vertices.size(); i++){
        if(vertices[i].getId() == id){ // como a ordem dos verticies nao é necessariamente na ordem do ID é  precisp procurar onde ele está
            vertices[i].addVizinho(aresta);
            return;
        }
    }
}

unsigned int Grafo::getNumVertices(){
    // boilerplate
    return this -> numVertices;
}


Verticie Grafo::getVerticie(int id){
    for(unsigned i = 0; i < vertices.size(); i++){
        if(vertices[i].getId() == id){
            return vertices[i];
        }
    }
    return Verticie(-1); // os ids sao sempre positivos portanto -1 significa que falhou
}