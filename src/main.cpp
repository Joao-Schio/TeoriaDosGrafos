#include <iostream>
#include "Grafo.hpp"





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
            int id;
            fscanf(arquivo, "%d", &id);
            g -> addVerticie(id);
            int x, y;
            fscanf(arquivo, "%d %d", &x, &y);
        }

        else if(inicio == 'E'){
            int id, vizinho, custo;
            fscanf(arquivo, "%d %d %d", &id, &vizinho, &custo);
            std::tuple<int,int> aresta = std::make_tuple(vizinho, custo);
            g -> addVizinho(id, aresta);
        }
        else if(inicio == 'T'){
            break;
        }
    }
    fclose(arquivo);
}



int main(int argc, char **argv){

    std::string nomeArquivo = argv[1];

    Grafo g = Grafo();

    leGrafo(nomeArquivo, &g);
    

    g.printVertices();
    

    return 0;
}