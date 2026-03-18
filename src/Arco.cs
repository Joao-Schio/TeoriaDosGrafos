

namespace arco;

using verticie;




struct Arco(Verticie verticie, int custo) {
    public Verticie Destino { get; set; } = verticie;
    public int Custo { get; set; } = custo;

}