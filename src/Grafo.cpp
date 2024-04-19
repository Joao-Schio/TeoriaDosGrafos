#include "Grafo.hpp"
#include <iostream>
#include <vector>




Grafo::Grafo(){
    numVertices = 0;
    numArestas = 0;
}

void Grafo::addVerticie(int id, std::vector<int> vizinhos){
    Verticie v(id, vizinhos);
    vertices.push_back(v);
    numVertices++;
    numArestas += vizinhos.size();
}

void Grafo::printVertices(){
    for(unsigned i = 0; i < vertices.size(); i++){
        std::cout << "Verticie " << vertices[i].getId() << " tem vizinhos: ";
        std::vector<int> vizinhos = vertices[i].getVizinhos();
        for(unsigned j = 0; j < vizinhos.size(); j++){
            std::cout << vizinhos[j] << " ";
        }
        std::cout << std::endl;
    }
}

