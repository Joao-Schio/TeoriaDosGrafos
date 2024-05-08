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
        void addVerticie(int id, std::vector<std::tuple<Verticie,int>> vizinhos);
        void addVerticie(int id, int grauEntrada, int grauSaida);
        void setNumVertices(int numVertices);
        void setNumArestas(int numArestas);
        void addArco(int id, int idFim, int);
        void printVertices(); 
        unsigned int getNumVertices();
        Verticie getVerticie(int id);
        std::vector<Verticie> getVerticesVetor();
};


