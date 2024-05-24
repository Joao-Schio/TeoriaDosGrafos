

namespace arco;

using verticie;




class Arco{
    Verticie destino;
    int custo;


    public Arco(){
        this.destino = new Verticie();
        this.custo = -1;
    }

    public Arco(Verticie verticie, int custo){
        this.destino = verticie;
        this.custo = custo;
    }

    public int getCusto(){
        return this.custo;
    }

    public Verticie getDestino(){
        return this.destino;
    }

}