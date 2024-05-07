#include <iostream>
#include <vector>
#include "Verticie.hpp"


/**
 * Sabemos que matematicamente um grafo é o par ordenado entre o conjunto de verticies V
 * e o conjunto de arestas A, sendo definido como
 * G = (V,A)
 * 
*/


class Grafo{

    private:

        std::vector<Verticie> vertices; // Conjunto de verticies
        int numVertices; // Ordem do grafo
        int numArestas; 
    
    public:
        Grafo();
        void addVerticie(int id, std::vector<std::tuple<int,int>> vizinhos);
        void addVerticie(int id);
        void setNumVertices(int numVertices);
        void setNumArestas(int numArestas);
        void addVizinho(int id, std::tuple<int,int> aresta);
        void printVertices(); 
        unsigned int getNumVertices();
        Verticie getVerticie(int id);
};


