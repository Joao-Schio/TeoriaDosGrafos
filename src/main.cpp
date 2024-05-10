#include <iostream>
#include "Grafo.hpp"
#include <algorithm>
#define REDUZIDO 1
#define PROCESSADO 3
#define NAO_PROCESSADO 0
#define VERTICIE_DO_ALG 4


void leGrafo(std::string nomeArquivo, Grafo *g){
    FILE *arquivo = fopen(nomeArquivo.c_str(), "r");
    if(arquivo == NULL){
        std::cout << "Erro ao abrir o arquivo" << std::endl;
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
        if(a.igual(b)){
            return true;
        }
    }
    return false;
}

void desmarcar(std::vector<int> v){
    for(unsigned i = 0; i < v.size(); i++){
        v[i] = NAO_PROCESSADO;
    }
}

std::vector<Grafo> bellmanford(Grafo g, Verticie v){
    std::vector<Verticie> anterior(g.getNumVertices());
    std::vector<int> distancia(g.getNumVertices());
    std::vector<Verticie> O = g.getVerticesVetor();
    std::vector<int> estadoVerticie(g.getNumVertices());


    /**
     * minha ideia eh usar os vetores como se fossem uma tabela de dispersao
     * com a funcao de dispersao sendo f(x) = x - 1
     * para um acesso mais rapido
     * diferentemente do vetor O que a ordem importa
     * 
     * anterior vai receber o verticie anterior a ele no caminho
     * e distancia vai receber o valor de v ate ele
     * 
     * 
     * exemplo:
     * G = ({1,2,3},{(1,2,3),(1,2,4)})
     * 
     * v = a
     * distancia[0] = 0
     * distancia[1] = 3
     * distancia[2] = 7
     * 
     * anterior[0] = null
     * anterior[1] = Verticie(1)
     * anterior[2] = Verticie(2)
    */

   int idV = 0;
    for(unsigned i = 0; i < g.getNumVertices(); i++){
        distancia[i] = __INT_MAX__; // distancia comeca sendo intmax
        anterior[i] = Verticie(-1,0,0); // verticie com id -1 significa que nao foi iniciado ainda
        if(v.igual(O.at(i))){
            idV = i;
        }
        estadoVerticie[i] = NAO_PROCESSADO;
    }
    
    Verticie aux = O[0];
    O[0] = O[idV];
    O[idV] = aux;
    mergesort(O,1,O.size() - 1); // para ter certeza que na primeira iteracao O sempre estara em ordem crescente
    std::vector<Grafo> saida;
    estadoVerticie[v.getId()] = VERTICIE_DO_ALG;
    long iteracoes = 0;
    do{
        imprimeVisitacao(O,iteracoes);
        std::vector<Verticie> OLinha;
        Grafo grafo = Grafo();
        desmarcar(estadoVerticie);
        for(Verticie v : O){
            grafo.addVerticie(v.getId(),0,0);
            estadoVerticie[v.getId()] = PROCESSADO;
            for(std::tuple<Verticie,int> a : v.getArcos()){
                if(distancia[v.getId()] + std::get<1>(a) < distancia[std::get<0>(a).getId()]){
                    grafo.addVerticie(std::get<0>(a).getId(),0,0);
                    distancia[std::get<0>(a).getId()] = distancia[v.getId()] + std::get<1>(a);
                    anterior[v.getId()] = std::get<0>(a);
                    estadoVerticie[std::get<0>(a).getId()] = REDUZIDO;
                    if(estadoVerticie[std::get<0>(a).getId()] != PROCESSADO){
                        OLinha.push_back(std::get<0>(a));
                    }
                    grafo.addArco(v.getId(),std::get<0>(a).getId(),std::get<1>(a));
                }
            }
        }
        for(unsigned i = 0; i < O.size(); i++){
            if(estadoVerticie[O[i].getId()] == REDUZIDO ){
                OLinha.push_back(O[i]);
            }
        }
        for(unsigned i = 0; i < O.size(); i++){
            if(estadoVerticie[O[i].getId()] != PROCESSADO && estadoVerticie[O[i].getId()] != REDUZIDO){
                OLinha.push_back(O[i]);
            }
        }

        for(unsigned i = 0; i < O.size(); i++){
            O[i] = OLinha[i];
        }
        iteracoes++;
        saida.push_back(grafo);
    }while(iteracoes < g.getNumVertices() - 1);
    return saida;
}


int main(int argc, char **argv){

    if(argc != 2){
        std::cout << "Erro: Argumentos invalidos" << std::endl;
        std::cout << "Uso: " << argv[0] << " <nome do arquivo>" << std::endl;
        exit(1);
    }
    std::string nomeArquivo = argv[1];
    //std::string nomeArquivo = "g1.txt";
    Grafo g = Grafo();

    leGrafo(nomeArquivo, &g);
    bellmanford(g, g.getVerticie(1));
    return 0;
}