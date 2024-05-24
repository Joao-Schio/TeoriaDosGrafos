

using System.Collections;
using System.Numerics;
using System.Security.AccessControl;
using arco;

namespace verticie;



class Verticie{
    int id;
    int grauEntrada;
    int grauSaida;
    ArrayList arcos;

    public Verticie(){
        this.id = -1;
        this.grauEntrada = 0;
        this.grauSaida = 0;
        this.arcos = new ArrayList();
    }

    public Verticie(int id, int grauEntrada, int grauSaida){
        this.id = id;
        this.grauEntrada = grauEntrada;
        this.grauSaida = grauSaida;
        this.arcos = new ArrayList();;
    }

    public void addArco(Verticie destino, int custo){
        Arco novo = new Arco(destino,custo);
        arcos.Add(novo);
    }

    public void addArco(Arco arco){
        this.arcos.Add(arco);
    }

    public int getId(){
        return this.id;
    }
    public ArrayList getArcos(){
        return this.arcos;
    }

    // how to add compare so that the sort function can be used
    public bool Comparer(Verticie v){
        return v.getId() < this.id;
    }

}