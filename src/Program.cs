




using grafo;

using System.IO;
using System.Numerics;
using System;
using System.Collections;
using verticie;
using arco;
using System.Runtime.Serialization;
public class Program{

    static void merge(ArrayList a, int inicio, int meio, int fim){
        ArrayList b = new ArrayList();
        int i = inicio;
        int j = meio + 1;
        while(i <= meio && j <= fim){
            Verticie? v1 = (Verticie?)a[i];
            Verticie? v2 = (Verticie?)a[j];
            if(v1 == null || v2 == null){
                return;
            }
            if(v1.getId() < v2.getId()){
                b.Add(v1);
                i++;
            }
            else{
                b.Add(v2);
                j++;
            }
        }
        while(i <= meio){
            b.Add(a[i]);
            i++;
        }
        while(j <= fim){
            b.Add(a[j]);
            j++;
        }
        for(int k = inicio; k <= fim; k++){
            a[k] = b[k - inicio];
        }
    }
    static void mergesort(ArrayList a, int inicio, int fim){
        if(inicio < fim){
            int meio = (inicio + fim) / 2;
            mergesort(a,inicio,meio);
            mergesort(a,meio + 1, fim);
            merge(a,inicio,meio,fim);
        }   
    }

    static void podeParar(ArrayList O, int iteracao, Grafo g){
        for(int i = iteracao + 1; i < g.getNumVerticies(); i++){
            printO(O,i);
        }
    }

    static void leGrafo(string nomeArquivo, Grafo g){
        // read file
        string[] lines = File.ReadAllLines(nomeArquivo);

        foreach(string line in lines){
            string[] values = line.Split(' ');
            if (values[0] == "I"){
                int numVerticies = int.Parse(values[1]);
                int numArestas = int.Parse(values[2]);
                g.setNumVerticies(numVerticies);
                g.setNumArestas(numArestas);
            }
            else if(values[0] == "N"){
                int id = int.Parse(values[1]);
                int grauEntrada = int.Parse(values[2]);
                int grauSaida = int.Parse(values[3]);
                g.addVerticie(id,grauEntrada,grauSaida);
            }
            else if(values[0] == "E"){
                int origem = int.Parse(values[1]);
                int destino = int.Parse(values[2]);
                int custo = int.Parse(values[3]);
                g.addArco(origem,destino,custo);
            }
        }
    }
    static void printO(ArrayList O, int iteracao){
        Console.Write("O " + iteracao + " ");
        foreach(Verticie v in O){
            Console.Write(v.getId() + " ");
        }
        Console.WriteLine();
    }
    static bool cicloNegativo(Grafo g, int[] custo){
        foreach(Verticie v in g.getVerticies()){
            ArrayList arcos = v.getArcos();
            foreach(Arco a in arcos){
                Verticie? u = a.getDestino();
                if(u == null){
                    return false;
                }
                if(custo[u.getId()] > custo[v.getId()] + a.getCusto()){
                    return true;
                }
            }
        }
        return false;
    }

    static void printaCaminho(int[] anteriores, int[] custo, Verticie v, Grafo g){
        ArrayList todos = g.getVerticies();
        mergesort(todos,0,todos.Count - 1);
        foreach (Verticie ver in todos){
            if(ver.getId() == v.getId()){
                Console.WriteLine("P " + ver.getId() + " 0 1 " + ver.getId());
            }
            else if(anteriores[ver.getId()] == -1){
                Console.WriteLine("U" + ver.getId());
            }
            else {
                ArrayList caminho = new ArrayList();
                int ant = anteriores[ver.getId()];
                while(ant != v.getId() && ant != -1){
                    caminho.Insert(0,ant);
                    ant = anteriores[ant];
                }
                int tamanho = caminho.Count + 2;
                Console.Write("P " + ver.getId() +  " " + custo[ver.getId()] + " " + tamanho + " " + v.getId());
                foreach(int i in caminho){
                    Console.Write(" " + i);
                }
                Console.WriteLine(" " + ver.getId());
            }
        }
    }
    static void bellmanford(Grafo g, Verticie v, int[] anteriores, int[] custo){
        for(int i = 0; i < g.getNumVerticies(); i++){
            anteriores[i] = -1;
            custo[i] = 2000000;
        }
        ArrayList O = g.getVerticies();
        int idV = 0;
        foreach(Verticie ver in O){
            if(ver.getId() == v.getId()){
                idV = ver.getId();
                break;
            }
        }
        custo[idV] = 0;
        anteriores[idV] = idV;
        // swap O[0] with O[idV]
        Verticie? aux = (Verticie?)O[0];
        if(aux == null){
            return;
        }
        O[0] = O[idV];
        O[idV] = aux;
        mergesort(O,1,O.Count - 1);
        int iteracoes = 0;
        do{
            printO(O,iteracoes);
            
            bool []processados = new bool[g.getNumVerticies()];
            bool []reduzidos = new bool[g.getNumVerticies()];
            bool []reduzidosApos = new bool[g.getNumVerticies()];
            bool redApos = false;
            bool red = false;
            for(int i = 0; i < g.getNumVerticies(); i++){
                processados[i] = false;
                reduzidos[i] = false;
                reduzidosApos[i] = false;
            }
            foreach(Verticie u in O){
                processados[u.getId()] = true;
                ArrayList arcos = u.getArcos();
                foreach(Arco a in arcos){
                    Verticie? ver = a.getDestino();
                    if(ver == null){
                        return;
                    }
                    if(custo[ver.getId()] > custo[u.getId()] + a.getCusto()){
                        custo[ver.getId()] = custo[u.getId()] + a.getCusto();
                        anteriores[ver.getId()] = u.getId();
                        if(!processados[ver.getId()]){
                            reduzidos[ver.getId()] = true;
                            red = true;
                        }
                        else{
                            reduzidosApos[ver.getId()] = true;
                            redApos = true;
                        }
                    }
                }
            }
            ArrayList OLinha = new ArrayList();
            foreach(Verticie w in O){
                if(reduzidosApos[w.getId()]){
                    OLinha.Add(w);
                }
            }
            foreach(Verticie w in O){
                if(reduzidos[w.getId()] && !OLinha.Contains(w)){
                    OLinha.Add(w);
                }
            }
            foreach(Verticie w in O){
                if(!OLinha.Contains(w)){
                    OLinha.Add(w);
                }
            }
            if(!(redApos || red)){
                podeParar(OLinha,iteracoes,g);
                break;
            }
            O = OLinha;
            iteracoes++;
        }while(iteracoes < g.getNumVerticies());

        if(cicloNegativo(g,custo)){
            Console.WriteLine("C");
        }
        else{
            printaCaminho(anteriores,custo,v,g);
        }
    }

    public static void Main(string[] args){
        string arquivo = "args[0];";
        int id = 2;
        if(args.Length == 2){
            arquivo = args[0];
            id = int.Parse(args[1]);
        }
        else{
            arquivo = "../g-10-30.txt";
            id = 0;
        }
        Grafo g = new Grafo();
        leGrafo(arquivo,g);
        Verticie? v = g.getVerticie(id);
         if(v == null){
            throw new Exception("Erro");
         }

        int []anteriores = new int[g.getNumVerticies()];
        int []custo = new int[g.getNumVerticies()];


        bellmanford(g,v,anteriores,custo);
    }
}


