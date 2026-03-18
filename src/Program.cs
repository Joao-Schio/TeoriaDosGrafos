




using grafo;
using System.Collections;
using verticie;
using arco;
public class Program{
    static void podeParar(IEnumerable<Verticie> O, int iteracao, Grafo g){
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
    static void printO(IEnumerable<Verticie> O, int iteracao){
        Console.Write("O " + iteracao + " ");
        foreach(var v in O){
            Console.Write(v.Id + " ");
        }
        Console.WriteLine();
    }
    static bool cicloNegativo(Grafo g, int[] custo){
        foreach(Verticie v in g.getVerticies()){
            var arcos = v.Arcos;
            foreach(Arco a in arcos){
                Verticie? u = a.Destino;
                if(u == null){
                    return false;
                }
                if(custo[u.Id] > custo[v.Id] + a.Custo){
                    return true;
                }
            }
        }
        return false;
    }

    static void printaCaminho(int[] anteriores, int[] custo, Verticie v, Grafo g){
        var todos = g.getVerticies();
        todos.Sort();

        foreach (Verticie ver in todos){
            if(ver.Id == v.Id){
                Console.WriteLine("P " + ver.Id + " 0 1 " + ver.Id);
            }
            else if(anteriores[ver.Id] == -1){
                Console.WriteLine("U " + ver.Id);
            }
            else {
                var caminho = new List<int>();
                int ant = anteriores[ver.Id];
                while(ant != v.Id && ant != -1){
                    caminho.Insert(0,ant);
                    ant = anteriores[ant];
                }
                int tamanho = caminho.Count + 2;
                Console.Write("P " + ver.Id +  " " + custo[ver.Id] + " " + tamanho + " " + v.Id);
                foreach(int i in caminho){
                    Console.Write(" " + i);
                }
                Console.WriteLine(" " + ver.Id);
            }
        }
    }
    static void bellmanford(Grafo g, Verticie v, int[] anteriores, int[] custo){
        for(int i = 0; i < g.getNumVerticies(); i++){
            anteriores[i] = -1;
            custo[i] = 2000000;
        }
        var O = g.getVerticies();
        int idV = 0;
        foreach(Verticie ver in O){
            if(ver.Id == v.Id){
                idV = ver.Id;
                break;
            }
        }
        custo[idV] = 0;
        anteriores[idV] = idV;
        Verticie? aux = (Verticie?)O[0];
        if(aux == null){
            return;
        }
        O[0] = O[idV];
        O[idV] = aux;
        O.Sort(1, O.Count - 1, null);
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
                processados[u.Id] = true;
                var arcos = u.Arcos;
                foreach(Arco a in arcos){
                    Verticie? ver = a.Destino;
                    if(ver == null){
                        return;
                    }
                    if(custo[ver.Id] > custo[u.Id] + a.Custo){
                        custo[ver.Id] = custo[u.Id] + a.Custo;
                        anteriores[ver.Id] = u.Id;
                        if(!processados[ver.Id]){
                            reduzidos[ver.Id] = true;
                            red = true;
                        }
                        else{
                            reduzidosApos[ver.Id] = true;
                            redApos = true;
                        }
                    }
                }
            }
            var OLinha = new List<Verticie>();
            foreach(Verticie w in O){
                if(reduzidosApos[w.Id]){
                    OLinha.Add(w);
                }
            }
            foreach(Verticie w in O){
                if(reduzidos[w.Id] && !OLinha.Contains(w)){
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
        Verticie? v = g.getVerticie(id) ?? throw new Exception("Erro");
        int []anteriores = new int[g.getNumVerticies()];
        int []custo = new int[g.getNumVerticies()];


        bellmanford(g,v,anteriores,custo);
    }
}


