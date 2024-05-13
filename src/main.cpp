#include <iostream>
#include "Grafo.hpp"


void leGrafo(std::string nomeArquivo, Grafo *g){
    FILE *arquivo = fopen(nomeArquivo.c_str(), "r");
    if(arquivo == NULL){
        std::cout << "E" << std::endl;
        exit(1);
    }
    char inicio = 'i';
    while(fscanf(arquivo, "%c", &inicio) != EOF){
        if(inicio == 'I'){
            int arestas,arcos;
            fscanf(arquivo, "%d %d", &arestas, &arcos);
            g -> setNumVertices(arestas);
            g -> setNumArestas(arcos);
        }

        else if(inicio == 'N'){
            int id, gEntrada, gSaida;
            fscanf(arquivo, "%d %d %d", &id, &gEntrada, &gSaida);
            g -> addVerticie(id,gEntrada, gSaida);
        }

        else if(inicio == 'E'){
            int id, vizinho, custo;
            fscanf(arquivo, "%d %d %d", &id, &vizinho, &custo);
            g -> addArco(id,vizinho,custo);
        }
        else if(inicio == 'T'){
            break;
        }
    }
    fclose(arquivo);
}


void merge(std::vector<Verticie> &v, int inicio,int meio, int fim){
    int tamanho1 = meio - inicio + 1;
    int tamanho2 = fim - meio;
    std::vector<Verticie> aux1(tamanho1);
    std::vector<Verticie> aux2(tamanho2);

    for(int i = 0; i < tamanho1; i++){
        aux1[i] = v.at(i + inicio);
    }
    for(int i = 0; i < tamanho2; i++){
        aux2[i] = v.at(1 + meio + i);
    }

    int i = 0, j = 0, k = inicio;

    while(i < tamanho1 && j < tamanho2){
        if(aux1[i].getId() > aux2[j].getId()){
            v.at(k) = aux2[j];
            j++;
        }
        else{
            v.at(k) = aux1[i];
            i++;
        }
        k++;
    }   
    while(j < tamanho2){
        v.at(k) = aux2[j];
        j++;
        k++;
    }
    while(i < tamanho1){
        v.at(k) = aux1[i];
        i++;
        k++;
    }
}

void imprimeVisitacao(std::vector<Verticie> O,int iteracao){
    std::cout << "O " << iteracao << " ";
    for(Verticie v : O){
        std::cout << v.getId() << " ";
    }
    std::cout << std::endl;
}

void mergesort(std::vector<Verticie> &v, int inicio, int fim){
    if(fim > inicio){
        int meio = (fim + inicio) / 2;
        mergesort(v,inicio,meio);
        mergesort(v, meio + 1, fim);
        merge(v,inicio,meio,fim);
    }
}

bool contem(std::vector<Verticie> v, Verticie a){
    for(Verticie b : v){
        if(a.getId() == b.getId()){
            return true;
        }
    }
    return false;
}

void desmarcar(std::vector<bool> v){
    for(unsigned i = 0; i < v.size(); i++){
        v.at(i) = false;
    }
}


void printCaminho(std::vector<Verticie> anterior, std::vector<int> custo, Verticie v, Grafo g){
    std::vector<Verticie> todos = g.getVerticesVetor();
    mergesort(todos,0,todos.size() - 1);
    for(Verticie i : todos){
        if(i.igual(v)){
            std::cout << "P " << i.getId() << " 0 1 " << i.getId() << std::endl;
        }
        else if(anterior.at(i.getId()).igual(Verticie())){
            std::cout << "U " << i.getId() << std::endl;
        }
        else if (!i.igual(v)){
            std::vector<int> idCaminho;
            Verticie aux = anterior.at(i.getId());
            while(!aux.igual(v) && !aux.igual(Verticie())){
                idCaminho.insert(idCaminho.begin(),aux.getId());
                aux = anterior.at(aux.getId());
            }
            std::cout << "P " << i.getId() << " " << custo.at(i.getId()) << " " << idCaminho.size() + 2 << " " << v.getId() << " ";
            for(int j : idCaminho){
                std::cout << j << " ";
            }
            std::cout << i.getId() << std::endl;
        }
    }
}

