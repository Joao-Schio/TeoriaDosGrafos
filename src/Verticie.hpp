#include <iostream>
#include <vector>
#include <tuple>


class Verticie{
    private:
        int id;
        std::vector<std::tuple<int,int>> vizinhos;
    public:
        Verticie();
        Verticie(int id);
        Verticie(int id, std::vector<std::tuple<int,int>> vizinhos);
        void addVizinho(std::tuple<int,int> aresta);
        int getId();
        std::vector<std::tuple<int,int>> getVizinhos();
};