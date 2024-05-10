#include <iostream>
#include <vector>
#include <tuple>

/**
 * em um grafo orientado com custo as arestas sao definidas pelo trio ordenado
 * (VI, VF, Custo)
 * Onde VI e VF são verticies pertencentes ao conjunto V
 * e o arco se orienta de VI para VF
 * Matemáticamente o custo pode ser qualquer numero pertencente aos reais
 * porém para o contexto desse trabalho ele sempre será um inteiro
 * entre -1000 e 1000
*/

class Verticie{
    private:
        int id; // identificador do verticie
        std::vector<std::tuple<Verticie,int>> arcos; 
        /**
         * ja que o verticie ja tem o seu identificador não é preciso usar um trio ordenado
         * então eu vou usar uma tupla com duas posições como um par ordenado
         * onde a primeira posição é o ID do verticie destino e a segunda é
         * o custo do arco
        */
       int grauEntrada;
       int grauSaida;
    public:
        Verticie();
        Verticie(int id, int grauEntrada, int grauSaida);
        Verticie(int id, std::vector<std::tuple<Verticie,int>> arcos);
        void addArco(std::tuple<Verticie,int> aresta);
        int getId();
        std::vector<std::tuple<Verticie,int>> getArcos();
        bool igual(Verticie b);
        std::vector<std::tuple<Verticie,int>> *getArcosRef();
};