bool cicloNeg(Grafo g, Verticie v,std::vector<Verticie> anterior, std::vector<int> custo){
    for(Verticie u : g.getVerticesVetor()){
        for(std::tuple<Verticie,int> arco : u.getArcos()){
            Verticie vArco = std::get<0>(arco);
            int custoArco = std::get<1>(arco);
            if(custo.at(vArco.getId()) > custo.at(u.getId()) + custoArco){
                return true;
            }
        }
    }
    return false;
}


void bellmanford(Grafo g, Verticie v,std::vector<Verticie> anterior, std::vector<int> custo){
    // Entradas grafo G, verticie de origem V, vetor de verticies que armazena o anterior de um id
    // vetor de custo que armazena o custo da origem ate o verticie com o id 
    for(unsigned i = 0; i < g.getNumVertices();i++){
        anterior[i] = Verticie();
        custo[i] =  200000000; // int max como infinito
    }
    custo[v.getId()] = 0;
    // definindo a ordem
    std::vector<Verticie> O = g.getVerticesVetor();
    int idV = 0;
    // achando a posicao do verticie V em O
    for(unsigned i = 0; i < O.size(); i++){
        if(O.at(i).igual(v)){
            idV = i;
        }
    }
    // definindo a ordem comecando em V e seguindo em ordem crescente de ID
    Verticie aux = O.at(0);
    O.at(0) = O.at(idV);
    O.at(idV) = aux;
    mergesort(O,1,O.size() - 1);

    long iteracoes = 0;
    while(iteracoes < g.getNumVertices()){
        imprimeVisitacao(O,iteracoes);
        std::vector<Verticie> processados(0);
        std::vector<Verticie> reduzidos(0);
        std::vector<Verticie> reduzidoApos(0);

        for(Verticie u : O){
            processados.push_back(u);
            for(std::tuple<Verticie,int> arco : u.getArcos()){
                Verticie vArco = std::get<0>(arco);
                int custoArco = std::get<1>(arco);
                if(custo.at(vArco.getId()) > custo.at(u.getId()) + custoArco){
                    custo.at(vArco.getId()) = custo.at(u.getId()) + custoArco;
                    anterior.at(vArco.getId()) = u;
                    if(contem(processados,vArco)){
                        reduzidoApos.push_back(vArco);
                    }
                    else if(!contem(processados,vArco)){
                        reduzidos.push_back(vArco);
                    }
                }
            }
        }
        int pos = 0;
        std::vector<Verticie> OLinha(g.getNumVertices());
        for(Verticie i : O){
            if(contem(reduzidoApos,i)){
                OLinha.at(pos) = i;
                pos++;
            }
        }
        for(Verticie i : O){
            if(contem(reduzidos,i) && !contem(OLinha,i)){
                OLinha.at(pos) = i;
                pos++;
            }
        }
        for(Verticie i : O){
            if(!contem(OLinha,i)){
                OLinha.at(pos) = i;
                pos++;
            }
        }
        iteracoes++;
        for(unsigned i = 0 ; i < OLinha.size(); i++){
            O.at(i) = OLinha.at(i);
        }
    }
    if(!cicloNeg(g,v,anterior,custo))
        printCaminho(anterior,custo,v,g);
    else if(cicloNeg(g,v,anterior,custo)){
        std::cout << "C" << std::endl;
    }
}


int main(int argc, char **argv){

    int idVerticie;

    if(argc != 3){
        std::cout << "E" << std::endl;
        exit(1);
    }
    std::string nomeArquivo = argv[1];
    std::string vId = argv[2];
    idVerticie = std::stoi(vId);
    //std::string nomeArquivo = "g-neg-c-10-30.txt";
    //idVerticie = 0;
    Grafo g = Grafo();

    leGrafo(nomeArquivo, &g);
    std::vector<Verticie> anteriores(g.getNumVertices());
    std::vector<int> distancias(g.getNumVertices());
    bellmanford(g,g.getVerticie(idVerticie),anteriores,distancias);

    return 0;
}