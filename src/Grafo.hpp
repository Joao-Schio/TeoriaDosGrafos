#include <iostream>
#include <vector>
#pragma once
#include "Verticie.hpp"

/**
 * Sabemos que matematicamente um grafo é o par ordenado entre o conjunto de verticies V
 * e o conjunto de arestas A, sendo definido como
 * G = (V,A)
 * 
*/


class Grafo{

    private:

        std::vector<Verticie*> vertices; // Conjunto de verticies
        int numVertices; // Ordem do grafo
        int numArcos; 
    
    public:
        Grafo(int vertices, int arcos);
        void addVerticie(int id, int grauEntrada, int grauSaida);
        void setNumVertices(int numVertices);
        void setNumArcos(int numArestas);
        void addArco(int id, int idFim, int custo);
        void printVertices(); 
        int getNumVertices();
        Verticie* getVerticie(int id);
        std::vector<Verticie*> getVerticesVetor();
        void removeArco(int verticie, int vizinho);
        void setVerticieVetor(std::vector<Verticie*> v);
        ~Grafo();
};


