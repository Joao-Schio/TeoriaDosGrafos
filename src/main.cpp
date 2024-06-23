/**
 * Aluno João Pedro Schio Ortega
 * comando de compilacao usado - g++ src/<regex para todos>.cpp -o pccm -Wall -Werror -std=c++20
 * (por algum motivo o Werror nao deixa compilar com asteristico dentro de comentario)
 *  
 * 
 * Considerações após a recorreção
 * 
 * Eu achava que o problema era a std::tuple mas não era
 * 
 * o problema era que eu fazia um vetor de verticies, e entao sempre que eu acessava um verticie 
 * ele tinha que passar por um construtor e quando ele saia de um escopo um destrutor
 * entao (não me pergunte quanto tempo eu demorei pra descobrir isso)
 * 
 * mudando as classes para um vetor de ponteiros para verticie cada verticie so passa por um construtor e um destrutor
 * o que aumenta significativamente a velocidade do programa
 * 
 * mas quando eu descobri ja tinha me livrado da tupla entao fica sem mesmo
 * 
 * o mergesort não estava comendo tanta performance mas decidi usar uma tabela de dispersão para aumentar a eficiência do código
 * 
*/



#include <iostream>
#include "Grafo.hpp"

Grafo* leGrafo(std::string nomeArquivo){
    FILE *arquivo = fopen(nomeArquivo.c_str(), "r");
    if(arquivo == NULL){
        std::cout << "E" << std::endl;
        exit(1);
    }
    Grafo *g = nullptr;
    char inicio = 'i';
    while(fscanf(arquivo, "%c", &inicio) != EOF){
        /**
         * Para remover o mergesort eu decidi usar o vetor de vertices do grafo como sendo uma tabela de dispersao
         * onde f(x) = x para a funcao de dispersao
         * isso elimina a necessidade do mergesort pois a insercao do grafo ja é ordenada
         */
        if(inicio == 'I'){
            int verticies,arcos;
            fscanf(arquivo, "%d %d", &verticies, &arcos);
            g = new Grafo(verticies,arcos);
        }

        else if(inicio == 'N'){
            int id, gEntrada, gSaida;
            fscanf(arquivo, "%d %d %d", &id, &gEntrada, &gSaida);

            if(g == nullptr){
                std::cout << "E" << std::endl;
                exit(1);
            }
            else{
                g -> addVerticie(id,gEntrada, gSaida);
            }
        }

        else if(inicio == 'E'){
            int id, vizinho, custo;
            fscanf(arquivo, "%d %d %d", &id, &vizinho, &custo);

            if(g == nullptr){
                std::cout << "E" << std::endl;
                exit(1);
            }

            else{
                g -> addArco(id,vizinho,custo);
            }
        }
        else if(inicio == 'T'){
            break;
        }
    }
    fclose(arquivo);
    return g;
}

void imprimeVisitacao(std::vector<Verticie*> &O,int iteracao){
    printf("O %d ",iteracao);
    for(unsigned i = 0; i < O.size(); i++){
        printf("%d ",O.at(i) -> getId());
    }
    printf("\n");
}


void desmarcar(std::vector<bool> &v){
    for(unsigned i = 0; i < v.size(); i++){
        v.at(i) = false;
    }
}


void printCaminho(std::vector<Verticie*> *anterior, std::vector<int> *custo, Verticie *v, Grafo *g){
    std::vector<Verticie*> todos = g -> getVerticesVetor();

    for(unsigned x = 0; x < todos.size(); x++){
        Verticie *i = todos.at(x);
        if(i -> igual(*v)){
            printf("P %d 0 1 %d\n",i -> getId(),i -> getId());
        }

        else if(anterior -> at(i -> getId()) -> igual(Verticie())){
            printf("U %d\n",i -> getId());
        }

        else if (!i -> igual(*v)){
            std::vector<int> idCaminho;
            Verticie *aux = anterior -> at(i -> getId());

            while(!aux -> igual(*v) && !aux -> igual(Verticie())){
                idCaminho.insert(idCaminho.begin(),aux -> getId());
                aux = anterior -> at(aux -> getId());
            }

            printf("P %d %d %ld %d ",i -> getId(),custo -> at(i -> getId()),idCaminho.size() + 2,v -> getId());
            for(int j : idCaminho){
                printf("%d ",j);
            }

            printf("%d\n",i -> getId());
        }
    }
}

bool cicloNeg(Grafo *g, Verticie *v, std::vector<int> *custo){
    for(int x = 0; x < g -> getNumVertices(); x++){
        Verticie *u = g -> getVerticie(x);
        std::vector<Arco> arcos = u -> getArcos();
        for(unsigned y = 0; y < arcos.size(); y++){
            Arco arco = arcos.at(y);
            Verticie vArco = *(arco.getDestino());
            int custoArco = arco.getCusto();
            if(custo -> at(vArco.getId()) > custo -> at(u -> getId()) + custoArco){
                return true;
            }
        }
    }
    return false;
}

