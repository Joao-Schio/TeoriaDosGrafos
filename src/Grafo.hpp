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
        void printVertices(); // para deixar meu debug mais facil
};


