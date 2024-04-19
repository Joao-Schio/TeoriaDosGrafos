#include <iostream>
#include <vector>
#include "Verticie.hpp"


class Grafo{

    private:
        std::vector<Verticie> vertices;
        int numVertices;
        int numArestas;
    
    public:
        Grafo();
        void addVerticie(int id, std::vector<std::tuple<int,int>> vizinhos);
        void addVerticie(int id);
        void setNumVertices(int numVertices);
        void setNumArestas(int numArestas);
        void addVizinho(int id, std::tuple<int,int> aresta);
        void printVertices(); // para deixar meu debug mais facil
};


