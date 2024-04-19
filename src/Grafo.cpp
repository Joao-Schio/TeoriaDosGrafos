#include "Grafo.hpp"
#include <iostream>
#include <vector>




Grafo::Grafo(){
    numVertices = 0;
    numArestas = 0;
}

void Grafo::addVerticie(int id, std::vector<std::tuple<int,int>> vizinhos){
    Verticie v(id, vizinhos);
    vertices.push_back(v);
    numVertices++;
    numArestas += vizinhos.size();
}

void Grafo::printVertices(){
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
    this -> numVertices = numVertices;
}

void Grafo::setNumArestas(int numArestas){
    this -> numArestas = numArestas;
}

void Grafo::addVerticie(int id){
    Verticie v(id);
    this -> vertices.push_back(v);
    this -> numVertices++;
}

void Grafo::addVizinho(int id, std::tuple<int,int> aresta){
    for(unsigned i = 0; i < vertices.size(); i++){
        if(vertices[i].getId() == id){
            vertices[i].addVizinho(aresta);
            break;
        }
    }
}