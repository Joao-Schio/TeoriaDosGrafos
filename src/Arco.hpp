#pragma once // para evitar usar ifndef e endif
#include "Verticie.hpp"



class Verticie;


class Arco{
    private:
        Verticie *destino;
        int custo;
    public:
        Arco(Verticie *destino, int custo);
        Verticie *getDestino();
        int getCusto();
        void setDestino(Verticie *destino);
        void setCusto(int custo);
        int getIdDestino();
};
