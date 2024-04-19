#include <iostream>
#include "Grafo.hpp"





int main(int argc, char **argv){

    Grafo g = Grafo();

    std::vector<std::tuple<int,int>> vizinhos1;
    vizinhos1.push_back(std::make_tuple(2, 1));
    vizinhos1.push_back(std::make_tuple(3, 1));
    g.addVerticie(1, vizinhos1);

    std::vector<std::tuple<int,int>> vizinhos2;

    vizinhos2.push_back(std::make_tuple(1, 1));

    g.addVerticie(2, vizinhos2);

    std::vector<std::tuple<int,int>> vizinhos3;

    vizinhos3.push_back(std::make_tuple(1, 1));

    g.addVerticie(3, vizinhos3);

    

    g.printVertices();
    

    return 0;
}