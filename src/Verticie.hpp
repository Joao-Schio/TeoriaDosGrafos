#include <iostream>
#include <vector>
#pragma once
#include "Arco.hpp"

/**
 * Desisti da tupla
 */


class Arco;
class Verticie{
    private:
        int id; // identificador do verticie
        std::vector<Arco> arcos; 
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
        Verticie(int id, std::vector<Arco> arcos);
        void addArco(Arco arco);
        int getId();
        std::vector<Arco> getArcos();
        std::vector<Arco> *getArcosRef();
        bool igual(Verticie b);
};