void podeParar(std::vector<Verticie*> &O, int iteracoes, int tamGrafo){
    for(int i = iteracoes + 1; i < tamGrafo; i++){
        imprimeVisitacao(O,i);
    }
}

void passaPraFrente(std::vector<Verticie*> &O, int pos){
    Verticie *aux = O.at(pos);
    for(unsigned i = pos; i > 0; i--){
        O.at(i) = O.at(i - 1);
    }
    O.at(0) = aux;
}

void bellmanford(Grafo *g, Verticie *v,std::vector<Verticie*> *anterior, std::vector<int> *custo){
    // Entradas grafo G, verticie de origem V, vetor de verticies que armazena o anterior de um id
    // vetor de custo que armazena o custo da origem ate o verticie com o id 
    for(int i = 0; i < g -> getNumVertices();i++){
       anterior -> at(i) = new Verticie();
        custo -> at(i) = 200000000; // numero muito maior que o custo maximo
    }
    custo -> at(v -> getId()) = 0;
    // definindo a ordem
    std::vector<Verticie*> O = g -> getVerticesVetor();
    

    passaPraFrente(O,v -> getId());

    std::vector<bool> processados(g -> getNumVertices());
    std::vector<bool> reduzidos(g -> getNumVertices());
    std::vector<bool> reduzidoApos(g -> getNumVertices());
    std::vector<bool> inserido(g -> getNumVertices());

    long iteracoes = 0;
    while(iteracoes < g -> getNumVertices()){
        imprimeVisitacao(O,iteracoes);
        desmarcar(processados);
        desmarcar(reduzidos);
        desmarcar(reduzidoApos);
        desmarcar(inserido);

        bool entrouNoRedApos = false; 
        bool entrouNoRed = false; 
        for(unsigned i = 0; i < O.size(); i++){
            Verticie *u = O.at(i);
            processados.at(u -> getId()) = true;
            std::vector<Arco> arcos = u -> getArcos();
            for(unsigned j = 0; j < arcos.size(); j++){
                Arco arco = arcos.at(j);
                int idDestino = arco.getIdDestino();
                int custoArco = arco.getCusto();
                if(custo -> at(idDestino) > custo -> at(u -> getId()) + custoArco){
                    custo -> at(idDestino) = custo -> at(u -> getId()) + custoArco;
                    anterior -> at(idDestino) = u;
                    if(processados.at(idDestino)){
                        reduzidoApos.at(idDestino) = true;
                        entrouNoRedApos = true;
                    }
                    else if(!processados.at(idDestino)){ 
                        reduzidos.at(idDestino) = true;
                        entrouNoRed = true;
                    }
                }
            }
        }
        if(!entrouNoRedApos && !entrouNoRed){
            podeParar(O,iteracoes,g -> getNumVertices());
            break;
        }
        int pos = 0;
        std::vector<Verticie*> OLinha(g -> getNumVertices());

        for(unsigned x = 0; x < O.size(); x++){
            Verticie *i = O.at(x);
            if(reduzidoApos.at(i -> getId())){
                OLinha.at(pos) = i;
                inserido.at(i -> getId()) = true;
                pos++;
            }
        }
        for(unsigned x = 0; x < O.size(); x++){
            Verticie *i = O.at(x);
            if(reduzidos.at(i -> getId()) && !inserido.at(i -> getId())){
                OLinha.at(pos) = i;
                inserido.at(i -> getId()) = true;
                pos++;
            }
        }
        for(unsigned x = 0; x < O.size(); x++){
            Verticie *i = O.at(x);
            if(!inserido.at(i -> getId())){
                OLinha.at(pos) = i;
                inserido.at(i -> getId()) = true;
                pos++;
            }
        }
        iteracoes++;
        O = OLinha;
        OLinha.clear();
    }
    if(!cicloNeg(g,v,custo))
        printCaminho(anterior,custo,v,g);
    else if(cicloNeg(g,v,custo)){
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

    Grafo *g = leGrafo(nomeArquivo);


    // como esse vetor nao eh um vetor* ele nao precisa de delete explicito
    std::vector<Verticie*> anteriores(g -> getNumVertices()); 
    // e os objetos que estao nele vao ser deletados quando o g++ chamar a funcao de destrutor do grafo

    std::vector<int> distancias(g -> getNumVertices());

    Verticie *v = g -> getVerticie(idVerticie);

    bellmanford(g,v,&anteriores,&distancias);
    
    delete g;
    anteriores.clear();
    distancias.clear();
    return 0;
}
