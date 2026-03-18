

using System.Collections;
using System.Numerics;
using System.Security.AccessControl;
using arco;

namespace verticie;



record Verticie(int id, int grauEntrada, int grauSaida) : IComparable<Verticie> {
    public int Id { get; init; } = id;
    public int GrauEntrada {get; init; } = grauEntrada;
    public int GrauSaida {get; init; } = grauSaida;
    public List<Arco> Arcos {get; init; } = new();
    public void addArco(Arco arco){
        this.Arcos.Add(arco);
    }

    // how to add compare so that the sort function can be used
    public int CompareTo(Verticie? v) {
        if (v is null) {
            return 1; 
        }
        return this.Id - v.Id;
    }

}