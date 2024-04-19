#include <iostream>
#include <vector>



class Verticie{
    private:
        int id;
        std::vector<int> vizinhos;
    public:
        Verticie();
        Verticie(int id);
        Verticie(int id, std::vector<int> vizinhos);
        void addVizinho(int id);
        int getId();
        std::vector<int> getVizinhos();
};