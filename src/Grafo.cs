


namespace grafo;

using System.Collections;
using arco;
using verticie;



class Grafo{
    ArrayList verticies;
    int numVerticies;
    int numArestas;

    public Grafo(){
        this.verticies = new ArrayList();
        this.numArestas = 0;
        this.numVerticies = 0;
    }

    public Grafo(int numArestas, int numVerticies){
        this.numArestas = numArestas;
        this.numVerticies = numVerticies;
        this.verticies =  new ArrayList();
    }

    public void addVerticie(int id, int grauEntrada, int grauSaida){
        Verticie v = new Verticie(id,grauEntrada,grauSaida);
        verticies.Add(v);
    }
    public Verticie? getVerticie(int id){
        foreach(Verticie v in verticies){
            if(v.getId() == id){
                return v;
            }
        }
        return null;
    }
    public void addArco(int origem, int destino, int custo){
        Verticie? fim = getVerticie(destino);
        if(fim != null){
            Arco a = new Arco(fim, custo);
            foreach(Verticie v in verticies){
                if(v.getId() == origem){
                    v.addArco(a);
                }
            }
        }
    }

    public ArrayList getVerticies(){
        return this.verticies;
    }

    public void setNumVerticies(int numVerticies){
        this.numVerticies = numVerticies;
    }
    public void setNumArestas(int numArestas){
        this.numArestas = numArestas;
    }

    public void print(){
        foreach(Verticie v in verticies){
            Console.WriteLine("Verticie: " + v.getId());
            ArrayList arcos = v.getArcos();
            foreach(Arco a in arcos){
                Console.WriteLine("Arco: " + a.getDestino().getId() + " Custo: " + a.getCusto());
            }
        }
    }

    public int getNumVerticies(){
        return this.numVerticies;
    }
    public int getNumArestas(){
        return this.numArestas;
    }
    
}