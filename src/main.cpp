#include <iostream>
#include "Grafo.hpp"





int main(void){

    Grafo g = Grafo();


    g.addVerticie(1, std::vector<int>{2, 3});

    g.addVerticie(2, std::vector<int>{1, 3});

    g.addVerticie(3, std::vector<int>{1, 2});


    g.printVertices();
    

    return 0;
}